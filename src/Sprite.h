#ifndef SPRITE_H_
#define SPRITE_H_

#include <GL/glew.h>
#include <string>

#include "GLTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);

	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

};

#endif
