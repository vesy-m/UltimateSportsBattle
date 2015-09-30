#pragma once

#include <SFML\OpenGL.hpp>
#include <string>
#include <map>
#include "Texture.h"
#include <il.h>
#include <iostream>
#include <stdexcept>

class TextureManager
{
public:
	void		loadTexture(const std::string & filename);
	Texture		*getTexture(const std::string &fileName);
	~TextureManager();
	static TextureManager& getInstance()
	{
		static TextureManager    instance;
		return instance;
	}
private:
	TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	std::map<std::string, Texture> textureMap;
};
