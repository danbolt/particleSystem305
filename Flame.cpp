#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <GL/gl.h>

#include "Globals.h"
#include "Particle.h"
#include "Flame.h"

Flame::Flame()
{
	//dead = true;
}

Flame::Flame (GLfloat newX, GLfloat newY)
{
	x = newX;
	y = newY;
	
	velocity.x = (rand() % 12) - 6;
	velocity.y = -5.0f;
	
	acceleration.x = 0.0f;
	acceleration.y = -9.8f;
	
	diameter = 2.0;
	
	creationTime = SDL_GetTicks();
	
	dead = false;
	
	type = FLAME;

	bounce = 0.0f;
	
	r = 1.0;
	g = 0.0;
	b = 0.0;

	lastUpdateTime = 0;
	lastUpdateTime2 = 0;
}

Flame::~Flame()
{
	//
}

void Flame::specialUpdate(Uint32 currTime)
{
	if (velocity.length() < 1.0f || currTime - creationTime > 2500 - (Uint32)(100*fabs(velocity.x)))
	{
		dead = true;
	}
	else
	{
		g = (currTime - creationTime)/4000.0f;
		if (g > 1.0f)
		{
			g = 1.0f;
		}
	}

}

void Flame::draw()
{
	p_vector dir = velocity;
	dir.normalize();

	glPointSize(diameter);
	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glVertex2f(0, 0);
	glEnd();
	glPointSize(diameter/1.5);
	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glVertex2f(-2*dir.x, -2*dir.y);
	glEnd();
}

