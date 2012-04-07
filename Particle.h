// C++ particle class
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef PART_H_GUARD
#define PART_H_GUARD

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"

class Particle
{
	public:
		p_vector velocity;
		p_vector acceleration;

		Uint32 lastUpdateTime;
		Uint32 lastUpdateTime2;

		GLfloat r;
		GLfloat g;
		GLfloat b;
	
		GLfloat x;
		GLfloat y;
		GLfloat diameter;
		
		bool dead; //identifier which marks for deletion
		
		GLfloat bounce; //between 0 and 1

		Particle();
		Particle(GLfloat newX, GLfloat newY, GLfloat newDiameter, GLfloat newBounce);
		~Particle();

		void update(Uint32 currTime);
		virtual void specialUpdate(Uint32 currTime); //for subclass logic
		void backstep(Uint32 currTime);

		void reflect(p_vector& normal);
		
		virtual void draw();

	protected:

};

#endif

