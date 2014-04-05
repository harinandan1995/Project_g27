/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif
#include <vector>
#include <cstring>
using namespace std;
#include <string>
#include "dominos.hpp"
#include <iostream>



namespace cs296
{
  /*!  The is the constructor <br>
   * This is the documentation block for the constructor.<br>
   * It creates the various parts of the simulation <bar>
*/	
	b2Vec2 init;

	vector <b2Vec2> positions;


/*bd_player2[0].position.Set(25.0f,20.0f);
		team2[0] = m_world->CreateBody(&bd_player2[0]);
		
		player2[0].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team2[0]->CreateFixture(&player2[0],0.0f);
		fd->filter.maskBits = 0x0000;*/

	vector <b2Body*> playerbodies;
	void keyboard(unsigned char);

/*void dominos_t::checkUp(b2Vec2 v1, b2Vec2 v2,b2PrismaticJoint* m_joint)
{
cout<<"Yo"<<endl;
b2Body *bod= m_joint->GetBodyA();
	if(v1.x-v2.x > 0.5 || v1.x-v2.x<-0.5)
	{
			cout<<"Heyo"<<endl;
			b2Filter filt=bod->GetFixtureList()->GetFilterData();
			filt.maskBits=0x0000;
			bod->GetFixtureList()->SetFilterData(filt);
		}
		else
		{
		cout<<"geyo"<<endl;
			b2Filter filt=bod->GetFixtureList()->GetFilterData();
			filt.maskBits=0xFFFF;
			bod->GetFixtureList()->SetFilterData(filt);
		}
	/*if(v1.x - v2.x > 0.1)
	{
	m_joint->SetMotorSpeed(0);
	}

}*/

/*void dominos_t::checkUp()
{

	 if(isGoingUp>5||isGoingUp<-5)
		for (int i=0;i<playerbodies.size();i++)
		{
			b2Filter filt=playerbodies[i]->GetFixtureList()->GetFilterData();
			filt.maskBits=0x0000;
			playerbodies[i]->GetFixtureList()->SetFilterData(filt);
		}
	/*	for (int i=0;i<playerbodies.size();i++)
		{
			b2Filter filt=playerbodies[i]->GetFixtureList()->GetFilterData();
			filt.maskBits=0xFFFF;
			playerbodies[i]->GetFixtureList()->SetFilterData(filt);
		}
		if( isGoingUp==0)
		{
			for (int i=0;i<playerbodies.size();i++)
			{
				playerbodies[i]->SetLinearVelocity(b2Vec2(0.0,0.0));
			}
		}
	
}*/
float dominos_t::incrGoingUp(int num)
{
	this->isGoingUp += num;
	return this->isGoingUp;
}
void dominos_t::resetUp()
{
		isGoingUp=0;
		
}

	int team1_score=-1,team2_score=-1;
	b2Body* ball;
	b2Body* rod[4];
	b2Body* score1[10];
	b2Body* score2[10];
	b2BodyDef bd_score1[10];
	b2BodyDef bd_score2[10];
		/*void dominos_t::KeyboardUp(unsigned char key){
		switch(key){
		}
		}*/
			void dominos_t::keyboard(unsigned char key){
				std::cout<<isGoingUp<<endl;
				int mul=6;
				//checkUp(m_joint->GetAnchorB(), m_joint->GetAnchorA(), m_joint);
		switch(key){
		case 'y':
		rod[3]->ApplyLinearImpulse(b2Vec2(0,40),rod[3]->GetPosition(),100);
		break;
		case 'h':
		rod[3]->ApplyLinearImpulse(b2Vec2(0,-40),rod[3]->GetPosition(),100);
		break;
		case ' ':
		rod[3]->SetLinearVelocity(b2Vec2(0,0));
		break;
		case 'v':
		if(m_joint->GetAnchorA().x - m_joint->GetAnchorB().x >0)// far right state
		m_joint->SetMotorSpeed(mul*2.0f);
		else // go for a shot!
		m_joint->SetMotorSpeed(mul*(2*(m_joint->GetAnchorB().x - m_joint->GetAnchorA().x)+.5));
		break;
		case 'n':
		if(m_joint->GetAnchorA().x - m_joint->GetAnchorB().x <0)// far left state
		m_joint->SetMotorSpeed(mul*-2.0f);
		else // go for a shot!
		m_joint->SetMotorSpeed(mul*(2*(m_joint->GetAnchorA().x - m_joint->GetAnchorB().x)-.5));
		break;
		case 'b':
		m_joint->SetMotorSpeed(0);
		break;
		//m_joint->SetMotorSpeed(-4.0f);
			case 'w':
			ball->ApplyLinearImpulse(b2Vec2(0,10),ball->GetPosition(),100);
			break;
			case 's':
			ball->ApplyLinearImpulse(b2Vec2(0,-10),ball->GetPosition(),100);
			//playerbodies[0]->ApplyLinearImpulse(b2Vec2(0,10),playerbodies[0]->GetPosition(),100);
			break;
			case 'a':
			//checkUp();
			ball->ApplyLinearImpulse(b2Vec2(-10,0),ball->GetPosition(),100);
			/*if(isGoingUp < -5)
			{
			playerbodies[0]->ApplyLinearImpulse(b2Vec2(-incrGoingUp(0),0),playerbodies[0]->GetPosition(),100);
			resetUp();
			}
			else
			incrGoingUp(-1);*/
			break;
			case 'd':
			//checkUp();
			ball->ApplyLinearImpulse(b2Vec2(10,0),ball->GetPosition(),100);
			/*if(isGoingUp > 5)
			{
			playerbodies[0]->ApplyLinearImpulse(b2Vec2(incrGoingUp(0),0),playerbodies[0]->GetPosition(),100);
			resetUp();
			}
			else
			incrGoingUp(1);*/
			break;
			default:
			break;
		}
		}

	void dominos_t::score_1(int i){
		if(i!=-1){
			//score1[9-i]->ApplyLinearImpulse(b2Vec2(0,1000),score1[9-i]->GetPosition(),100);
			score1[9-i]->SetLinearVelocity(b2Vec2(0,10));
		}
	}
	
	void dominos_t::score_2(int j){
		if(j!=-1){
			score2[9-j]->SetLinearVelocity(b2Vec2(0,-10));
		}
	}
	
	void dominos_t::check(void){
		if(ball->GetPosition().x<=32 && ball->GetPosition().x>=30 &&
			ball->GetPosition().y>=14 && ball->GetPosition().y <=26){
				ball->SetTransform(b2Vec2(0,20),0);team1_score++;
				score_1(team1_score);
				if(team1_score==3){
					for(int i=0;i<10;i++){
						score1[i]->SetTransform(b2Vec2(-35.0f,6+2.2*i),0);
						score2[i]->SetTransform(b2Vec2(35.0f,34-2*i),0);
						score1[9-i]->SetLinearVelocity(b2Vec2(0,0));
						score2[9-i]->SetLinearVelocity(b2Vec2(0,0));
					}
				}
			}
		for(int i=0;i<10;i++){
			//cout<<score1[i]->GetPosition().y<<endl;
			if(score1[9-i]->GetPosition().y>=34-i*2){
				score1[9-i]->SetLinearVelocity(b2Vec2(0,0));
			}
			
			if(score2[9-i]->GetPosition().y<=6+i*2){
				score2[9-i]->SetLinearVelocity(b2Vec2(0,0));
			}
		}
		if(ball->GetPosition().x>=-32 && ball->GetPosition().x<=-30 &&
			ball->GetPosition().y>=14 && ball->GetPosition().y <=26){
				ball->SetTransform(b2Vec2(0,20),0);team2_score++;
				score_2(team2_score);
				if(team2_score==3){
					for(int i=0;i<10;i++){
						score1[i]->SetTransform(b2Vec2(-35.0f,6+2*i),0);
						score2[i]->SetTransform(b2Vec2(35.0f,34-2*i),0);
						score1[9-i]->SetLinearVelocity(b2Vec2(0,0));
						score2[9-i]->SetLinearVelocity(b2Vec2(0,0));
					}
				}
				//Move the score box
			}
	}

  dominos_t::dominos_t()
  {  
	//Base rectangle's
	{
		b2PolygonShape shape;
		b2BodyDef bd_base;
		bd_base.position.Set(0,20);
		b2Body* base = m_world->CreateBody(&bd_base);
		shape.SetAsBox(0.5,15.5,b2Vec2(-32,0),0.0f);
		base->CreateFixture(&shape,0.0f);
		shape.SetAsBox(0.5,15.5,b2Vec2(32,0),0.0f);
		base->CreateFixture(&shape,0.0f);
		shape.SetAsBox(32.5,0.5,b2Vec2(0,15),0.0f);
		base->CreateFixture(&shape,0.0f);
		shape.SetAsBox(32.5,0.5,b2Vec2(0,-15),0.0f);
		base->CreateFixture(&shape,0.0f);
	}
	
/////////////////////////////////////////////////////////////////////////////	
	
	{
		//b2PolygonShape rec1;
		//rec1.SetAsBox(32.0f,15.0f);
		//base->CreateFixture(&rec1,0.0f);
		b2BodyDef bd_base;
		bd_base.type = b2_kinematicBody;
		bd_base.position.Set(0.0f,20.0f);
		b2Body* base = m_world->CreateBody(&bd_base);
		b2PolygonShape lines;
		lines.SetAsBox(4.5f,6.0f,b2Vec2(-27.5f,0.0f),0.0f);
		b2FixtureDef *fd = new b2FixtureDef;
		fd->shape = &lines;
		fd->density = 0.0;
		fd->filter.maskBits = 0x0000;
		base->CreateFixture(fd);
		lines.SetAsBox(4.5f,6.0f,b2Vec2(27.5f,0.0f),0.0f);
		fd->shape = &lines;
		base->CreateFixture(fd);		
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	//Base circle
	{
		b2CircleShape cir;
		cir.m_radius=7;
		b2BodyDef bd_circle; 
		b2FixtureDef *fd = new b2FixtureDef;
		fd->shape = &cir;
		fd->density = 0.0;
		fd->filter.maskBits = 0x0000;
		bd_circle.type = b2_kinematicBody;
		bd_circle.position.Set(0.0f,20.0f);
		b2Body* circle=m_world->CreateBody(&bd_circle);
		circle->CreateFixture(fd);
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	//Ball
	{
		//b2Body* ball;
		b2CircleShape bal;
		bal.m_radius=0.6;
		b2BodyDef bd_ball;
		bd_ball.bullet=true;
		b2FixtureDef *fd = new b2FixtureDef;
		fd->shape = &bal;
		fd->density = 0.0;
		fd->restitution = 0.7f;
		bd_ball.type = b2_dynamicBody;
		bd_ball.position.Set(0.0f,20.0f);
		ball=m_world->CreateBody(&bd_ball);
		ball->CreateFixture(fd);
		ball->SetActive(true);
		//b2Vec2 force = b2Vec2(10,10);
		//ball->ApplyLinearImpulse(force, ball->GetPosition(),100);
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	//Players Team1
	b2Body* team1[11]; 
	b2PolygonShape player1[11];
	b2BodyDef bd_player1[11];
	{
		
		int x[11],y[11];
		x[0]=-25;y[0]=0;
		x[1]=-18;y[1]=5;
		x[2]=-18;y[2]=-5;
		x[3]=-4;y[3]=12;
		x[4]=-4;y[4]=6;
		x[5]=-4;y[5]=0;
		x[6]=-4;y[6]=-6;
		x[7]=-4;y[7]=-12;
		x[8]=11;y[8]=8;
		x[9]=11;y[9]=0;
		x[10]=11;y[10]=-8;
		for(int i=0;i<11;i++){
			bd_player1[i].position.Set(x[i],20.0f);
			team1[i] = m_world->CreateBody(&bd_player1[i]);
			player1[i].SetAsBox(0.8,1.2,b2Vec2(0.0f,y[i]),0.0f);
			team1[i]->CreateFixture(&player1[i],0.0f);
		}
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	//Players Team2
	b2Body* team2[11], *team2join[11]; 
	b2PolygonShape player2[11];
	b2BodyDef bd_player2[11];
	{
		int x[11],y[11];
		x[0]=25;y[0]=0;
		x[1]=18;y[1]=5;
		x[2]=18;y[2]=-5;
		x[3]=4;y[3]=12;
		x[4]=4;y[4]=6;
		x[5]=4;y[5]=0;
		x[6]=4;y[6]=-6;
		x[7]=4;y[7]=-12;
		x[8]=-11;y[8]=8;
		x[9]=-11;y[9]=0;
		x[10]=-11;y[10]=-8;
		for(int i=0;i<11;i++){
			bd_player2[i].position.Set(x[i],20.0f);
			team2join[i] = m_world->CreateBody(&bd_player2[i]);
			bd_player2[i].type=b2_dynamicBody;
			team2[i] = m_world->CreateBody(&bd_player2[i]);
			player2[i].SetAsBox(0.8,1.2,b2Vec2(0.0f,y[i]),0.0f);
			team2[i]->CreateFixture(&player2[i],0.0f);
		}

			 
		// Team 2 Rods

		for(int i=0;i<4;i++){
			b2PolygonShape rod1, constr;
			b2BodyDef bd_rod_1, bd_constr[4];
			b2Body * constraintBlock;
			bd_rod_1.type = b2_dynamicBody;
			
			float pos;
			if(i==0){
				pos=-11.0f;
			}
			else if(i==1){
				pos=4.0f;
			}
			else if(i==2){
				pos=18.0f;
			}
			else if(i==3){
			pos= 25.0f;
			}
			bd_rod_1.position.Set(pos,20.0f);
			bd_constr[0].position.Set(pos+0.8f,6.0f);
			bd_constr[1].position.Set(pos-0.8f,6.0f);
			bd_constr[2].position.Set(pos+0.8f,34.0f);
			bd_constr[3].position.Set(pos-0.8f,34.0f);
			
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &constr;
			fd->density = 0.0;
			fd->filter.categoryBits = 0x0002;
			fd->filter.maskBits = 0x0002;
			b2Body* con;
			for(int j=0;j<4;j++){
				constr.SetAsBox(0.4f,0.4f,b2Vec2(0.0f,0.0f),0.0f);
				bd_constr[j].type=b2_staticBody;
				con=m_world->CreateBody(&bd_constr[j]);
				con->CreateFixture(fd);
			}
			
			
			fd->shape = &rod1;
			rod1.SetAsBox(0.4f,18.0f,b2Vec2(0.0f,0.0f),0.0f);
			rod[i] = m_world->CreateBody(&bd_rod_1);
			rod[i]->CreateFixture(fd);
			rod1.SetAsBox(0.8f,3.0f,b2Vec2(0.0f,21.0f),0.0f);
			rod[i]->CreateFixture(&rod1,0.0f);
			rod1.SetAsBox(0.6f,0.2f,b2Vec2(0.0f,-18.3f),0.0f);
			rod[i]->CreateFixture(&rod1,0.0f);
		}
			b2PrismaticJointDef prismaticJointDef;
			  prismaticJointDef.bodyA = team2[0];
			  prismaticJointDef.bodyB = rod[3];
			  prismaticJointDef.collideConnected = false;
			  prismaticJointDef.localAxisA.Set(1,0);
			  prismaticJointDef.localAnchorA.Set( 0,0);
			  prismaticJointDef.localAnchorB.Set( 0,0);
			  prismaticJointDef.enableLimit = true;
			  prismaticJointDef.lowerTranslation = -2.0;
			  prismaticJointDef.upperTranslation = 2.0;
			  prismaticJointDef.enableMotor = true;
			  prismaticJointDef.maxMotorForce = 10000;
			  m_joint = (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );
			  
			/*  b2PrismaticJointDef prismaticJointRod;// 0,-15
			  prismaticJointDef.bodyA = team2[0];
			  prismaticJointDef.bodyB = rod[3];
			  prismaticJointDef.collideConnected = false;
			  prismaticJointDef.localAxisA.Set(1,0);
			  prismaticJointDef.localAnchorA.Set( 0,0);
			  prismaticJointDef.localAnchorB.Set( 0,0);
			  prismaticJointDef.enableLimit = true;
			  prismaticJointDef.lowerTranslation = -2.0;
			  prismaticJointDef.upperTranslation = 2.0;
			  prismaticJointDef.enableMotor = true;
			  prismaticJointDef.maxMotorForce = 10000;
			  m_joint = (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );*/
	}
	
/////////////////////////////////////////////////////////////////////////////
	
    //Rods team1
	{
		b2Body* rod;
		for(int i=0;i<4;i++){
			b2PolygonShape rod1;
			b2BodyDef bd_rod_1;
			bd_rod_1.type = b2_kinematicBody;
			if(i==0){
				bd_rod_1.position.Set(-25.0f,20.0f);
			}
			else if(i==1){
				bd_rod_1.position.Set(-18.0f,20.0f);
			}
			else if(i==2){
				bd_rod_1.position.Set(-4.0f,20.0f);
			}
			else if(i==3){
				bd_rod_1.position.Set(11.0f,20.0f);
			}
			rod = m_world->CreateBody(&bd_rod_1);
			rod1.SetAsBox(0.4f,18.0f,b2Vec2(0.0f,0.0f),0.0f);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &rod1;
			fd->density = 0.0;
			fd->filter.maskBits = 0x0000;
			rod->CreateFixture(fd);
			rod1.SetAsBox(0.8f,3.0f,b2Vec2(0.0f,-21.0f),0.0f);
			rod->CreateFixture(&rod1,0.0f);
		}
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	//Score team1
	{
		//b2Body* score1[10];
		b2PolygonShape shape[10];
		b2FixtureDef *fd = new b2FixtureDef;
		fd->restitution = 0;
		//b2BodyDef bd_score[10];
		for(int i=0;i<10;i++){
			shape[i].SetAsBox(1,1);	
			bd_score1[i].type = b2_dynamicBody;
			fd->shape = &shape[i];
			bd_score1[i].position.Set(-35.0f,6+2*i);
			score1[i]=m_world->CreateBody(&bd_score1[i]);
			score1[i]->CreateFixture(fd);
		}
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	//Score team2
	{
		//b2Body* score2[10];
		b2PolygonShape shape[10];
		//b2BodyDef bd_score[10];
		for(int i=0;i<10;i++){
			shape[i].SetAsBox(1,1);	
			bd_score2[i].type = b2_dynamicBody;
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &shape[i];
			fd->restitution = 0;
			bd_score2[i].position.Set(35.0f,34-2*i);
			score2[i]=m_world->CreateBody(&bd_score2[i]);
			score2[i]->CreateFixture(fd);
		}
	}
	
/////////////////////////////////////////////////////////////////////////////
	 
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

