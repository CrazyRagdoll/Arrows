#include "Sprite.h"

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

	float vertexData[12];

	// First triangle
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	// Second triangle
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;

	vertexData[10]= x + width;
	vertexData[11]= y + height;

	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}
