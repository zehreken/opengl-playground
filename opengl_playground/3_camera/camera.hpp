#ifndef camera_hpp
#define camera_hpp

#include "shader.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	void update(int mouseX, int mouseY);
	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);
private:
	Shader _shader;
	glm::mat4 _view;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraRight;
	glm::vec3 _cameraUp;
	glm::vec3 _cameraForward;
	float _yaw;
	float _pitch;
	bool _isUp = false;
	bool _isLeft = false;
	bool _isDown = false;
	bool _isRight = false;
};

#endif /* camera_hpp */
