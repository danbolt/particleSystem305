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

using namespace std;

class Player
{
	public:
	       Player(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList, vector<Wall*>* newWallList);
	       ~Player();
	       
	       void update(Uint32 currTime);
	       void draw();
	       bool log_xor(bool a, bool b);

	       GLfloat x,y;
	       GLfloat xSpeed, ySpeed;
	       
	       vector<Particle*>* particleList;
	       vector<Wall*>* wallList;
};

#endif