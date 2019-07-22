#ifndef world_hpp
#define world_hpp

#include "shader.h"

class World
{
public:
	World();
	void update();
private:
	Shader _shader;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
};

#endif /* world_hpp */
