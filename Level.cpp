#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Globals.h"
#include "Particle.h"
#include "Triangle.h"
#include "Fire.h"
#include "Player.h"
#include "Wall.h"
#include "Level.h"
#include "Enemy.h"

using namespace std;

Level::Level(char level[15][20])
{
	particleList.reserve(3000);
	wallList.reserve(1200);
	triangleList.reserve(2400);
	enemyList.reserve(30);

	pl = NULL;

	Wall* testWall;
	Fire* testFire;
	Enemy* testEnemy;

	//iterate through level and create data
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			switch (level[j][i])
			{
				case 1:
					testWall = new Wall(i * 32, j * 32);
					wallList.push_back(testWall);
					triangleList.push_back(&(testWall->upper));
					triangleList.push_back(&(testWall->upper));
					
					testWall = new Wall((i * 32) + 16, j * 32);
					wallList.push_back(testWall);
					triangleList.push_back(&(testWall->upper));
					triangleList.push_back(&(testWall->upper));

					testWall = new Wall(i * 32, (j * 32) + 16);
					wallList.push_back(testWall);
					triangleList.push_back(&(testWall->upper));
					triangleList.push_back(&(testWall->upper));

					testWall = new Wall((i * 32) + 16, (j * 32) + 16);
					wallList.push_back(testWall);
					triangleList.push_back(&(testWall->upper));
					triangleList.push_back(&(testWall->upper));

				break;
				case 2:
					if (pl == NULL)
					{
						pl = new Player(32 * i, 32 * j, &particleList, &wallList, &fireList);
					}
				break;
				case 3:
					testFire = new Fire((i * 32) + 16, (j * 32) + 22, &particleList, &wallList, false);
					triangleList.push_back(testFire);
					fireList.push_back(testFire);
				break;
				case 4:
					testEnemy = new Enemy(i* 32, j * 32 + 16, &particleList, &wallList, &fireList, &triangleList);
					enemyList.push_back(testEnemy);
				break;
			}
		}
	}
	
	if (pl == NULL)
	{
		pl = new Player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, &particleList, &wallList, &fireList);
	}
}

Level::~Level()
{
	particleList.clear();
	triangleList.clear();
	fireList.clear();
	wallList.clear();
	enemyList.clear();

	delete pl;
}

void Level::update(Uint32 currTime)
{
	pl->update(currTime);

	for (vector<Fire*>::iterator it = fireList.begin(); it != fireList.end(); ++it)
	{
		if ((*it)->life < 1)
		{
			for(std::vector<Triangle*>::iterator it2 = triangleList.begin(); it2 != triangleList.end(); ++it2)
			{
				if ((*it2) == (*it))
				{
					it2 = triangleList.erase(it2);
					it2--;
				}
			}

			delete (*it);
			it = fireList.erase(it);
			it--;
		}
		else
		{
			(*it)->update(currTime);
		}
	}

	for (vector<Enemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		if ((*it)->life < 1)
		{
			delete (*it);
			it = enemyList.erase(it);
			it--;
		}
		else
		{
			(*it)->update(currTime);
		}
	}

	for (std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); )
	{
		if ((*it)->dead)
		{
			delete (*it);
			it = particleList.erase(it);
		}
		else
		{
			(*it)->update(currTime);
			
			for(std::vector<Triangle*>::iterator it2 = triangleList.begin(); it2 != triangleList.end(); ++it2)
			{
				if ((*it2)->pointIntersect(*it))
				{
					(*it)->backstep(currTime);
					
					p_vector wallNormal(0,0);
					(*it2)->getRelevantNormal((*it), wallNormal);
					
					(*it)->reflect(wallNormal);
				}
			}
			
			if ((*it)->x <= 0)
			{
				(*it)->backstep(currTime);
					
				p_vector wallNormal(1,0);

				(*it)->reflect(wallNormal);
			}
			else if ((*it)->x >= SCREEN_WIDTH)
			{
				(*it)->backstep(currTime);
					
				p_vector wallNormal(-1,0);
					
				(*it)->reflect(wallNormal);
			}
			
			++it;
		}
	}
}

void Level::draw()
{
	glLoadIdentity();

	pl->draw();

	for(std::vector<Wall*>::iterator it = wallList.begin(); it != wallList.end(); ++it)
	{
		(*it)->draw();
	}

	for (vector<Enemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		(*it)->draw();
	}

	for(std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		if ((*it)->dead)
		{
			continue;
		}
		glPushMatrix();
		glTranslatef((*it)->x, (*it)->y, 0);
		(*it)->draw();
		glPopMatrix();
	}

	for(std::vector<Triangle*>::iterator it2 = triangleList.begin(); it2 != triangleList.end(); ++it2)
	{
		if ((*it2)->visible)
		{
			(*it2)->draw();
		}
	}
}

