#include "camera.hpp"

Camera::Camera()
{
	_projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
	
	_cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	
	_cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_cameraRight = glm::cross(_cameraForward, _cameraUp);
	
	_yaw = -90.0f;
	_pitch = 0.0f;
	
	_view = glm::lookAt(_cameraPos, // position vector
					   _cameraPos + _cameraForward, // target vector
					   _cameraUp); // up vector
}

void Camera::update(int deltaX, int deltaY)
{
	float sensitivity = 0.05f;
	_yaw += deltaX * sensitivity;
	_pitch -= deltaY * sensitivity;
	if (_pitch > 89.0f) _pitch = 89.0f;
	if (_pitch < -89.0f) _pitch = -89.0f;
	
	glm::vec3 forward = glm::vec3(0.0f);
	forward.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	forward.y = sin(glm::radians(_pitch));
	forward.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
	_cameraForward = glm::normalize(forward);
	
	_cameraRight = glm::normalize(glm::cross(_cameraForward, _cameraUp));
	
	
	_view = glm::lookAt(_cameraPos,
						_cameraPos + _cameraForward,
						_cameraUp);
	
	// For FPS like camera movement
	_cameraForward.y = 0.0f;
	// ============================
	
	float factor = 0.1;
	if (_isForward)
		_cameraPos += _cameraForward * factor;
	if (_isLeft)
		_cameraPos -= _cameraRight * factor;
	if (_isBack)
		_cameraPos -= _cameraForward * factor;
	if (_isRight)
		_cameraPos += _cameraRight * factor;
}

glm::mat4 Camera::getView()
{
	return _view;
}

glm::mat4 Camera::getProjection()
{
	return _projection;
}

void Camera::onKeyDown(SDL_Keycode key)
{
	switch (key)
	{
		case SDLK_w:
			_isForward = true;
			break;
		case SDLK_a:
			_isLeft = true;
			break;
		case SDLK_s:
			_isBack = true;
			break;
		case SDLK_d:
			_isRight = true;
			break;
	}
}

void Camera::onKeyUp(SDL_Keycode key)
{
	switch (key)
	{
		case SDLK_w:
			_isForward = false;
			break;
		case SDLK_a:
			_isLeft = false;
			break;
		case SDLK_s:
			_isBack = false;
			break;
		case SDLK_d:
			_isRight = false;
			break;
	}
}
