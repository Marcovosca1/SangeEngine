#include "model.h"
#include <iostream>
#include <filesystem>

Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::draw() const
{
	for (const auto& mesh : meshes) {
		mesh->draw();
	}
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | 
		aiProcess_FlipUVs | 
		aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = std::filesystem::path(path).parent_path().string();
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

std::shared_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	Vertex vertexData;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		// Positions
		vertexData.position.push_back(mesh->mVertices[i].x);
		vertexData.position.push_back(mesh->mVertices[i].y);
		vertexData.position.push_back(mesh->mVertices[i].z);

		// Colors
		if (mesh->HasVertexColors(0)) {
			vertexData.color.push_back(mesh->mColors[0][i].r);
			vertexData.color.push_back(mesh->mColors[0][i].g);
			vertexData.color.push_back(mesh->mColors[0][i].b);
		} 
		else {
			vertexData.color.push_back(1.0f);
			vertexData.color.push_back(1.0f);
			vertexData.color.push_back(1.0f);
		}

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) {
			vertexData.texCoords.push_back(mesh->mTextureCoords[0][i].x);
			vertexData.texCoords.push_back(mesh->mTextureCoords[0][i].y);
		} 
		else {
			vertexData.texCoords.push_back(0.0f);
			vertexData.texCoords.push_back(0.0f);
		}
	}

	// Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			vertexData.indices.push_back(face.mIndices[j]);
	}

	return std::make_shared<Mesh>(vertexData);

}

