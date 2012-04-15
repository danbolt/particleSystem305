// C++ particle for fire
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef FIRE_H_GUARD
#define FIRE_H_GUARD

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Triangle.h"
#include "Particle.h"
#include "Wall.h"

using namespace std;

class Fire : public Triangle
{
	public:
	       Fire(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList, vector<Wall*>* newWallList, bool hasFuse);
	       ~Fire();

	       virtual void update(Uint32 currTime);
	       virtual bool pointIntersect(Particle* p);

	       virtual void draw();

	       bool hitTest(GLfloat oX, GLfloat oY, GLfloat oWidth, GLfloat oHeight);

	       GLfloat xSpeed;
	       GLfloat ySpeed;

	       int life; //between 0 and 100

	       bool limited;
	       Uint32 timeToLive;
	       Uint32 creationTime;

	       vector<Particle*>* particleList;
	       vector<Wall*>* wallList;
};

#endif
