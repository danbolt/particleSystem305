#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>

#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Globals.h"
#include "vector.h"
#include "Particle.h"
#include "Raindrop.h"
#include "Triangle.h"
#include "Flame.h"
#include "Fire.h"
#include "Wall.h"
#include "Player.h"

char testLevel[15][20] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

SDL_Surface* screen;

Uint8* keys;
int mouseX = 0;
int mouseY = 0;

Uint32 lastUpdate;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

std::vector<Particle*> particleList;
std::vector<Triangle*> triangleList;
std::vector<Wall*> wallList;

Player* pl;

bool spaceDown = false;
int addCount = 0;

Fire* testFire;
Wall* testWall;

// initalization function for things like SDL and OpenGL
int init()
{
	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		perror("Error initalizing SDL");
		return 0;
	}
	
	freopen( "CON", "w", stdout );

	if ((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
	{
		perror("Error initalizing screen");
		return 0;
	}
	
	srand( time(NULL) );

	SDL_WM_SetCaption("Particle System", NULL);
	
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);

	particleList.reserve(3000);
	wallList.reserve(1200);

	lastUpdate = SDL_GetTicks();

	return 1;
}

void updateLogic(Uint32 currTime)
{
	pl->update(currTime);

	testFire->update(currTime);

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

void draw()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	for(std::vector<Wall*>::iterator it = wallList.begin(); it != wallList.end(); ++it)
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
	
	pl->draw();

	SDL_GL_SwapBuffers();
}

void loop()
{
	int quit = 0;
	SDL_Event ev;

	while (!quit)
	{
		while(SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
		
		Uint32 currentTime = SDL_GetTicks();
		if (currentTime - lastUpdate > 30)
		{

			keys = SDL_GetKeyState(NULL);

			updateLogic(currentTime);

			draw();                      
			lastUpdate = currentTime;
		}
	}
}

int deinit()
{
	SDL_Quit();

	return 1;
}


int main (int argc, char* argv[])
{
	init();

	pl = new Player(120, 220, &particleList, &wallList);

	testFire = new Fire(320, 340, &particleList);
	triangleList.push_back(testFire);

	for (int i = 0; i < 40; i++)
	{
		if (i == 20 || i == 19)
		{
			continue;
		}

		testWall = new Wall(i*16, 248);
		wallList.push_back(testWall);
		triangleList.push_back(&(testWall->upper));
		triangleList.push_back(&(testWall->lower));
		
		testWall = new Wall(i*16, 200);
		wallList.push_back(testWall);
		triangleList.push_back(&(testWall->upper));
		triangleList.push_back(&(testWall->lower));

	}

	loop();

	particleList.clear();
	triangleList.clear();

	deinit();
	
	return 0;
}
