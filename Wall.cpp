#include <vector>
#include <cstdio>
#include <cmath>

#include <GL/gl.h>
#include <SDL/SDL.h>

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

void Wall::draw()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.5, 0.0);
	glVertex2f(x, y);
        glVertex2f(x + 16, y);
        glVertex2f(x + 16, y + 16);
        glVertex2f(x, y + 16);
	glEnd();
}
