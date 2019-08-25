#ifndef model_hpp
#define model_hpp

#include "mesh.hpp"
#include "../shader.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(char *path);
	void draw(Shader shader);
private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif /* model_hpp */
