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
#include <cmath>


namespace cs296
{
  	int team1_score=-1,team2_score=-1;
	b2Body* ball;
	b2Body* rod2[4], * rod1[4];
	int range[4][2]={{8,10},{4,8},{1,4},{0,1}}; ///< Range of players for each rod
	b2Body* score1[10];///< Blocks that show the score
	b2Body* score2[10];
	b2BodyDef bd_score1[10];
	b2BodyDef bd_score2[10];
	b2Body* team1[11];///< Players Team1
	b2Body* team2[11];///< Players Team2
	b2BodyDef bd_player1[11];
	b2BodyDef bd_player2[11];
	b2Body* active2, *active1;///Define Active rod for players
	b2Body* pointer1, * pointer2;///We define pointers to the current active rod
	int key_pressed;
	/**Handle keyboard inputs*/
		void dominos_t::keyboard(unsigned char key){
			std::cout<<key<<endl;
			int mul=6;
			switch(key){
			///Team 2
			case'e': 
				rod_2_index=(rod_2_index+1)%4;///rod_2_index tells which rod is active
				active2=rod2[rod_2_index];/// Keypress e: Shift active rod one position right, set pointer accordingly
				pointer2->SetTransform(b2Vec2(active2->GetPosition().x,-4),0);
				break;
			case'q': 
				rod_2_index=(rod_2_index+3)%4;///Keypress q: Shift active rod one position left, set pointer accordingly
				active2=rod2[rod_2_index];
				pointer2->SetTransform(b2Vec2(active2->GetPosition().x,-4),0);
				break;
			case 'w':///Keypress w: Pushes the active rod upwards
				active2->ApplyLinearImpulse(b2Vec2(0,100),active2->GetPosition(),100);
				break;
			case 's':///Keypress s: Pushes the active rod downwards
				active2->ApplyLinearImpulse(b2Vec2(0,-100),active2->GetPosition(),100);
				break;
			case'1':///Keypress 1:Stops the rod 
				active2->SetLinearVelocity(b2Vec2(0,0));
				break;
			case 'a':///Keypress a: Rotates the player towards left,if the player is already to the left and v is pressed then the player get lifted
				for(int i=range[rod_2_index][0];i<range[rod_2_index][1];i++){
					b2Body *bod= m_joint_2[i]->GetBodyA();
					b2Vec2 v1=m_joint_2[i]->GetAnchorB();
					b2Vec2 v2=m_joint_2[i]->GetAnchorA();
					b2Fixture* origFix=bod->GetFixtureList();
					cout<<v1.x<<" "<<v2.x<<" "<<v1.x-v2.x<<endl;
					if(v1.x-v2.x > 1.3){///We check if player is far left
						
						b2FixtureDef *fd = new b2FixtureDef;/// if so, we make player transparent
						b2PolygonShape player2;
						int x=team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x;x=x/3;
						b2Vec2 vertices[4];/// Create a new fixture for player based on his position.
						if(x>0){
							vertices[0].Set(-x-0.5,1.1);
							vertices[1].Set(-x-0.5,-1.1);
							vertices[2].Set(x+0.5,1.1-(x/2));
							vertices[3].Set(x+0.5,-1.1+(x/2));
						}
						else {
							vertices[0].Set(x-0.5,1.1-(-x/2));
							vertices[1].Set(x-0.5,-1.1+(-x/2));
							vertices[2].Set(-x+0.5,1.1);
							vertices[3].Set(-x+0.5,-1.1);
						}		
						player2.Set(vertices,4);
						//player2.SetAsBox(1+abs(team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
						fd->shape = &player2;
						fd->density = 0.5f;
						fd->filter.maskBits = 0x0000;
						bod->DestroyFixture(origFix);
						bod->CreateFixture(fd);
						//filt.maskBits=0x0000;//also change fixture here
					}
					else{ 
						//cout<<"Hari"<<endl;
						//if(origFix->GetFilterData().maskBits == 0x0000 ){/// We check if player is in transparent state
							b2FixtureDef *fd = new b2FixtureDef;/// if so, we change fixture accordingly
							b2PolygonShape player2;
							int x=team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x;
							x=x/3;
							b2Vec2 vertices[4];
							if(x>0){
								vertices[0].Set(-x-0.5,1.1);
								vertices[1].Set(-x-0.5,-1.1);
								vertices[2].Set(x+0.5,1.1-(x/2));
								vertices[3].Set(x+0.5,-1.1+(x/2));
							}
							else {
								vertices[0].Set(x-0.5,1.1-(-x/2));
								vertices[1].Set(x-0.5,-1.1+(-x/2));
								vertices[2].Set(-x+0.5,1.1);
								vertices[3].Set(-x+0.5,-1.1);
							}		
							player2.Set(vertices,4);
							//player2.SetAsBox(1+abs(team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
							fd->shape = &player2;
							fd->density = 0.5f;
							fd->filter.maskBits = 0xFFFF;
							bod->DestroyFixture(origFix);
							bod->CreateFixture(fd);
						/*}			
						else{
							b2Filter filt=bod->GetFixtureList()->GetFilterData();
							filt.maskBits=0xFFFF;
							bod->GetFixtureList()->SetFilterData(filt);
						}*/
					}
					m_joint_2[i]->SetMotorSpeed(mul*(2* abs(m_joint_2[i]->GetAnchorB().x - m_joint_2[i]->GetAnchorA().x)+.5));
					/// Rotate the player with speed proportional to amount of backlift(i.e. distance from final position)
				}
				break;
			case 'd':///Keypress d: Rotates the player towards right,if the player is already to the right and n is pressed then the player get lifted
				for(int i=range[rod_2_index][0];i<range[rod_2_index][1];i++){
					b2Body *bod= m_joint_2[i]->GetBodyA();
					b2Vec2 v1=m_joint_2[i]->GetAnchorB();
					b2Vec2 v2=m_joint_2[i]->GetAnchorA();
					b2Fixture* origFix=bod->GetFixtureList();
					cout<<v1.x<<" "<<v2.x<<" "<<v1.x-v2.x<<endl;
					if(v1.x-v2.x < -1.3){///We check if player is far right
						b2FixtureDef *fd = new b2FixtureDef;///< If so, we create a new fixture
						b2PolygonShape player2;
						int x=team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x;x=x/3;
						b2Vec2 vertices[4];
						if(x>0){
							vertices[0].Set(-x-0.5,1.1);
							vertices[1].Set(-x-0.5,-1.1);
							vertices[2].Set(x+0.5,1.1-(x/2));
							vertices[3].Set(x+0.5,-1.1+(x/2));
						}
						else {
							vertices[0].Set(x-0.5,1.1-(-x/2));
							vertices[1].Set(x-0.5,-1.1+(-x/2));
							vertices[2].Set(-x+0.5,1.1);
							vertices[3].Set(-x+0.5,-1.1);
						}
						player2.Set(vertices,4);
						//player2.SetAsBox(1+abs(team2[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
						fd->shape = &player2;
						fd->density = 0.5f;
						fd->filter.maskBits = 0x0000;
						bod->DestroyFixture(origFix);
						bod->CreateFixture(fd);
					}
					else{ 
						//if(origFix->GetFilterData().maskBits == 0x0000 ){/// in transparent state
							b2FixtureDef *fd = new b2FixtureDef;
							b2PolygonShape player2;
							int x=team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x;x=x/3;
							b2Vec2 vertices[4];
							if(x>0){
								vertices[0].Set(-x-0.5,1.1);
								vertices[1].Set(-x-0.5,-1.1);
								vertices[2].Set(x+0.5,1.1-(x/2));
								vertices[3].Set(x+0.5,-1.1+(x/2));
							}
							else {
								vertices[0].Set(x-0.5,1.1-(-x/2));
								vertices[1].Set(x-0.5,-1.1+(-x/2));
								vertices[2].Set(-x+0.5,1.1);
								vertices[3].Set(-x+0.5,-1.1);
							}							
							player2.Set(vertices,4);
							//player2.SetAsBox(1+abs(team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
							fd->shape = &player2;
							fd->density = 0.5f;
							fd->filter.maskBits = 0xFFFF;
							bod->DestroyFixture(origFix);
							bod->CreateFixture(fd);
						/*}			
						else{
							b2Filter filt=bod->GetFixtureList()->GetFilterData();
							filt.maskBits=0xFFFF;
							bod->GetFixtureList()->SetFilterData(filt);
						}*/
					}
					/// If not far right, go for a shot!
					m_joint_2[i]->SetMotorSpeed(mul*(-2*abs(m_joint_2[i]->GetAnchorA().x - m_joint_2[i]->GetAnchorB().x) -.5));
				}
				break;
			case '2':
				for(int i=range[rod_2_index][0];i<range[rod_2_index][1];i++)
					m_joint_2[i]->SetMotorSpeed(0);
				break;
			/////////////////////////////////////////////////////////////////////////////
			///Team 1
			case'y':
				rod_1_index=(rod_1_index+1)%4;
				active1=rod1[rod_1_index];
				pointer1->SetTransform(b2Vec2(active1->GetPosition().x,45),0);
				break;
			case'i':
				rod_1_index=(rod_1_index+3)%4;
				active1=rod1[rod_1_index];
				pointer1->SetTransform(b2Vec2(active1->GetPosition().x,45),0);
				break;
			case 'u':
				active1->ApplyLinearImpulse(b2Vec2(0,100),active1->GetPosition(),100);
				break;
			case 'n':
				active1->ApplyLinearImpulse(b2Vec2(0,-100),active1->GetPosition(),100);
				break;
			case 'j':
				active1->SetLinearVelocity(b2Vec2(0,0));
				break;
			case 'h':///Keypress a: Rotates the player towards left,if the player is already to the left and v is pressed then the player get lifted
				for(int i=range[rod_1_index][0];i<range[rod_1_index][1];i++){
					b2Body *bod= m_joint_1[i]->GetBodyA();
					b2Vec2 v1=m_joint_1[i]->GetAnchorB();
					b2Vec2 v2=m_joint_1[i]->GetAnchorA();
					b2Fixture* origFix=bod->GetFixtureList();
					cout<<v1.x<<" "<<v2.x<<" "<<v1.x-v2.x<<endl;
					if(v1.x-v2.x > 1.3){///We check if player is far left
						
						b2FixtureDef *fd = new b2FixtureDef;/// if so, we make player transparent
						b2PolygonShape player1;
						int x=team2[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x;x=x/3;
						b2Vec2 vertices[4];
						if(x>0){
							vertices[0].Set(-x-0.5,1.1);
							vertices[1].Set(-x-0.5,-1.1);
							vertices[2].Set(x+0.5,1.1-(x/2));
							vertices[3].Set(x+0.5,-1.1+(x/2));
						}
						else {
							vertices[0].Set(x-0.5,1.1-(-x/2));
							vertices[1].Set(x-0.5,-1.1+(-x/2));
							vertices[2].Set(-x+0.5,1.1);
							vertices[3].Set(-x+0.5,-1.1);
						}		
						player1.Set(vertices,4);
						//player1.SetAsBox(1+abs(team2[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
						fd->shape = &player1;
						fd->density = 0.5f;
						fd->filter.maskBits = 0x0000;
						bod->DestroyFixture(origFix);
						bod->CreateFixture(fd);
						//filt.maskBits=0x0000;//also change fixture here
					}
					else{ 
						//cout<<"Hari"<<endl;
						//if(origFix->GetFilterData().maskBits == 0x0000 ){/// We check if player is in transparent state
							b2FixtureDef *fd = new b2FixtureDef;/// if so, we change fixture accordingly
							b2PolygonShape player1;
							int x=team2[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x;
							x=x/3;
							b2Vec2 vertices[4];
							if(x>0){
								vertices[0].Set(-x-0.5,1.1);
								vertices[1].Set(-x-0.5,-1.1);
								vertices[2].Set(x+0.5,1.1-(x/2));
								vertices[3].Set(x+0.5,-1.1+(x/2));
							}
							else {
								vertices[0].Set(x-0.5,1.1-(-x/2));
								vertices[1].Set(x-0.5,-1.1+(-x/2));
								vertices[2].Set(-x+0.5,1.1);
								vertices[3].Set(-x+0.5,-1.1);
							}		
							player1.Set(vertices,4);
							//player1.SetAsBox(1+abs(team2[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
							fd->shape = &player1;
							fd->density = 0.5f;
							fd->filter.maskBits = 0xFFFF;
							bod->DestroyFixture(origFix);
							bod->CreateFixture(fd);
						/*}			
						else{
							b2Filter filt=bod->GetFixtureList()->GetFilterData();
							filt.maskBits=0xFFFF;
							bod->GetFixtureList()->SetFilterData(filt);
						}*/
					}
					m_joint_1[i]->SetMotorSpeed(mul*(2* abs(m_joint_1[i]->GetAnchorB().x - m_joint_1[i]->GetAnchorA().x)+.5));
				}
				break;
			case 'k':///Keypress j: Rotates the player towards right,if the player is already to the right and n is pressed then the player get lifted
				for(int i=range[rod_1_index][0];i<range[rod_1_index][1];i++){
					b2Body *bod= m_joint_1[i]->GetBodyA();
					b2Vec2 v1=m_joint_1[i]->GetAnchorB();
					b2Vec2 v2=m_joint_1[i]->GetAnchorA();
					b2Fixture* origFix=bod->GetFixtureList();
					cout<<v1.x<<" "<<v2.x<<" "<<v1.x-v2.x<<endl;
					if(v1.x-v2.x < -1.3){///We check if player is far right
						b2FixtureDef *fd = new b2FixtureDef;///< If so, we create a new fixture
						b2PolygonShape player1;
						int x=team1[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x;x=x/3;
						b2Vec2 vertices[4];
						if(x>0){
							vertices[0].Set(-x-0.5,1.1);
							vertices[1].Set(-x-0.5,-1.1);
							vertices[2].Set(x+0.5,1.1-(x/2));
							vertices[3].Set(x+0.5,-1.1+(x/2));
						}
						else {
							vertices[0].Set(x-0.5,1.1-(-x/2));
							vertices[1].Set(x-0.5,-1.1+(-x/2));
							vertices[2].Set(-x+0.5,1.1);
							vertices[3].Set(-x+0.5,-1.1);
						}
						player1.Set(vertices,4);
						//player1.SetAsBox(1+abs(team1[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
						fd->shape = &player1;
						fd->density = 0.5f;
						fd->filter.maskBits = 0x0000;
						bod->DestroyFixture(origFix);
						bod->CreateFixture(fd);
					}
					else{ 
						//if(origFix->GetFilterData().maskBits == 0x0000 ){/// in transparent state
							b2FixtureDef *fd = new b2FixtureDef;
							b2PolygonShape player1;
							int x=team1[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x;x=x/3;
							b2Vec2 vertices[4];
							if(x>0){
								vertices[0].Set(-x-0.5,1.1);
								vertices[1].Set(-x-0.5,-1.1);
								vertices[2].Set(x+0.5,1.1-(x/2));
								vertices[3].Set(x+0.5,-1.1+(x/2));
							}
							else {
								vertices[0].Set(x-0.5,1.1-(-x/2));
								vertices[1].Set(x-0.5,-1.1+(-x/2));
								vertices[2].Set(-x+0.5,1.1);
								vertices[3].Set(-x+0.5,-1.1);
							}							
							player1.Set(vertices,4);
							//player1.SetAsBox(1+abs(team1[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x)/2.2,1.1);
							fd->shape = &player1;
							fd->density = 0.5f;
							fd->filter.maskBits = 0xFFFF;
							bod->DestroyFixture(origFix);
							bod->CreateFixture(fd);
						/*}			
						else{
							b2Filter filt=bod->GetFixtureList()->GetFilterData();
							filt.maskBits=0xFFFF;
							bod->GetFixtureList()->SetFilterData(filt);
						}*/
					}
					/// If not far right, go for a shot!
					m_joint_1[i]->SetMotorSpeed(mul*(-2*abs(m_joint_1[i]->GetAnchorA().x - m_joint_1[i]->GetAnchorB().x) -.5));
				}
				break;
			case 'm':
				for(int i=range[rod_1_index][0];i<range[rod_1_index][1];i++)
				m_joint_1[i]->SetMotorSpeed(0);
				break;
			///////////////////////////////////////////////////////////////////////////////////////////////////
		      /*  case '[':
				ball->ApplyLinearImpulse(b2Vec2(0,10),ball->GetPosition(),100);
				break;
			case '\'':
				ball->ApplyLinearImpulse(b2Vec2(0,-10),ball->GetPosition(),100);
				break;
			case ';':
				ball->ApplyLinearImpulse(b2Vec2(-10,0),ball->GetPosition(),100);
				break;
			case '/':
				ball->ApplyLinearImpulse(b2Vec2(10,0),ball->GetPosition(),100);
				break;*/
			///////////////////////////////////////////////////////////////////////////////////////////////////
			default:
				break;
		}
	}
	/// First team's score
	void dominos_t::score_1(int i){
		if(i!=-1){
			score1[9-i]->SetLinearVelocity(b2Vec2(0,10));
		}
	}
	/// Second team's score
	void dominos_t::score_2(int j){
		if(j!=-1){
			score2[9-j]->SetLinearVelocity(b2Vec2(0,-10));
		}
	}
	/// Check if someone has scored
	void dominos_t::check(void){
		///To change the fixture of the player depending on the position of the player
		///Team1
		for(int i=0;i<10;i++){
			b2Fixture* origFix=team1[i]->GetFixtureList();
			b2PolygonShape newShape;
			b2Vec2 vertices[4];
			float x=team1[i]->GetPosition().x-m_joint_1[i]->GetBodyB()->GetPosition().x;x=x/3;
			if(x>0){
				vertices[0].Set(-x-0.5,1.1);
				vertices[1].Set(-x-0.5,-1.1);
				vertices[2].Set(x+0.5,1.1-(x/2));
				vertices[3].Set(x+0.5,-1.1+(x/2));
			}
			else {
				vertices[0].Set(x-0.5,1.1-(-x/2));
				vertices[1].Set(x-0.5,-1.1+(-x/2));
				vertices[2].Set(-x+0.5,1.1);
				vertices[3].Set(-x+0.5,-1.1);
			}
			newShape.Set(vertices,4);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &newShape;
			fd->density = 0.5f;
			fd->filter.maskBits = origFix->GetFilterData().maskBits;
			team1[i]->DestroyFixture(origFix);
			team1[i]->CreateFixture(fd);
		}	
		///Team2
		for(int i=0;i<10;i++){
			b2Fixture* origFix=team2[i]->GetFixtureList();
			b2PolygonShape newShape;
			b2Vec2 vertices[4];
			float x=team2[i]->GetPosition().x-m_joint_2[i]->GetBodyB()->GetPosition().x;x=x/3;
			if(x>0){
				vertices[0].Set(-x-0.5,1.1);
				vertices[1].Set(-x-0.5,-1.1);
				vertices[2].Set(x+0.5,1.1-(x/2));
				vertices[3].Set(x+0.5,-1.1+(x/2));
			}
			else {
				vertices[0].Set(x-0.5,1.1-(-x/2));
				vertices[1].Set(x-0.5,-1.1+(-x/2));
				vertices[2].Set(-x+0.5,1.1);
				vertices[3].Set(-x+0.5,-1.1);
			}
			newShape.Set(vertices,4);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &newShape;
			fd->density = 0.5f;			
			fd->filter.maskBits = origFix->GetFilterData().maskBits;
			team2[i]->DestroyFixture(origFix);
			team2[i]->CreateFixture(fd);
			
		}
		///To check if ball has reached the goal 	
			
		if(ball->GetPosition().x<=32 && ball->GetPosition().x>=30 &&
			ball->GetPosition().y>=14 && ball->GetPosition().y <=26){
			ball->SetTransform(b2Vec2(0,20),0);team1_score++;
			ball->SetLinearVelocity(b2Vec2(0,0));
			score_1(team1_score);
			if(team1_score==10){/// Reset game if someone has won
			keyboard('r');
				for(int i=0;i<10;i++){
					score1[i]->SetTransform(b2Vec2(-35.0f,6+2.2*i),0);
					score2[i]->SetTransform(b2Vec2(35.0f,34-2*i),0);
					score1[9-i]->SetLinearVelocity(b2Vec2(0,0));
					score2[9-i]->SetLinearVelocity(b2Vec2(0,0));
				}
			}
		}
		for(int i=0;i<10;i++){
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
			ball->SetLinearVelocity(b2Vec2(0,0));
			score_2(team2_score);
			if(team2_score==10){
			keyboard('r');/// Reset game if someone has won
				for(int i=0;i<10;i++){
					score1[i]->SetTransform(b2Vec2(-35.0f,6+2*i),0);
					score2[i]->SetTransform(b2Vec2(35.0f,34-2*i),0);
					score1[9-i]->SetLinearVelocity(b2Vec2(0,0));
					score2[9-i]->SetLinearVelocity(b2Vec2(0,0));
				}
			}
		}
	}

  dominos_t::dominos_t()
  {  
	rod_1_index=0;
	rod_2_index=0;

	/// We define the bodies for :
	///1. Base rectangles
	b2Body* base;
	{
		b2PolygonShape shape;
		b2BodyDef bd_base;
		bd_base.position.Set(0,20);
		base = m_world->CreateBody(&bd_base);
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
	///Base lines 
	{
	
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
	
	///2. Base circle
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
	
	///3. Ball
	{
		b2CircleShape bal;
		bal.m_radius=0.8;
		b2BodyDef bd_ball;
		bd_ball.bullet=true;/// Ball has numerous collisions at high speed, and is therefore a bullet object.
		b2FixtureDef *fd = new b2FixtureDef;
		fd->shape = &bal;
		fd->density = 0.1f;
		fd->restitution = 0.8f;
		bd_ball.type = b2_dynamicBody;
		bd_ball.position.Set(0.0f,20.0f);
		ball=m_world->CreateBody(&bd_ball);
		ball->CreateFixture(fd);
		ball->SetActive(true);
	}
	
/////////////////////////////////////////////////////////////////////////////
	
	b2PolygonShape player1;
	
		
/////////////////////////////////////////////////////////////////////////////
	
	b2PolygonShape player2;
	
	{
		///4. Team 1 and Team 2 Rods

		for(int i=0;i<4;i++){
			b2PolygonShape rodShape, constr;
			b2BodyDef bd_rodShape1,bd_rodShape2, bd_constr2[4], bd_constr1[4];
			b2Body * constraintBlock;
			bd_rodShape1.type = b2_dynamicBody;
			bd_rodShape2.type = b2_dynamicBody;
			/// We set positions of rods symmetrically for both teams
			float pos2,pos1;
			if(i==0){
				pos2=-18.0f;
			}
			else if(i==1){
				pos2=-4.0f;
			}
			else if(i==2){
				pos2=11.0f;
			}
			else if(i==3){
				pos2= 25.0f;
			}
			pos1= -1*pos2;///Player 1's rods are mirror images of Player 2's rods.
			bd_rodShape1.position.Set(pos1,20.0f);
			bd_rodShape2.position.Set(pos2,20.0f);
			
			bd_constr1[0].position.Set(pos1+0.9f,6.0f);
			bd_constr1[1].position.Set(pos1-0.9f,6.0f);
			bd_constr1[2].position.Set(pos1+0.9f,34.0f);
			bd_constr1[3].position.Set(pos1-0.9f,34.0f);
			
			bd_constr2[0].position.Set(pos2+0.9f,6.0f);
			bd_constr2[1].position.Set(pos2-0.9f,6.0f);
			bd_constr2[2].position.Set(pos2+0.9f,34.0f);
			bd_constr2[3].position.Set(pos2-0.9f,34.0f);
			
			b2FixtureDef *fd = new b2FixtureDef;
			fd->shape = &constr;
			fd->density = 0.0;
			fd->filter.categoryBits = 0x0002;
			fd->filter.maskBits = 0x0002;
			b2Body* con;
			for(int j=0;j<4;j++){
				constr.SetAsBox(0.4f,0.4f,b2Vec2(0.0f,0.0f),0.0f);
				bd_constr2[j].type=b2_staticBody;
				bd_constr1[j].type=b2_staticBody;
				con=m_world->CreateBody(&bd_constr2[j]);
				con->CreateFixture(fd);
				con=m_world->CreateBody(&bd_constr1[j]);
				con->CreateFixture(fd);
			}
			fd->shape = &rodShape;
			rodShape.SetAsBox(0.4f,18.0f,b2Vec2(0.0f,0.0f),0.0f);
			
			fd->density = 0.5f;
			
			rod2[i] = m_world->CreateBody(&bd_rodShape2);
			rod2[i]->CreateFixture(fd);
			
			rod1[i] = m_world->CreateBody(&bd_rodShape1);
			rod1[i]->CreateFixture(fd);
			
			rodShape.SetAsBox(0.8f,3.0f,b2Vec2(0.0f,21.0f),0.0f);
			rod2[i]->CreateFixture(&rodShape,0.0f);
			rodShape.SetAsBox(0.8f,3.0f,b2Vec2(0.0f,-21.0f),0.0f);
			rod1[i]->CreateFixture(&rodShape,0.0f);
			
			rodShape.SetAsBox(0.6f,0.2f,b2Vec2(0.0f,-18.3f),0.0f);
			rod2[i]->CreateFixture(&rodShape,0.0f);
			rodShape.SetAsBox(0.6f,0.2f,b2Vec2(0.0f,18.3f),0.0f);
			rod1[i]->CreateFixture(&rodShape,0.0f);
		}		
	}
/////////////////////////////////////////////////////////////////////////////
	/// 5. To set Players
	///a. Team 1
	{
		player1.SetAsBox(0.5,1.1,b2Vec2(0.0f,0.0f),0.0f);
		
		///Rod 1		
		bd_player1[0].position.Set(-25.0f,20.0f);
		
		///Rod 2
		bd_player1[1].position.Set(-11.0f,28.0f);

		bd_player1[2].position.Set(-11.0f,20.0f);
	
		bd_player1[3].position.Set(-11.0f,12.0f);
		//Rod 3
		bd_player1[4].position.Set(4.0f,31.0f);
	
		bd_player1[5].position.Set(4.0f,24.0f);
		
		bd_player1[6].position.Set(4.0f,17.0f);
	
		bd_player1[7].position.Set(4.0f,10.0f);
		//Rod 4
		bd_player1[8].position.Set(18.0f,25.0f);
	
		bd_player1[9].position.Set(18.0f,15.0f);

		int j=3;
		b2Body* active_rod;
		for( int i=0;i<10;i++){
			if(i==1 || i==4 || i==8)
				j--;
					  
			bd_player1[i].type=b2_dynamicBody;
			team1[i] = m_world->CreateBody(&bd_player1[i]);
			team1[i]->CreateFixture(&player1,0.0f);	

			b2PrismaticJointDef prismaticJointDef;		///We define joints for all these players
			prismaticJointDef.bodyA = team1[i];
			prismaticJointDef.bodyB = rod1[j];
			prismaticJointDef.collideConnected = false;
			prismaticJointDef.localAxisA.Set(1,0);
			prismaticJointDef.localAnchorA.Set( 0,0);
			prismaticJointDef.localAnchorB.Set( 0,0 - rod1[j]->GetPosition().y+ team1[i]->GetPosition().y);
			prismaticJointDef.enableLimit = true;
			prismaticJointDef.lowerTranslation = -2.0;
			prismaticJointDef.upperTranslation = 2.0;
			prismaticJointDef.enableMotor = true;
			prismaticJointDef.maxMotorForce = 10000;
			m_joint_1[i] = (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );
		}
/////////////////////////////////////////////////////////////////////////////

		///b. Team 2	
		player2.SetAsBox(0.5,1.1,b2Vec2(0.0f,0.0f),0.0f);
		
		///Rod 1		
		bd_player2[0].position.Set(25.0f,20.0f);
		
		///Rod 2
		bd_player2[1].position.Set(11.0f,28.0f);

		bd_player2[2].position.Set(11.0f,20.0f);
	
		bd_player2[3].position.Set(11.0f,12.0f);
		//Rod 3
		bd_player2[4].position.Set(-4.0f,31.0f);
	
		bd_player2[5].position.Set(-4.0f,24.0f);
		
		bd_player2[6].position.Set(-4.0f,17.0f);
	
		bd_player2[7].position.Set(-4.0f,10.0f);
		//Rod 4
		bd_player2[8].position.Set(-18.0f,25.0f);
	
		bd_player2[9].position.Set(-18.0f,15.0f);
	
		j=3;
		for( int i=0;i<10;i++){
			if(i==1 || i==4 || i==8)
				j--;
					  
			bd_player2[i].type=b2_dynamicBody;
			team2[i] = m_world->CreateBody(&bd_player2[i]);
			team2[i]->CreateFixture(&player2,0.0f);	
			///We define joints for all these players
			b2PrismaticJointDef prismaticJointDef;
			prismaticJointDef.bodyA = team2[i];
			prismaticJointDef.bodyB = rod2[j];
			prismaticJointDef.collideConnected = false;
			prismaticJointDef.localAxisA.Set(1,0);
			prismaticJointDef.localAnchorA.Set( 0,0);
			prismaticJointDef.localAnchorB.Set( 0,0 - rod2[j]->GetPosition().y+ team2[i]->GetPosition().y);
			prismaticJointDef.enableLimit = true;
			prismaticJointDef.lowerTranslation = -2.0;
			prismaticJointDef.upperTranslation = 2.0;
			prismaticJointDef.enableMotor = true;
			prismaticJointDef.maxMotorForce = 10000;
			m_joint_2[i] = (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );
			
	/// We set active values.			
	active2=rod2[0]; active1=rod2[0];
		}
	}

/////////////////////////////////////////////////////////////////////////////
	
	///6. Score team1
	{
		b2PolygonShape shape[10];
		b2FixtureDef *fd = new b2FixtureDef;
		fd->restitution = 0;
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
	
	///7. Score team2
	{
		b2PolygonShape shape[10];
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
  ///8. Pointers
	  {
	b2Vec2 vertices[3];
	vertices[0].Set(-1.0f, 0.0f);
	vertices[1].Set(1.0f, 0.0f);
	vertices[2].Set(0.0f, -2.0f);
	b2PolygonShape triangle;
	triangle.Set(vertices,3);
	
	b2FixtureDef *fd = new b2FixtureDef;
	fd->shape=&triangle;
	fd->filter.maskBits=0x0000;
	
	b2BodyDef triangle_body_1, triangle_body_2;
	triangle_body_1.position.Set(rod1[0]->GetPosition().x,45);
	pointer1= m_world->CreateBody(&triangle_body_1);
	pointer1->CreateFixture(fd);
	
	vertices[0].Set(-1.0f, 0.0f);
	vertices[1].Set(1.0f, 0.0f);
	vertices[2].Set(0.0f, 2.0f);
	
	fd->shape=&triangle;
	triangle.Set(vertices,3);
	triangle_body_2.position.Set(rod2[0]->GetPosition().x,-4);
	pointer2= m_world->CreateBody(&triangle_body_2);
	pointer2->CreateFixture(fd);
	
	}	 
  }
  
/////////////////////////////////////////////////////////////////////////////

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}


