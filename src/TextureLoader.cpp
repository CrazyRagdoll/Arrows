#include "TextureLoader.h"

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{

}

int TextureLoader::loadGLTexture(string imagePath)
{
	/* load an image file directly as a new OpenGL texture */
	_texture[0] = SOIL_load_OGL_texture
		(
		imagePath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(_texture[0] == 0)
		return false;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture[0]);

	return _texture[0];
}