#include <GL/glew.h>
#include <SDL2/SDL.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main_t(int argc, char* args[])
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
	
	SDL_Event event;
	while (true) // Render loop
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_Quit();
	
	return 0;
}
