#include "model.hpp"

Model::Model(char *path)
{
	loadModel(path);
}

void Model::draw(Shader shader)
{
	for (int i = 0; i < _meshes.size(); i++)
	{
		_meshes[i].draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
}
