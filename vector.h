// C++ Vector Class
//
// CSC 305 Project 5: Particle System
// Daniel Savage 2012

#ifndef VECTOR_H
#define VECTOR_H

#include <GL/gl.h>

class p_vector
{
	public:
		p_vector();
		p_vector(GLfloat newX, GLfloat newY);
		~p_vector();
		
		GLfloat x;
		GLfloat y;

		void normalize();
		GLfloat length();

		GLfloat dotProduct(p_vector* other);

		p_vector operator+ (const p_vector& rhs) const;
		p_vector operator- (const p_vector& rhs) const;
		GLfloat operator* (const p_vector& rhs) const; //dot product
		p_vector operator* (const GLfloat& rhs) const;
	private:
};

#endif

