#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>

#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "vector.h"
#include "Particle.h"
#include "Triangle.h"

SDL_Surface* screen;

Uint8* keys;

std::vector<Particle*> particleList;
std::vector<Triangle*> triangleList;

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
	
	srand( time(NULL) );

	SDL_WM_SetCaption("Particle System", NULL);
	
	glViewport(0, 0, 640, 480);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	
	glOrtho(0, 640, 480, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);


	return 1;
}

void updateLogic(Uint32 currTime)
{
	for(std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
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
		
		if ((*it)->x < 0)
		{
			(*it)->backstep(currTime);
				
			p_vector wallNormal(1,0);
				
			(*it)->reflect(wallNormal);
		}
		else if ((*it)->x > 640)
		{
			(*it)->backstep(currTime);
				
			p_vector wallNormal(-1,0);
				
			(*it)->reflect(wallNormal);
		}
	}
}

void draw()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	for(std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		glPointSize((*it)->diameter);
		glBegin(GL_POINTS);
		glColor3f((*it)->r, (*it)->g, (*it)->b);
		glVertex2f((*it)->x, (*it)->y);
		glEnd();
	}
	
	for(std::vector<Triangle*>::iterator it2 = triangleList.begin(); it2 != triangleList.end(); ++it2)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f((*it2)->p1.x, (*it2)->p1.y);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f((*it2)->p2.x, (*it2)->p2.y);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f((*it2)->p3.x, (*it2)->p3.y);
		glEnd();
	}

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

	for (int i = 0; i < 10; i++)
	{
		Triangle* testTriangle = new Triangle();
		testTriangle->p1.x = 64*i - 1 ;
		testTriangle->p1.y = 480 - 10 ;
		testTriangle->p2.x = 64*i + 64 + 1 ;
		testTriangle->p2.y = 480 - 10 ;
		testTriangle->p3.x = 64*i + 32;
		testTriangle->p3.y = 416 - 10 ;
		triangleList.push_back(testTriangle);
	}

	//easy firework
	for (int i = 0; i < 10; i++)
	{
		Particle* testParticle = new Particle(rand() % 640, 140.0f, rand() % 10, (rand() % 100)/100.0);
		testParticle->velocity.x = 7 + (rand() % 10);
		testParticle->acceleration.y = 32;
		particleList.push_back(testParticle);
	}

	loop();

	particleList.clear();
	triangleList.clear();

	deinit();
	
	return 0;
}
