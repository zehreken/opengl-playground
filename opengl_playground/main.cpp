#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "rotatingPlane.hpp"
#include "cubes.hpp"
#include "3_camera/world.hpp"
#include "4_color/color.hpp"
#include "5_basicLighting/basicLighting.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	SDL_Window *window = SDL_CreateWindow("OpenGL Playground", 250, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	// Test how many attributes does the GPU supports
	int attribCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attribCount);
	printf("max attribute: %d\n", attribCount);
	// ==============================================
	
	RotatingPlane rotatingPlane;
	Cubes cubes;
	World world;
	Color color;
	BasicLighting basicLighting;
	
	int deltaX;
	int deltaY;
	
	SDL_Event event;
	SDL_SetRelativeMouseMode(SDL_TRUE); // Gives the relative mouse position even if the mouse reaches the edge
	bool isRunning = true;
	while (isRunning) // Render loop
	{
		deltaX = 0;
		deltaY = 0;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			if (event.type == SDL_KEYDOWN)
			{
//				world.onKeyDown(event.key.keysym.sym);
//				color.onKeyDown(event.key.keysym.sym);
				basicLighting.onKeyDown(event.key.keysym.sym);
			}
			else if (event.type == SDL_KEYUP)
			{
//				world.onKeyUp(event.key.keysym.sym);
//				color.onKeyUp(event.key.keysym.sym);
				basicLighting.onKeyUp(event.key.keysym.sym);
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetRelativeMouseState(&deltaX, &deltaY);
			}
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
//		rotatingPlane.update();
//		cubes.update();
//		world.update(deltaX, deltaY);
//		color.update(deltaX, deltaY);
		basicLighting.update(deltaX, deltaY);
		
		// Always the last statement in the render loop
		SDL_GL_SwapWindow(window);
		
		SDL_Delay(20);
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_Quit();
	
	return 0;
}
