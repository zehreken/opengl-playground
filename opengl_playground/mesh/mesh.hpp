#ifndef mesh_hpp
#define mesh_hpp

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "../shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Norma;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	// Mesh Data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	// Functions
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
private:
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	void setupMesh();
};

#endif /* mesh_hpp */
