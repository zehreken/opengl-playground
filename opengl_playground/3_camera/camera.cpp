#include "camera.hpp"

Camera::Camera()
{
	_shader = {"/Users/zehreken/Development/opengl_playground/opengl_playground/3_camera/vertex3.txt",
		"/Users/zehreken/Development/opengl_playground/opengl_playground/3_camera/fragment3.txt"};
	
	_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	
	glm::vec3 cameraTarget = glm::vec3(0.0f);
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - cameraTarget);
	
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	
	_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), // position vector
					   glm::vec3(0.0f, 0.0f, 0.0f), // target vector
					   glm::vec3(0.0f, 1.0f, 0.0f)); // up vector
	
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

void Camera::update()
{
	_shader.use();
	
	glm::mat4 model = glm::mat4(1.0f);
	
	float radius = 10.0f;
	float cameraX = sin(SDL_GetTicks() / 1000.0f) * radius;
	float cameraZ = cos(SDL_GetTicks() / 1000.0f) * radius;
	if (_isUp)
		_cameraPos.y += 0.2f;
	if (_isLeft)
		_cameraPos.x -= 0.2f;
	if (_isDown)
		_cameraPos.y -= 0.2f;
	if (_isRight)
		_cameraPos.x += 0.2f;
		
	_view = glm::lookAt(_cameraPos,
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 1.0f, 0.0f));
	
	glm::mat4 projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
	
	unsigned int modelLoc = glGetUniformLocation(_shader.ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(_shader.ID, "view");
	unsigned int projLoc  = glGetUniformLocation(_shader.ID, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	glBindVertexArray(_vao);
	for (int i = 0; i < 20; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, i * 0.0f, i * 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Camera::onKeyDown(SDL_Keycode key)
{
	_isUp = key == SDLK_w;
	_isLeft = key == SDLK_a;
	_isDown = key == SDLK_s;
	_isRight = key == SDLK_d;
}

void Camera::onKeyUp(SDL_Keycode key)
{
	if (key == SDLK_w)
		_isUp = false;
	if (key == SDLK_a)
		_isLeft = false;
	if (key == SDLK_s)
		_isDown = false;
	if (key == SDLK_d)
		_isRight = false;
}
