
#include <cstdio>
#include <cmath>

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Globals.h"
#include "Particle.h"
#include "Raindrop.h"
#include "Wall.h"
#include "Player.h"

bool Player::log_xor(bool a, bool b)
{
    return ( (a && !b) || (!a && b) );
}

Player::Player(GLfloat newX, GLfloat newY, vector<Particle*>* newParticleList, vector<Wall*>* newWallList)
{
	x = newX;
	y = newY;
	
	xSpeed = 0;
	ySpeed = 0;
	
	particleList = newParticleList;
	wallList = newWallList;
	
	facingRight = true;
}

Player::~Player()
{
	x = 0;
	y = 0;
}

void Player::update(Uint32 currTime)
{
	if (keys[SDLK_RIGHT])
	{
		facingRight = true;
		xSpeed = 2;
	}
	else if (keys[SDLK_LEFT])
	{
		facingRight = false;
		xSpeed = -2;
	}
	else
	{
		xSpeed = 0;
	}
	
	if (keys[SDLK_x] && (swHit || seHit))
	{
		ySpeed = -3;
	}

	if (ySpeed < 5)
	{
		ySpeed += 0.10;
	}

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
	
	if (keys[SDLK_c])
	{
		if (facingRight)
		{
			particleList->push_back(new Raindrop(x + 16, y + 8, (rand() % 20) + 30, (rand() % 10)));
		}
		else
		{
			particleList->push_back(new Raindrop(x, y + 8, -30 - (rand() % 20), (rand() % 10)));
		}
	}
}

void Player::draw()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x, y);
	glVertex2f(x + 16, y);
	glVertex2f(x + 16, y + 16);
	glVertex2f(x, y + 16);
	glEnd();
}
