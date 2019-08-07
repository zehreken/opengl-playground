#include "world.hpp"

World::World()
{
	_shader = {"/Users/zehreken/Development/opengl_playground/opengl_playground/3_camera/vertex3.txt",
		"/Users/zehreken/Development/opengl_playground/opengl_playground/3_camera/fragment3.txt"};
	
	float vertices[] =
	{
		// top right
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		// bottom right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		// bottom left
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		// top left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
	};
	
	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};
	
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void World::update(int deltaX, int deltaY)
{
	_camera.update(deltaX, deltaY);
	_shader.use();
	
	glm::mat4 model(1.0f);
	
	unsigned int modelLoc = glGetUniformLocation(_shader.ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(_shader.ID, "view");
	unsigned int projLoc  = glGetUniformLocation(_shader.ID, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera.getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_camera.getProjection()));
	
	unsigned int colorLoc = glGetUniformLocation(_shader.ID, "Color");
	glUniform4f(colorLoc, 1.0f, 0.0f, 0.215f, 1.0f);
	
	glBindVertexArray(_vao);
	for (int i = 0; i < 21; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, i * 0.0f, -10 + i * 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	
	// Green quad, floor
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, 0.0f, 1.0f, 0.215f, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	// Blue quad, ceiling
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

void World::onKeyDown(SDL_Keycode key)
{
	_camera.onKeyDown(key);
}

void World::onKeyUp(SDL_Keycode key)
{
	_camera.onKeyUp(key);
}
