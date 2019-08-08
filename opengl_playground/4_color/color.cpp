#include "color.hpp"

Color::Color()
{
	_shader = {"/Users/zehreken/Development/opengl_playground/opengl_playground/4_color/vertex4.txt",
		"/Users/zehreken/Development/opengl_playground/opengl_playground/4_color/fragment4.txt"};
	
	_lightShader = {"/Users/zehreken/Development/opengl_playground/opengl_playground/4_color/vertex4.txt",
		"/Users/zehreken/Development/opengl_playground/opengl_playground/4_color/lightF4.txt"};
	
	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		
		-0.5f, 0.5f,  0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
	};
	
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	// light box
	glGenVertexArrays(1, &_lightVao);
	glBindVertexArray(_lightVao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glEnable(GL_DEPTH_TEST);
}

void Color::update(int deltaX, int deltaY)
{
	_camera.update(deltaX, deltaY);
	_shader.use();
	unsigned int objectColorLoc = glGetUniformLocation(_shader.ID, "objectColor");
	glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.0f);
	unsigned int lightColorLoc = glGetUniformLocation(_shader.ID, "lightColor");
	glUniform3f(lightColorLoc, 0.0f, 1.0f, 0.0f);
	
	glm::mat4 model = glm::mat4(1.0f);
	
	unsigned int modelLoc = glGetUniformLocation(_shader.ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(_shader.ID, "view");
	unsigned int projLoc  = glGetUniformLocation(_shader.ID, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera.getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_camera.getProjection()));
	
	// Render cube
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	// Render light object, not the actual light
	_lightShader.use();
	modelLoc = glGetUniformLocation(_lightShader.ID, "model");
	viewLoc  = glGetUniformLocation(_lightShader.ID, "view");
	projLoc  = glGetUniformLocation(_lightShader.ID, "projection");
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, glm::vec3(2.0f, 0.0f, 0.0f));
	modelLoc = glGetUniformLocation(_shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera.getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_camera.getProjection()));
	
	glBindVertexArray(_lightVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glBindVertexArray(0);
}

void Color::onKeyDown(SDL_Keycode key)
{
	_camera.onKeyDown(key);
}

void Color::onKeyUp(SDL_Keycode key)
{
	_camera.onKeyUp(key);
}
