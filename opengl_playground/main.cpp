#include <GL/glew.h>
#include <SDL2/SDL.h>

const GLchar *VERTEX_SOURCE = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = vec4(0.5, 0.0, 0.0, 0.0);
}
)glsl";

const GLchar *FRAGMENT_SOURCE = R"glsl(
#version 330 core
out vec4 FragColor;
uniform vec4 globalColor;
in vec4 vertexColor;

void main()
{
	FragColor = vertexColor;
	FragColor = globalColor;
}
)glsl";

bool init()
{
	return false;
}

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
	
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
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
		
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "globalColor");
		
		glUseProgram(shaderProgram);
		
		glUniform4f(vertexColorLocation, 0.5f, sin(ticks), 0.0f, 1.0f);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// Always the last statement in the render loop
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_Quit();
	
	return 0;
}
