#include "Cube.h"
#include "Vertex.h"

#include <iostream>
#include <cstddef>

Cube::Cube()
{
	_vboID = 0;
}

Cube::~Cube()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Cube::init(float x, float y, float z, float width)
{
	_x = x;
	_y = y;
	_z = z;
	_width = width;

	_position = glm::vec3(x,y,z);

	_texture.id = _textureLoader.loadGLTexture("../src/Textures/NeHe.bmp");

	if(_texture.id == 0)
	{
		std::cout << "Could not find texture" << std::endl;
	}

	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

	    // Make a cube out of triangles (two triangles per side)
    	Vertex vertexData[36];
        //  X     Y     Z       U     V
        // bottom
        vertexData[0].setPosUV(-_width + x,-_width + y,-_width + z,   0.0f, 0.0f);
        vertexData[1].setPosUV( _width + x,-_width + y,-_width + z,   1.0f, 0.0f);
        vertexData[2].setPosUV(-_width + x,-_width + y, _width + z,   0.0f, 1.0f);
        vertexData[3].setPosUV( _width + x,-_width + y,-_width + z,   1.0f, 0.0f);
        vertexData[4].setPosUV( _width + x,-_width + y, _width + z,   1.0f, 1.0f);
        vertexData[5].setPosUV(-_width + x,-_width + y, _width + z,   0.0f, 1.0f);

        // top
        vertexData[6].setPosUV(-_width + x, _width + y,-_width + z,   0.0f, 0.0f);
        vertexData[7].setPosUV(-_width + x, _width + y, _width + z,   0.0f, 1.0f);
        vertexData[8].setPosUV( _width + x, _width + y,-_width + z,   1.0f, 0.0f);
        vertexData[9].setPosUV( _width + x, _width + y,-_width + z,   1.0f, 0.0f);
        vertexData[10].setPosUV(-_width + x, _width + y, _width + z,   0.0f, 1.0f);
        vertexData[11].setPosUV( _width + x, _width + y, _width + z,   1.0f, 1.0f);

        // right
        vertexData[12].setPosUV( _width + x,-_width + y, _width + z,   1.0f, 0.0f); 
        vertexData[13].setPosUV( _width + x,-_width + y,-_width + z,   0.0f, 0.0f); 
        vertexData[14].setPosUV( _width + x, _width + y,-_width + z,   0.0f, 1.0f); 
        vertexData[15].setPosUV( _width + x,-_width + y, _width + z,   1.0f, 0.0f); 
        vertexData[16].setPosUV( _width + x, _width + y,-_width + z,   0.0f, 1.0f); 
        vertexData[17].setPosUV( _width + x, _width + y, _width + z,   1.0f, 1.0f); 

	// left
        vertexData[18].setPosUV(-_width + x,-_width + y, _width + z,   1.0f, 1.0f);
        vertexData[19].setPosUV(-_width + x, _width + y,-_width + z,   0.0f, 0.0f);
        vertexData[20].setPosUV(-_width + x,-_width + y,-_width + z,   1.0f, 0.0f);
        vertexData[21].setPosUV(-_width + x,-_width + y, _width + z,   0.0f, 1.0f);
        vertexData[22].setPosUV(-_width + x, _width + y, _width + z,   1.0f, 0.0f);
        vertexData[23].setPosUV(-_width + x, _width + y,-_width + z,   0.0f, 0.0f);

        // front
        vertexData[24].setPosUV(-_width + x,-_width + y, _width + z,   1.0f, 0.0f);
        vertexData[25].setPosUV( _width + x,-_width + y, _width + z,   0.0f, 0.0f);
        vertexData[26].setPosUV(-_width + x, _width + y, _width + z,   1.0f, 1.0f);
        vertexData[27].setPosUV( _width + x,-_width + y, _width + z,   0.0f, 0.0f);
        vertexData[28].setPosUV( _width + x, _width + y, _width + z,   0.0f, 1.0f);
        vertexData[29].setPosUV(-_width + x, _width + y, _width + z,   1.0f, 1.0f);

        // back
        vertexData[30].setPosUV(-_width + x,-_width + y,-_width + z,   0.0f, 0.0f);
        vertexData[31].setPosUV(-_width + x, _width + y,-_width + z,   0.0f, 1.0f);
        vertexData[32].setPosUV( _width + x,-_width + y,-_width + z,   1.0f, 0.0f);
        vertexData[33].setPosUV( _width + x,-_width + y,-_width + z,   1.0f, 0.0f);
        vertexData[34].setPosUV(-_width + x, _width + y,-_width + z,   0.0f, 1.0f);
        vertexData[35].setPosUV( _width + x, _width + y,-_width + z,   1.0f, 1.0f);

	for (int i = 0; i < 36; i++) {
		vertexData[i].setColor(255, 255, 255, 255);
	}
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw()
{
	//bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//tell opengl that we want to use the first arrribute array.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//This is the position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//This is the color attribute pointer	
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//this is the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
	//Draw the 6 verticies to the screen
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//disable the vertex attrib array. Not optional
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}