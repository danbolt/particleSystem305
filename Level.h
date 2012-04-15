// C++ Level class
//
// CSC 305 Project 5 : Particle System
// Daniel Savage

#ifndef LEVEL_H_GUARD
#define LEVEL_H_GUARD

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Particle.h"
#include "Triangle.h"
#include "Fire.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"

using namespace std;

class Level
{
	public:
		Level(char level[30][40]);
		~Level();

		void update(Uint32 currTime);
		void draw();
	protected:
		vector<Particle*> particleList;
		vector<Triangle*> triangleList;
		vector<Fire*> fireList;
		vector<Wall*> wallList;
		vector<Enemy*> enemyList;
		Player* pl;

};

#endif

