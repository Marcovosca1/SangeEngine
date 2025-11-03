#pragma once
#include <string>

class Texture
{
	public:
	unsigned int ID;
	int width, height, nrChannels;

	Texture(const char* imagePath, bool flipVertically = true);

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	void setWrapping(int wrapS, int wrapT) const;
	void setFiltering(int minFilter, int magFilter) const;

	~Texture();
};

