#pragma once

#include <vector>
#include <string>
#include <memory>
#include "mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model
{
public:
	Model(const std::string& path);
	~Model() = default;

	void draw() const;

private:
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::string directory;

	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

};

