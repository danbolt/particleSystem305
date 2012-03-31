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
		p_vector n1( -dx, dy);
		p_vector n2( dx, -dy);
		n1.normalize();
		n2.normalize();
		
		Particle candidate1(p->x + n1.x, p->y + n1.y, 0);
		Particle candidate2(p->x + n2.x, p->y + n2.y, 0);

		if (!pointIntersect(&candidate1))
		{
			normal.x = n1.x;
			normal.y = n1.y;
		}
		else
		{
			normal.x = n2.x;
			normal.y = n2.y;
		}
	}
	else if (bary2 < 0)
	{
		// point on p3/p1 side of triangle
	}
	else if (bary1 + bary2 > 1)
	{
		// point on p1/p2 side of triangle
	}
	else
	{
		// point should be inside triangle
	}
}

