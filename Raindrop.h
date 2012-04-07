// C++ particle raindrop
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef RAIN_H_GUARD
#define RAIN_H_GUARD

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Particle.h"

class Raindrop : public Particle
{
	public:
	       Raindrop();
	       Raindrop(GLfloat newX, GLfloat newY, GLfloat newXSpeed, GLfloat newYSpeed);
	       ~Raindrop();
	       
	       virtual void specialUpdate(Uint32 currTime);
	       
	       virtual void draw();

	       Uint32 creationTime;
};

#endif