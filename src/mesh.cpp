#include "mesh.h"

Mesh::Mesh(const Vertex vertices) : data(vertices)
{
	//setup buffers
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// -- Positions --
	glGenBuffers(1, &VBO_positions);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferData(GL_ARRAY_BUFFER, data.position.size() * sizeof(float), data.position.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);       // aici am link-uit atributul 0 din vertex shader la datele din VBO
	glEnableVertexAttribArray(0);

	// -- Colors --
	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, data.color.size() * sizeof(float), data.color.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);       // aici am link-uit atributul 1 din vertex shader la datele din VBO
	glEnableVertexAttribArray(1);

	// -- Texture Coordinates --
	glGenBuffers(1, &VBO_texCoords);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_texCoords);
	glBufferData(GL_ARRAY_BUFFER, data.texCoords.size() * sizeof(float), data.texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);       // aici am link-uit atributul 2 din vertex shader la datele din VBO
	glEnableVertexAttribArray(2);

	// -- Indices --
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(unsigned int), data.indices.data(), GL_STATIC_DRAW);

	//unbinding
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_positions);
	glDeleteBuffers(1, &VBO_colors);
	glDeleteBuffers(1, &VBO_texCoords);
	glDeleteBuffers(1, &EBO);
}

void Mesh::draw() const
{
	glBindVertexArray(VAO);

	if (!data.indices.empty()) {
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(data.indices.size()), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(data.position.size() / 3));
	}

	glBindVertexArray(0);
}
