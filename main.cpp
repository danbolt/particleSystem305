#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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
#include "Level.h"

char testTileMap[30][40] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,4,0,0,0,0,0,0,0,1,1,0,1},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,1},
{0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
{0,0,0,0,1,0,0,2,0,1,1,0,0,1,1,0,4,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,0,1},
{0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0},
{1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,0,1,0,0,0,0,1,4,0,0,1,0,0},
{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,0,0},
{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,0,3,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0},
{1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,1,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0},
{0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0},
{0,0,0,1,4,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,1,0,0},
{0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

SDL_Surface* screen;

SDL_Surface* tiles;
GLuint tilesTexture;

Uint8* keys;
int mouseX = 0;
int mouseY = 0;

GLfloat playerX;

Uint32 lastUpdate;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

std::vector<Particle*> particleList;
std::vector<Triangle*> triangleList;
std::vector<Wall*> wallList;

Player* pl;

Level* testLevel;

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
	
	if ((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
	{
		perror("Error initalizing screen");
		return 0;
	}
	
	srand( time(NULL) );

	SDL_WM_SetCaption("Particle System", NULL);

	tiles = IMG_Load("sprites.png");
	
	SDL_SetAlpha(tiles, 0, 0);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);

	glEnable(GL_TEXTURE_2D);

	glAlphaFunc(GL_GREATER, 0.1f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);	
	glGenTextures(1, &tilesTexture);
	glBindTexture(GL_TEXTURE_2D, tilesTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, tiles->pixels);
	SDL_FreeSurface(tiles); 

	testLevel = new Level(testTileMap);

	lastUpdate = SDL_GetTicks();

	return 1;
}

void updateLogic(Uint32 currTime)
{
	testLevel->update(currTime);
}

void draw()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	testLevel->draw();

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

	loop();

	deinit();
	
	return 0;
}
