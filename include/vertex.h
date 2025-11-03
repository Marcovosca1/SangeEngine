#pragma once

#include <vector>

struct Vertex {
	std::vector<float> position; // 3 floats
	std::vector<float> color;    // 3 floats
	std::vector<float> texCoords; // 2 floats
	std::vector<unsigned int> indices;
};