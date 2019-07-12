#ifndef cubes_hpp
#define cubes_hpp

#include "shader.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Cubes
{
public:
	Cubes();
	void update();
private:
	Shader _shader;
	unsigned int _texture0;
	unsigned int _texture1;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

#endif /* cubes_hpp */
