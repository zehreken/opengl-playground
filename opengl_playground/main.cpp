#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	// Second texture
	surface = IMG_Load("/Users/zehreken/Development/opengl_playground/opengl_playground/grass.png");
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	SDL_FreeSurface(surface);
	
	// x, y, z, r, g, b, u, v
	// UV coordinates are flipped on y-axis because
	// Most file formats have topdown indexing but OpenGL has the opposite
	float vertices[] =
	{
		// top right
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,
		// bottom right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.6f, 0.6f,
		// bottom left
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.4f, 0.6f,
		// top left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.4f, 0.4f
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
	
	shader.use(); // don't forget to activate the shader before setting uniforms!
	glUniform1i(glGetUniformLocation(shader.ID, "texture0"), 0); // set it manually
	shader.setInt("texture1", 1); // or with shader class
	
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
		shader.setFloat("lever", sin(ticks));
//		shader.setFloat("offset", sin(ticks));
		
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "globalColor");
		
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(ticks * 10), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::translate(trans, glm::vec3(0.0f, -0.0f, 0.0f));
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
//		glUseProgram(shaderProgram);
		
		
		shader.use();
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600, 0.1f, 100.0f);
		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		unsigned int viewLoc  = glGetUniformLocation(shader.ID, "view");
		unsigned int projLoc  = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		
//		glUniform4f(vertexColorLocation, 0.5f, sin(ticks), 0.0f, 1.0f);
		
		glBindVertexArray(vao);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glm::mat4 trans2 = glm::mat4(1.0f);
//		trans2 = glm::rotate(trans2, glm::radians(ticks), glm::vec3(0.0f, 0.0f, 1.0f));
		trans2 = glm::scale(trans2, glm::vec3(sin(ticks), sin(ticks), 0.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans2));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		// Always the last statement in the render loop
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	
	SDL_Quit();
	
	return 0;
}
