#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	void update(int deltaX, int deltaY);
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::vec3 getPosition();
	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);
private:
	glm::mat4 _view;
	glm::mat4 _projection;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraRight;
	glm::vec3 _cameraUp;
	glm::vec3 _cameraForward;
	float _yaw;
	float _pitch;
	bool _isForward = false;
	bool _isLeft = false;
	bool _isBack = false;
	bool _isRight = false;
};

#endif /* camera_hpp */
