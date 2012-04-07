#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <GL/gl.h>

#include "Globals.h"
#include "Particle.h"
#include "Raindrop.h"

Raindrop::Raindrop()
{
	dead = true;
}

Raindrop::Raindrop (GLfloat newX, GLfloat newY, GLfloat newXSpeed, GLfloat newYSpeed)
{
	x = newX;
	y = newY;
	
	velocity.x = newXSpeed;
	velocity.y = newYSpeed;
	
	acceleration.x = 0.0f;
	acceleration.y = 9.8f;
	
	diameter = 2.0;
	
	creationTime = SDL_GetTicks();
	
	dead = false;
	
	bounce = 0.4;
	
	r = 0.0;
	g = 0.0;
	b = 1.0;
}

Raindrop::~Raindrop()
{
	//
}

void Raindrop::specialUpdate(Uint32 currTime)
{
	//
}

void Raindrop::draw()
{
	glPointSize(diameter);
	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glVertex2f(0, 0);
	glEnd();
}

