// C++ player class
// The player will be a 16x16 sprite; nothing fancy
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef PLAYER_H_GUARD
#define PLAYER_H_GUARD

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Particle.h"
#include "Wall.h"
#include "Fire.h"

using namespace std;

class Player
{
	public:
	       Player(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList, vector<Wall*>* newWallList, vector<Fire*>* newFireList);
	       ~Player();

	       void update(Uint32 currTime);
	       void draw();
	       bool log_xor(bool a, bool b);

	       GLfloat x,y;
	       GLfloat xSpeed, ySpeed;

	       bool nwHit;
	       bool neHit;
	       bool swHit;
	       bool seHit;
	       
	       bool facingRight;

	       bool knockedBack;
	       GLfloat knockBackSpeed;
	       GLfloat xDelta;

	       vector<Particle*>* particleList;
	       vector<Wall*>* wallList;
	       vector<Fire*>* fireList;
};

#endif
