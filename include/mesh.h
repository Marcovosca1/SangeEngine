#pragma once
#include <glad/glad.h>
#include "vertex.h"

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

