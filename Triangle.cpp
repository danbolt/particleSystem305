#include <cstdlib>
#include <cmath>
#include <cstdio>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Particle.h"
#include "Triangle.h"

bool Triangle::pointIntersect(Particle* p)
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
		return true;
	}
}

void Triangle::getRelevantNormal(Particle* p, p_vector& normal)
{
	//computes the point's barycentric coordinates of the triangle
	GLfloat bary1 = ( (p2.y - p3.y)*(p->x - p3.x) + (p3.x - p2.x)*(p->y - p3.y) )/( (p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y) );
	GLfloat bary2 = ( (p3.y - p1.y)*(p->x - p3.x) + (p1.x - p3.x)*(p->y - p3.y) )/( (p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y) );

	if (bary1 < 0)
	{

		// point on p3/p2 side of triangle
		GLfloat dx = p3.x - p2.x;
		GLfloat dy = p3.y - p2.y;
		
		//two candidates for a normal; find if inside trangle
		p_vector n1( -dy, dx);
		p_vector n2( dy, -dx);
		n1.normalize();
		n2.normalize();
		
		Particle candidate1(p->x + n1.x, p->y + n1.y);
		Particle candidate2(p->x + n2.x, p->y + n2.y);

		if (!pointIntersect(&candidate1))
		{
			normal.x = n1.x;
			normal.y = n1.y;
		}
		else if (!pointIntersect(&candidate2))
		{
			normal.x = n2.x;
			normal.y = n2.y;
		}
		else
		{
			normal.x = 0.0;
			normal.y = 0.0;
		}
	}
	else if (bary2 < 0)
	{

		// point on p3/p1 side of triangle
		GLfloat dx = p3.x - p1.x;
		GLfloat dy = p3.y - p1.y;

		//two candidates for a normal; find if inside trangle
		p_vector n1( -dy, dx);
		p_vector n2( dy, -dx);
		n1.normalize();
		n2.normalize();

		Particle candidate1(p->x + n1.x, p->y + n1.y);
		Particle candidate2(p->x + n2.x, p->y + n2.y);

		if (!pointIntersect(&candidate1))
		{
			normal.x = n1.x;
			normal.y = n1.y;
		}
		else if (!pointIntersect(&candidate2))
		{
			normal.x = n2.x;
			normal.y = n2.y;
		}
		else
		{
			normal.x = 0.0;
			normal.y = 0.0;
		}
	}
	else if (bary1 + bary2 > 1)
	{
		// point on p1/p2 side of triangle
		GLfloat dx = p2.x - p1.x;
		GLfloat dy = p2.y - p1.y;

		//two candidates for a normal; find if inside trangle
		p_vector n1( -dy, dx);
		p_vector n2( dy, -dx);
		n1.normalize();
		n2.normalize();

		Particle candidate1(p->x + n1.x, p->y + n1.y);
		Particle candidate2(p->x + n2.x, p->y + n2.y);

		if (!pointIntersect(&candidate1))
		{
			normal.x = n1.x;
			normal.y = n1.y;
		}
		else if (!pointIntersect(&candidate2))
		{
			normal.x = n2.x;
			normal.y = n2.y;
		}
		else
		{
			printf("this is an issue\n");
			normal.x = 0.0;
			normal.y = 0.0;
		}
	}
	else
	{
		// point should be inside triangle
	}
}

void Triangle::draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(p1.x, p1.y);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(p2.x, p2.y);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(p3.x, p3.y);
	glEnd();
}

