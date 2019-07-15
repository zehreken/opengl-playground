#ifndef rotatingPlane_hpp
#define rotatingPlane_hpp

#include "shader.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class RotatingPlane
{
public:
	RotatingPlane();
	void update();
private:
	Shader _shader;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

#endif /* rotatingPlane_hpp */
