#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{

}

GLTexture TextureCache::getTexture(std::string texturePath)
{

	//look up the texture	
	auto mit = _textureMap.find(texturePath);

	//check if its not in the map
	if(mit == _textureMap.end())
	{
		//load the teture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		
		//inseter it into the map
		_textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Loaded texture!\n";

		return newTexture;
	}

	std::cout << "Used cached texture!\n";
	return mit->second;
}
