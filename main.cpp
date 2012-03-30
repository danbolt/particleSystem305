#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "vector.h"
#include "Particle.h"

SDL_Surface* screen;

Uint8* keys;

std::vector<Particle*> particleList;

// initalization function for things like SDL and OpenGL
int init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		perror("Error initalizing SDL");
		return 0;
	}

	if ((screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
	{
		perror("Error initalizing screen");
		return 0;
	}

	SDL_WM_SetCaption("Particle System", NULL);
	
	glViewport(0, 0, 640, 480);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	glOrtho(0, 640, 480, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);

	return 1;
}

void updateLogic(Uint32 currTime)
{
	for(std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		(*it)->update(currTime);
	}
}

void draw()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for(std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		glVertex2f((*it)->x, (*it)->y);
	}
	glEnd();

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
		
		keys = SDL_GetKeyState(NULL);

		updateLogic(SDL_GetTicks());

		draw();
	}

	SDL_Delay(20);
}

int deinit()
{
	SDL_Quit();

	return 1;
}


int main (int argc, char* argv[])
{
	init();

	for (int i = 0; i < 500; i++)
	{
		Particle* testParticle = new Particle(320.0f, 240.0f, 2.0f);
		testParticle->velocity.x = (rand() % 50) - 25;
		testParticle->velocity.y = (rand() % 50) - 25;
		
		particleList.push_back(testParticle);
	}

	loop();
	
	particleList.clear();

	deinit();
	
	return 0;
}
