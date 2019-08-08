#ifndef color_hpp
#define color_hpp

#include "../3_camera/camera.hpp"
#include <SDL2/SDL.h>
#include "shader.h"

class Color
{
public:
	Color();
	void update(int deltaX, int deltaY);
	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);
private:
	Camera _camera;
	Shader _shader;
	Shader _lightShader;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	unsigned int _lightVao;
};

#endif /* color_hpp */
