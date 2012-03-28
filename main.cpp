#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

SDL_Surface* screen;

// initalization function for things like SDL and OpenGL
int init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		perror("Error initalizing SDL");
		return 0;
	}

	if ((screen = SDL_SetVideoMode(320, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
	{
		perror("Error initalizing screen");
		return 0;
	}

	SDL_WM_SetCaption("Particle System", NULL);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	return 1;
}

int deinit()
{
	SDL_Quit();

	return 1;
}


int main (int argc, char* argv[])
{
	init();
	
	//
	
	deinit();
	
	return 0;
}
