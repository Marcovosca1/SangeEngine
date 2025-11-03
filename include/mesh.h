#pragma once
#include <glad/glad.h>
#include <vector>

struct Vertex {
	std::vector<float> position; // 3 floats
	std::vector<float> color;    // 3 floats
	std::vector<float> texCoords; // 2 floats
	std::vector<unsigned int> indices;
};

class Mesh
{
public:
	Vertex data;

	// OpenGL handles
	unsigned int VAO;
	unsigned int VBO_positions, VBO_colors, VBO_texCoords;
	unsigned int EBO;

	Mesh(const Vertex vertices);
	~Mesh();

	void draw() const;
};

