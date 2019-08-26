#ifndef model_hpp
#define model_hpp

#include "mesh.hpp"
#include "../shader.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Model
{
public:
	Model();
	void init(char *path);
	void draw(Shader shader);
private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int loadTextureFromFile(std::string path, std::string directory);
};

#endif /* model_hpp */
