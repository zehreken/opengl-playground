#ifndef basicLighting_hpp
#define basicLighting_hpp

#include <SDL2/SDL.h>
#include "../3_camera/camera.hpp"
#include "../shader.h"

class BasicLighting
{
public:
	BasicLighting();
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

#endif /* basicLighting_hpp */
