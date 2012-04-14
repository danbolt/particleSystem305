#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <GL/gl.h>

#include "Globals.h"
#include "Particle.h"

Particle::Particle()
{
	dead = true;
}

Particle::Particle(GLfloat newX, GLfloat newY)
{
	x = newX;
	y = newY;
	
	bounce = (rand() % 100)/100.0;
	
	dead = false;

	velocity.x = 0.0f;
	velocity.y = 0.0f;

	acceleration.x = 0.0f;
	acceleration.y = 0.0f;
	
	r = (rand() % 100) - 50;
	g = (rand() % 100) - 50;
	b = (rand() % 100) - 50;
	
	diameter = 3;
	
	type = NONE;

	lastUpdateTime2 = 0;
	lastUpdateTime = 0;
}

Particle::~Particle()
{
	//
}

void Particle::specialUpdate(Uint32 currTime)
{
	//
}

void Particle::update(Uint32 currTime)
{
	// something's not working right with lastUpdateTime when constructed
	// don't have time to figure it out
	if (lastUpdateTime > 10000000 || lastUpdateTime == 0)
	{
		lastUpdateTime = currTime;
	}

	if (dead)
	{
		return;
	}
	
	specialUpdate(currTime);

	GLfloat deltaTimeF = ((float)currTime - (float)lastUpdateTime)/1000.0;

	// if the particle hasn't been updated for longer than one second, something's probably wrong
	// might not be able to fix in time frame, but easy to cover up
	if (currTime - lastUpdateTime > 1000)
	{
		dead = true;
	}

	// amy's reccomended Euler integration tricks
	x += (velocity.x)*deltaTimeF + (acceleration.x)*0.5*deltaTimeF*deltaTimeF;
	velocity.x += (acceleration.x)*deltaTimeF;

	y += (velocity.y)*deltaTimeF + (acceleration.y)*0.5*deltaTimeF*deltaTimeF;
	velocity.y += (acceleration.y)*deltaTimeF;

	if (x < -10)
	{
		dead = true;
	}
	if (x > SCREEN_WIDTH + 10)
	{
		dead = true;
	}
	if (y < -10)
	{
		dead = true;
	}
	if (y > SCREEN_HEIGHT + 10)
	{
		dead = true;
	}

	lastUpdateTime2 = lastUpdateTime;
	lastUpdateTime = currTime;
}

void Particle::backstep(Uint32 currTime)
{
	GLfloat deltaTimeF = ((float)lastUpdateTime - (float)lastUpdateTime2)/1000.0;

	// amy's reccomended Euler integration tricks
	velocity.x -= (acceleration.x)*deltaTimeF;
	x -= (velocity.x)*deltaTimeF + (acceleration.x)*0.5*deltaTimeF*deltaTimeF;

        velocity.y -= (acceleration.y)*deltaTimeF;
	y -= (velocity.y)*deltaTimeF + (acceleration.y)*0.5*deltaTimeF*deltaTimeF;
}

void Particle::reflect(p_vector& wallNormal)
{
	backstep(0);

	p_vector oldVelo = velocity;

	GLfloat c1 = (-1) * ((oldVelo.x * wallNormal.x) + (oldVelo.y * wallNormal.y));
	
	GLfloat newVectorX = oldVelo.x + (2* wallNormal.x * c1);
	GLfloat newVectorY = oldVelo.y + (2* wallNormal.y * c1);

	velocity.x = newVectorX * bounce;
	velocity.y = newVectorY * bounce;
}

void Particle::draw()
{
	glPointSize(diameter);
	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glVertex2f(0, 0);
	glEnd();
}

