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
//vector<float> v={-26.0,-19.0,-5.0,9.0};
	enum _entityCategory {
		BOUNDARY =          0x0001,
		FRIENDLY_SHIP =     0x0002,
		ENEMY_SHIP =        0x0004,
	};
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
	
	//Ball
	{
		b2Body* ball;
		b2CircleShape bal;
		bal.m_radius=1.2;
		b2BodyDef bd_ball;
		b2FixtureDef *fd = new b2FixtureDef;
		fd->shape = &bal;
		fd->density = 0.0;
		fd->restitution = 0.7f;
		bd_ball.type = b2_dynamicBody;
		bd_ball.position.Set(0.0f,20.0f);
		ball=m_world->CreateBody(&bd_ball);
		ball->CreateFixture(fd);
		ball->SetActive(true);
		b2Vec2 force = b2Vec2(10,10);
		ball->ApplyLinearImpulse(force, ball->GetPosition(),100);
	}
	//Players Team1
	b2Body* team1[11]; 
	b2PolygonShape player1[11];
	b2BodyDef bd_player1[11];
	{
		
		bd_player1[0].position.Set(-25.0f,20.0f);
		team1[0] = m_world->CreateBody(&bd_player1[0]);
		player1[0].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team1[0]->CreateFixture(&player1[0],0.0f);
		
		bd_player1[1].position.Set(-18.0f,20.0f);
		team1[1] = m_world->CreateBody(&bd_player1[1]);
		player1[1].SetAsBox(1,1.5,b2Vec2(0.0f,5.0f),0.0f);
		team1[1]->CreateFixture(&player1[1],0.0f);
		
		bd_player1[2].position.Set(-18.0f,20.0f);
		team1[2] = m_world->CreateBody(&bd_player1[2]);
		player1[2].SetAsBox(1,1.5,b2Vec2(0.0f,-5.0f),0.0f);
		team1[2]->CreateFixture(&player1[2],0.0f);
		
		bd_player1[3].position.Set(-4.0f,20.0f);
		team1[3] = m_world->CreateBody(&bd_player1[3]);
		player1[3].SetAsBox(1,1.5,b2Vec2(0.0f,12.0f),0.0f);
		team1[3]->CreateFixture(&player1[3],0.0f);
		
		bd_player1[4].position.Set(-4.0f,20.0f);
		team1[4] = m_world->CreateBody(&bd_player1[4]);
		player1[4].SetAsBox(1,1.5,b2Vec2(0.0f,6.0f),0.0f);
		team1[4]->CreateFixture(&player1[4],0.0f);
		
		bd_player1[5].position.Set(-4.0f,20.0f);
		team1[5] = m_world->CreateBody(&bd_player1[5]);
		player1[5].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team1[5]->CreateFixture(&player1[5],0.0f);
		
		bd_player1[6].position.Set(-4.0f,20.0f);
		team1[6] = m_world->CreateBody(&bd_player1[6]);
		player1[6].SetAsBox(1,1.5,b2Vec2(0.0f,-6.0f),0.0f);
		team1[6]->CreateFixture(&player1[6],0.0f);
		
		bd_player1[7].position.Set(-4.0f,20.0f);
		team1[7] = m_world->CreateBody(&bd_player1[7]);
		player1[7].SetAsBox(1,1.5,b2Vec2(0.0f,-12.0f),0.0f);
		team1[7]->CreateFixture(&player1[7],0.0f);
		
		bd_player1[8].position.Set(11.0f,20.0f);
		team1[8] = m_world->CreateBody(&bd_player1[8]);
		player1[8].SetAsBox(1,1.5,b2Vec2(0.0f,8.0f),0.0f);
		team1[8]->CreateFixture(&player1[8],0.0f);
		
		bd_player1[9].position.Set(11.0f,20.0f);
		team1[9] = m_world->CreateBody(&bd_player1[9]);
		player1[9].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team1[9]->CreateFixture(&player1[9],0.0f);
		
		bd_player1[10].position.Set(11.0f,20.0f);
		team1[10] = m_world->CreateBody(&bd_player1[10]);
		player1[10].SetAsBox(1,1.5,b2Vec2(0.0f,-8.0f),0.0f);
		team1[10]->CreateFixture(&player1[10],0.0f);
		
		
	}
	
	//Players Team2
	b2Body* team2[11]; 
	b2PolygonShape player2[11];
	b2BodyDef bd_player2[11];
	{
		
		bd_player2[0].position.Set(25.0f,20.0f);
		team2[0] = m_world->CreateBody(&bd_player2[0]);
		player2[0].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team2[0]->CreateFixture(&player2[0],0.0f);
		
		bd_player2[1].position.Set(18.0f,20.0f);
		team2[1] = m_world->CreateBody(&bd_player2[1]);
		player2[1].SetAsBox(1,1.5,b2Vec2(0.0f,5.0f),0.0f);
		team2[1]->CreateFixture(&player2[1],0.0f);
		
		bd_player2[2].position.Set(18.0f,20.0f);
		team2[2] = m_world->CreateBody(&bd_player2[2]);
		player2[2].SetAsBox(1,1.5,b2Vec2(0.0f,-5.0f),0.0f);
		team2[2]->CreateFixture(&player2[2],0.0f);
		
		bd_player2[3].position.Set(4.0f,20.0f);
		team2[3] = m_world->CreateBody(&bd_player2[3]);
		player2[3].SetAsBox(1,1.5,b2Vec2(0.0f,12.0f),0.0f);
		team2[3]->CreateFixture(&player2[3],0.0f);
		
		bd_player2[4].position.Set(4.0f,20.0f);
		team2[4] = m_world->CreateBody(&bd_player2[4]);
		player2[4].SetAsBox(1,1.5,b2Vec2(0.0f,6.0f),0.0f);
		team2[4]->CreateFixture(&player2[4],0.0f);
		
		bd_player2[5].position.Set(4.0f,20.0f);
		team2[5] = m_world->CreateBody(&bd_player2[5]);
		player2[5].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team2[5]->CreateFixture(&player2[5],0.0f);
		
		bd_player2[6].position.Set(4.0f,20.0f);
		team2[6] = m_world->CreateBody(&bd_player2[6]);
		player2[6].SetAsBox(1,1.5,b2Vec2(0.0f,-6.0f),0.0f);
		team2[6]->CreateFixture(&player2[6],0.0f);
		
		bd_player2[7].position.Set(4.0f,20.0f);
		team2[7] = m_world->CreateBody(&bd_player2[7]);
		player2[7].SetAsBox(1,1.5,b2Vec2(0.0f,-12.0f),0.0f);
		team2[7]->CreateFixture(&player2[7],0.0f);
		
		bd_player2[8].position.Set(-11.0f,20.0f);
		team2[8] = m_world->CreateBody(&bd_player2[8]);
		player2[8].SetAsBox(1,1.5,b2Vec2(0.0f,8.0f),0.0f);
		team2[8]->CreateFixture(&player2[8],0.0f);
		
		bd_player2[9].position.Set(-11.0f,20.0f);
		team2[9] = m_world->CreateBody(&bd_player2[9]);
		player2[9].SetAsBox(1,1.5,b2Vec2(0.0f,0.0f),0.0f);
		team2[9]->CreateFixture(&player2[9],0.0f);
		
		bd_player2[10].position.Set(-11.0f,20.0f);
		team2[10] = m_world->CreateBody(&bd_player2[10]);
		player2[10].SetAsBox(1,1.5,b2Vec2(0.0f,-8.0f),0.0f);
		team2[10]->CreateFixture(&player2[10],0.0f);
		
		
	}
	
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
	//Rods team2
	
	{
		b2Body* rod;
		for(int i=0;i<4;i++){
			b2PolygonShape rod1;
			b2BodyDef bd_rod_1;
			bd_rod_1.type = b2_kinematicBody;
			if(i==0){
				bd_rod_1.position.Set(-11.0f,20.0f);
			}
			else if(i==1){
				bd_rod_1.position.Set(4.0f,20.0f);
			}
			else if(i==2){
				bd_rod_1.position.Set(18.0f,20.0f);
			}
			else if(i==3){
				bd_rod_1.position.Set(25.0f,20.0f);
			}
			rod = m_world->CreateBody(&bd_rod_1);
			rod1.SetAsBox(0.4f,18.0f,b2Vec2(0.0f,0.0f),0.0f);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &rod1;
			fd->density = 0.0;
			fd->filter.maskBits = 0x0000;
			rod->CreateFixture(fd);
			rod1.SetAsBox(0.8f,3.0f,b2Vec2(0.0f,21.0f),0.0f);
			rod->CreateFixture(&rod1,0.0f);
		}
	}
	
	{
		b2Body* player;
		b2PolygonShape player1;
		player1.SetAsBox(4,4);
		b2BodyDef bd_player;
		bd_player.position.Set(0.0f,50.0f);
		player=m_world->CreateBody(&bd_player);
		player->CreateFixture(&player1,0.0f);
		for(int i=0;i<10000000;i++){};
		for(int i=0;i<30;i++){
			//player->GetWorld()->DestroyBody(player);
			b2Body* player;
			b2PolygonShape player1;
			player1.SetAsBox(i,4);
			b2BodyDef bd_player;
			bd_player.position.Set(0,50.0f);
			player=m_world->CreateBody(&bd_player);
			player->CreateFixture(&player1,0.0f);
		}
	}
	//Score team1
	{
		b2Body* score1[10];
		b2PolygonShape shape[10];
		b2BodyDef bd_score[10];
		for(int i=0;i<10;i++){
			shape[i].SetAsBox(1,1);	
			bd_score[i].position.Set(-35.0f,33.5-3*i);
			score1[i]=m_world->CreateBody(&bd_score[i]);
			score1[i]->CreateFixture(&shape[i],0.0f);
		}
	}
	//Score team2
	{
		b2Body* score2[10];
		b2PolygonShape shape[10];
		b2BodyDef bd_score[10];
		for(int i=0;i<10;i++){
			shape[i].SetAsBox(1,1);	
			bd_score[i].position.Set(35.0f,33.5-3*i);
			score2[i]=m_world->CreateBody(&bd_score[i]);
			score2[i]->CreateFixture(&shape[i],0.0f);
		}
	}
	 
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
