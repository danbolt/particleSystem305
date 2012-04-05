#include <GL/gl.h>
#include <cstdlib>
#include <cmath>

#include "vector.h"

p_vector::p_vector()
{
	x = 0.0f;
	y = 0.0f;
}

p_vector::p_vector(GLfloat newX, GLfloat newY)
{
	x = newX;
	y = newY;
}

p_vector::~p_vector()
{
	//
}

GLfloat p_vector::length()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}


void p_vector::normalize()
{
	GLfloat vec_length = length();

	if (fabs(vec_length) > 0.0001)
	{
		x = x/vec_length;
		y = y/vec_length;
	}
}

GLfloat p_vector::dotProduct(p_vector* other)
{
	return (x * other->x) + (y * other->y);
}

p_vector p_vector::operator+ (const p_vector& rhs) const
{
	p_vector temp(0.0f, 0.0f);
	temp.x = this->x + rhs.x;
	temp.y = this->y + rhs.y;

	return temp;
}

p_vector p_vector::operator- (const p_vector& rhs) const
{
	p_vector temp(0.0f, 0.0f);
	temp.x = this->x - rhs.x;
	temp.y = this->y - rhs.y;

	return temp;
}

GLfloat p_vector::operator* (const p_vector& rhs) const
{
	return (x * rhs.x) + (y * rhs.y);
}

p_vector p_vector::operator* (const GLfloat& rhs) const
{
	p_vector temp(0.0f, 0.0f);
	temp.x = (this->x) * rhs;
	temp.y = (this->y) * rhs;

	return temp;
}

