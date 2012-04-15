#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "GL/gl.h"
#include "SDL/SDL.h"

#include "Globals.h"
#include "Particle.h"
#include "Triangle.h"
#include "Flame.h"
#include "Fire.h"
#include "Wall.h"
#include "Enemy.h"

using namespace std;

bool Enemy::log_xor(bool a, bool b)
{
    return ( (a && !b) || (!a && b) );
}

Enemy::Enemy(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList, vector<Wall*>* newWallList, vector<Fire*>* newFireList, vector<Triangle*>* newTriangleList)
{
	x = newX;
	y = newY;

	xSpeed = 0;
	ySpeed = 0;

	life = 100;

	facingRight = true;

	wallList = newWallList;
	particleList = newParticleList;
	fireList = newFireList;
	triangleList = newTriangleList;

	nwHit = false;
	neHit = false;
	swHit = false;
	seHit = false;

	jumpTimer = 0;
	jumpOffset = (rand() % 2000) + 2000;

	shootTimer = 0;
	shootOffset = (rand() % 1000) + 3000;
}

Enemy::~Enemy()
{
	//
}

void Enemy::update(Uint32 currTime)
{
	if (jumpTimer == 0)
	{
		jumpTimer = currTime;
	}
	if (shootTimer == 0)
	{
		shootTimer = currTime;
	}

	if (x < playerX)
	{
		facingRight = true;
	}
	else
	{
		facingRight = false;
	}

	int flamesToAdd = 0;

	//loop through particles and subtract life for water
	for (std::vector<Particle*>::iterator it = particleList->begin(); it != particleList->end(); ++it)
	{
		if ((*it)->type == RAINDROP && hitTest((*it)->x, (*it)->y, 2, 2))
		{
			life--;
			flamesToAdd++;
			(*it)->dead = true;
		}

	}

	for (int i = 0; i < flamesToAdd; i++)
	{
		particleList->push_back(new Flame(x + (rand() % 16), y));
	}

	if (life < 1)
	{
		for (int i = 0; i < 20; i++)
		{
			particleList->push_back(new Flame(x + 8, y + 8));
		}
	}

	if ((seHit || swHit) && currTime - jumpTimer > jumpOffset)
	{
		ySpeed = -4;
		jumpTimer = currTime;
	}

	if (currTime - shootTimer > shootOffset)
	{
		Fire* shot = new Fire(x, y, particleList, wallList, true);
		if (facingRight)
		{
			shot->xSpeed = 4.6;
			shot->timeToLive = 1050;
			shot->life = 20;

			shot->p1.y += 14;
			shot->p2.x += 5;
			shot->p3.x -= 5;
		}
		else
		{
			shot->xSpeed = -4.6;
			shot->timeToLive = 1050;
			shot->life = 20;

			shot->p1.y += 14;
			shot->p2.x += 5;
			shot->p3.x -= 5;
		}
		
		fireList->push_back(shot);
		triangleList->push_back(shot);

		shootTimer = currTime;
	}

	//speed settings
	if (ySpeed < 5)
	{
		ySpeed += 0.10;
	}

	//collision detection
	x += xSpeed;
	y += ySpeed;

	nwHit = false;
	neHit = false;
	swHit = false;
	seHit = false;
	
	for (std::vector<Wall*>::iterator it = wallList->begin(); it != wallList->end(); ++it)
	{
		nwHit = (*it)->hitTest(x + 1, y + 1, 8, 8) || nwHit;
		neHit = (*it)->hitTest(x + 7, y + 1, 8, 8) || neHit;
		swHit = (*it)->hitTest(x + 1, y + 7, 8, 8) || swHit;
		seHit = (*it)->hitTest(x + 7, y + 7, 8, 8) || seHit;
	}

	if (log_xor(log_xor(neHit, nwHit), log_xor(seHit, swHit)))
	{
		if (xSpeed < 0.0 && (nwHit || swHit))
		{
			x -= xSpeed;
		}
		if (xSpeed > 0.0 && (neHit || seHit))
		{
			x -= xSpeed;
		}
		if (ySpeed > 0.0 && (seHit || swHit))
		{
			y -= ySpeed;
		}
		if (ySpeed < 0.0 && (neHit || nwHit))
		{
			y -= ySpeed;
		}
	}
	
	if ( (neHit && nwHit && !seHit && !swHit) || (seHit && swHit && !neHit && !nwHit) )
	{
		y -= ySpeed;
	}
	if ( (neHit && seHit && !nwHit && !swHit) || (nwHit && swHit && !neHit && !seHit))
	{
		x -= xSpeed;
	}
	
	if (seHit || swHit)
	{
		ySpeed = 0;
	}
	else if (neHit || nwHit)
	{
		ySpeed = 0;
	}
}

void Enemy::draw()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(x, y);
        glVertex2f(x + 16, y);
        glVertex2f(x + 16, y + 16);
        glVertex2f(x, y + 16);
	glEnd();
}

bool Enemy::hitTest(GLfloat oX, GLfloat oY, GLfloat oWidth, GLfloat oHeight)
{
	if (x < oX + oWidth && x + 16 > oX && y < oY + oHeight && y + 16 > oY)
	{
		return true;
	}
	else
	{
		return false;
	}
}



