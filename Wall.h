// C++ wall class
// A wall is always a 16x16 pixel block
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef WALL_H_GUARD
#define WALL_H_GUARD

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "vector.h"
#include "Triangle.h"

using namespace std;

class Wall
{
	public:
	       Wall(GLfloat newX, GLfloat newY);
	       ~Wall();
	       
	       void draw();

	       GLfloat x,y;
	       Triangle upper;
	       Triangle lower;
};

#endif