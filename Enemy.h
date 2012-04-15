// C++ enemy class
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef ENEMY_H_GUARD
#define ENEMY_H_GUARD

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Particle.h"
#include "Wall.h"
#include "Fire.h"
#include "Triangle.h"

using namespace std;

class Enemy
{
	public:
	       Enemy(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList, vector<Wall*>* newWallList, vector<Fire*>* newFireList, vector<Triangle*>* newTriangleList);
	       ~Enemy();

	       void update(Uint32 currTime);
	       void draw();

	       bool log_xor(bool a, bool b);
	       bool hitTest(GLfloat oX, GLfloat oY, GLfloat oWidth, GLfloat oHeight);

	       GLfloat x,y;
	       GLfloat xSpeed, ySpeed;
	       
	       bool nwHit;
	       bool neHit;
	       bool swHit;
	       bool seHit;

	       bool facingRight;

	       int life;

	       Uint32 jumpTimer;
	       Uint32 jumpOffset;

	       Uint32 shootTimer;
	       Uint32 shootOffset;

	       vector<Particle*>* particleList;
	       vector<Wall*>* wallList;
	       vector<Fire*>* fireList;
	       vector<Triangle*>* triangleList;
};

#endif
