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

	lastUpdateTime2 = SDL_GetTicks();
	lastUpdateTime = SDL_GetTicks();
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
	if (dead)
	{
		return;
	}
	
	specialUpdate(currTime);

	GLfloat deltaTime = ((float)currTime - (float)lastUpdateTime)/1000.0;
	
	// if the particle has travelled a crazy amount of distance, something's wrong. for now delete it
	// might not be able to fix in time frame, but easy to cover up
	GLfloat distance = sqrt( pow(((velocity.x)*deltaTime + (acceleration.x)*0.5*deltaTime*deltaTime), 2) + pow(((velocity.x)*deltaTime + (acceleration.x)*0.5*deltaTime*deltaTime), 2) );
	if (distance > 5.0)
	{
		//printf("distance travelled: %f, deltatime: %f\n", distance, deltaTime);
		dead = true;
	}


	// amy's reccomended Euler integration tricks
	x += (velocity.x)*deltaTime + (acceleration.x)*0.5*deltaTime*deltaTime;
	velocity.x += (acceleration.x)*deltaTime;

	y += (velocity.y)*deltaTime + (acceleration.y)*0.5*deltaTime*deltaTime;
	velocity.y += (acceleration.y)*deltaTime;

	lastUpdateTime2 = lastUpdateTime;
	lastUpdateTime = currTime;
	
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
}

void Particle::backstep(Uint32 currTime)
{
	GLfloat deltaTime = ((float)lastUpdateTime - (float)lastUpdateTime2)/1000.0;

	// amy's reccomended Euler integration tricks
	velocity.x -= (acceleration.x)*deltaTime;
	x -= (velocity.x)*deltaTime + (acceleration.x)*0.5*deltaTime*deltaTime;

        velocity.y -= (acceleration.y)*deltaTime;
	y -= (velocity.y)*deltaTime + (acceleration.y)*0.5*deltaTime*deltaTime;
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

