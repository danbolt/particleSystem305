//

#include <cstdio>
#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Particle.h"
#include "Flame.h"
#include "Fire.h"

Fire::Fire(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList)
{
	p1.x = newX;
	p1.y = newY - 15;
	p2.x = newX - 10;
	p2.y = newY + 10;
	p3.x = newX + 10;
	p3.y = newY + 10;

	particleList = newParticleList;
	
	visible = true;
	
	life = 100;
}

Fire::~Fire()
{
	//
}

void Fire::update(Uint32 currTime)
{
	if (visible && life > 0)
	{
		particleList->push_back(new Flame( p1.x, p1.y));
		particleList->push_back(new Flame( p2.x, p2.y - 5));
		particleList->push_back(new Flame( p3.x + 1, p3.y - 5));
	}

	if (life < 1 && visible)
	{
		visible = false;
	}
}

bool Fire::pointIntersect(Particle* p)
{
	//computes the point's barycentric coordinates of the triangle
	GLfloat bary1 = ( (p2.y - p3.y)*(p->x - p3.x) + (p3.x - p2.x)*(p->y - p3.y) )/( (p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y) );
	GLfloat bary2 = ( (p3.y - p1.y)*(p->x - p3.x) + (p1.x - p3.x)*(p->y - p3.y) )/( (p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y) );
	
	if (bary1 < 0 || bary2 < 0 || bary1 > 1 || bary2 > 1 || bary1 + bary2 > 1)
	{
		return false;
	}
	else
	{
		if (p->type == RAINDROP)
		{
			life--;
		}
		if (p->type != FLAME)
		{
			p->dead = true;
		}
		return true;
	}
}

void Fire::draw()
{
	if (visible)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(p3.x, p3.y);
		glEnd();
	}
}


