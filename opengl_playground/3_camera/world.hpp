#ifndef world_hpp
#define world_hpp

#include "camera.hpp"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class World
{
public:
	World();
	void update(int deltaX, int deltaY);
	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);
private:
	Camera _camera;
	Shader _shader;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

#endif /* world_hpp */
