// C++ particle raindrop
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef FLAME_H_GUARD
#define FLAME_H_GUARD

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Particle.h"

class Flame : public Particle
{
	public:
	       Flame();
	       Flame(GLfloat newX, GLfloat newY);
	       ~Flame();
	       
	       virtual void specialUpdate(Uint32 currTime);
	       
	       virtual void draw();

	       Uint32 creationTime;
};

#endif