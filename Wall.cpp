#include <vector>
#include <cstdio>
#include <cmath>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Globals.h"
#include "vector.h"
#include "Triangle.h"
#include "Wall.h"

Wall::Wall(GLfloat newX, GLfloat newY)
{
	x = newX;
	y = newY;

	upper.p1.x = newX;
	upper.p1.y = newY;
	upper.p2.x = newX + 16;
	upper.p2.y = newY;
	upper.p3.x = newX;
	upper.p3.y = newY + 16;
	upper.visible = false;
	
	lower.p1.x = newX + 16;
	lower.p1.y = newY + 16;
	lower.p2.x = newX;
	lower.p2.y = newY + 16;
	lower.p3.x = newX + 16;
	lower.p3.y = newY ;
	lower.visible = false;
}

Wall::~Wall()
{
	//
}

bool Wall::hitTest(GLfloat oX, GLfloat oY, GLfloat oWidth, GLfloat oHeight)
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

void Wall::draw()
{
	/*
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.5, 0.0);
	glVertex2f(x, y);
        glVertex2f(x + 16, y);
        glVertex2f(x + 16, y + 16);
        glVertex2f(x, y + 16);
	glEnd(); */

	//glBindTexture(GL_TEXTURE_2D, tilesTexture);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.25, 0.25);
	glVertex2f(x, y);
	glTexCoord2f(0.50, 0.25);
	glVertex2f(x + 16, y);
	glTexCoord2f(0.50, 0.50);
	glVertex2f(x + 16, y + 16);
	glTexCoord2f(0.25, 0.50);
	glVertex2f(x, y + 16);
	glEnd();

}
