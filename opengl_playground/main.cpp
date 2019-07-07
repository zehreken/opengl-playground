#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "shader.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	SDL_Window *window = SDL_CreateWindow("OpenGL Playground", 250, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	// Test how many attributes does the GPU supports
	int attribCount;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attribCount);
	printf("max attribute: %d\n", attribCount);
	// ==============================================
	
	// Program related
	/* OBSOLETE
	unsigned  vertexShader = 0;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VERTEX_SOURCE, NULL);
	glCompileShader(vertexShader);
	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FRAGMENT_SOURCE, NULL);
	glCompileShader(fragmentShader);
	
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	 */
    
    Shader shader("/Users/zehreken/Development/opengl_playground/opengl_playground/vertex.txt", "/Users/zehreken/Development/opengl_playground/opengl_playground/fragment.txt");
	
	SDL_Surface *surface = IMG_Load("/Users/zehreken/Development/opengl_playground/opengl_playground/uv_map.jpg");
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	SDL_FreeSurface(surface);
	
	// x, y, z, r, g, b, u, v
	float vertices[] =
	{
		// top right
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		// bottom right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		// bottom left
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		// top left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};
	
	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};
	
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// ===============
	
	SDL_Event event;
	while (true) // Render loop
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		float ticks = SDL_GetTicks() / 1000.0f;
//		shader.setFloat("offset", sin(ticks));
		
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "globalColor");
		
		glBindTexture(GL_TEXTURE_2D, texture);
//		glUseProgram(shaderProgram);
		shader.use();
		
//		glUniform4f(vertexColorLocation, 0.5f, sin(ticks), 0.0f, 1.0f);
		
		glBindVertexArray(vao);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		// Always the last statement in the render loop
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_Quit();
	
	return 0;
}
