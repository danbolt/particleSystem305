#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <GL/gl.h>

#include "Particle.h"

Particle::Particle(GLfloat newX, GLfloat newY, GLfloat newDiameter)
{
	x = newX;
	y = newY;

	velocity.x = 0.0f;
	velocity.y = 0.0f;

	acceleration.x = 0.0f;
	acceleration.y = 0.0f;
	
	r = (rand() % 100) - 50;
	g = (rand() % 100) - 50;
	b = (rand() % 100) - 50;
	
	diameter = newDiameter;

	lastUpdateTime2 = SDL_GetTicks();
	lastUpdateTime = SDL_GetTicks();
}

Particle::~Particle()
{
	//
}

void Particle::update(Uint32 currTime)
{
	GLfloat deltaTime = ((float)currTime - (float)lastUpdateTime)/1000.0;

	// amy's reccomended Euler integration tricks
	x += (velocity.x)*deltaTime + (acceleration.x)*0.5*deltaTime*deltaTime;
	velocity.x += (acceleration.x)*deltaTime;

	y += (velocity.y)*deltaTime + (acceleration.y)*0.5*deltaTime*deltaTime;
	velocity.y += (acceleration.y)*deltaTime;

	lastUpdateTime2 = lastUpdateTime;
	lastUpdateTime = currTime;
}

void Particle::backstep(Uint32 currTime)
{
	GLfloat deltaTime = ((float)currTime - (float)lastUpdateTime2)/1000.0;

	// amy's reccomended Euler integration tricks
	velocity.x -= (acceleration.x)*deltaTime;
	x -= (velocity.x)*deltaTime + (acceleration.x)*0.5*deltaTime*deltaTime;

        velocity.y -= (acceleration.y)*deltaTime;
	y -= (velocity.y)*deltaTime + (acceleration.y)*0.5*deltaTime*deltaTime;
}

