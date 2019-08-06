#ifndef color_hpp
#define color_hpp

#include "../3_camera/camera.hpp"
#include <SDL2/SDL.h>
#include "shader.h"

class Color
{
public:
	Color();
	void update();
private:
	Camera _camera;
	Shader _shader;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

#endif /* color_hpp */
