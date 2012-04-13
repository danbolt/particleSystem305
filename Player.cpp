
#include <cstdio>
#include <cmath>

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Globals.h"
#include "Particle.h"
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
		xSpeed = 2;
	}
	else if (keys[SDLK_LEFT])
	{
		xSpeed = -2;
	}
	else
	{
		xSpeed = 0;
	}

	if (keys[SDLK_DOWN])
	{
		ySpeed = 2;
	}
	else if (keys[SDLK_UP])
	{
		ySpeed = -2;
	}
	else
	{
		ySpeed = 0;
	}
	
	x += xSpeed;
	y += ySpeed;
	
	/*for (std::vector<Wall*>::iterator it = wallList->begin(); it != wallList->end(); ++it)
	{
		if ((*it)->hitTest(x, y, 16, 16))
		{
			x -= xSpeed;
			y -= ySpeed;
		}
	}        */

	bool nwHit = false;
	bool neHit = false;
	bool swHit = false;
	bool seHit = false;
	
	for (std::vector<Wall*>::iterator it = wallList->begin(); it != wallList->end(); ++it)
	{
		nwHit = (*it)->hitTest(x + 2, y + 2, 8, 8) || nwHit;
		neHit = (*it)->hitTest(x + 6, y + 2, 8, 8) || neHit;
		swHit = (*it)->hitTest(x + 2, y + 6, 8, 8) || swHit;
		seHit = (*it)->hitTest(x + 6, y + 6, 8, 8) || seHit;
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
