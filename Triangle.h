// C++ triangle class
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef TRIANGLE_H_GUARD
#define TRIANGLE_H_GUARD

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Particle.h"

class Triangle
{
	public:
	       // just use 3 vectors for the points
		p_vector p1;
		p_vector p2;
		p_vector p3;
		
		bool pointIntersect(Particle* p);
		void getRelevantNormal(Particle* p, p_vector& normal);

	protected:


};

#endif
