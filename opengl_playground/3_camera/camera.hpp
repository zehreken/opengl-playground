#ifndef camera_hpp
#define camera_hpp

#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	void update();
private:
	Shader _shader;
	glm::mat4 _view;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

#endif /* camera_hpp */
