#include "camera.hpp"

Camera::Camera()
{
	_shader = {"/Users/zehreken/Development/opengl_playground/opengl_playground/camera/vertexe.txt",
		"/Users/zehreken/Development/opengl_playground/opengl_playground/camera/fragmente.txt"};
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	
	glm::vec3 cameraTarget = glm::vec3(0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	
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
}
