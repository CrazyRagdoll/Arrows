#include "Arrow.h"

Arrow::Arrow(glm::vec3 pos, glm::vec3 dir, float speed, float width, int lifeTime, string texture) :
	_gravity(-0.002f),
	_floorTime(100),
	_stuck(false),
	_active(true)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
	_width = width;
	_velocity = dir * speed;
	_skin = texture;
}

Arrow::~Arrow()
{

}

bool Arrow::update(float dt)
{	
	//checking to see if the arrow is still in flight or not, then updating its position and deleting after a certain time
	if(_stuck){
		_floorTime--;
	} else {
		//SUVAT to figure out the effects of gravity on the velocity v = u + at
		_velocity.y += (dt * _gravity);
		_position += _velocity;
		_lifeTime--;
	}

	if(!_active || _lifeTime == 0 || _floorTime == 0) { return true; }
	return false;
}

void Arrow::clean()
{

}

bool Arrow::checkFloorCollision(Floor& floor)
{
	return(_position.y - _width < floor._y &&
		   _position.x < floor._x + floor._width &&
		   _position.x > floor._x - floor._width &&
		   _position.z < floor._z + floor._width &&
		   _position.z > floor._z - floor._width); 
}

//Checking for collisions with agents
bool Arrow::checkAgentCollision(Agent& agent)
{
	return(_position.x - _width < agent._position.x + agent._width &&
			_position.x + _width > agent._position.x - agent._width &&
			_position.y - _width < agent._position.y + agent._height &&
			_position.y + _width > agent._position.y - agent._height &&
			_position.z - _width < agent._position.z + agent._width &&
			_position.z + _width > agent._position.z - agent._width);
}

//Checking only the TIP of the arrow against stuffs
bool Arrow::checkTerrainCollision(Terrain& terrain)
{
	return(_position.x < terrain._position.x + terrain._size &&
		   _position.x > terrain._position.x - terrain._size &&
		   _position.y < terrain._position.y + terrain._size &&
		   _position.y > terrain._position.y - terrain._size &&
		   _position.z < terrain._position.z + terrain._size &&
		   _position.z > terrain._position.z - terrain._size); 
}

//Checking collisions with cubes
bool Arrow::checkCollision(Cube& cube)
{
	return(_position.x + _width > cube._x - cube._width &&
		_position.x - _width < cube._x + cube._width &&
		_position.y + _width > cube._y - cube._width &&
		_position.y - _width < cube._y + cube._width &&
		_position.z + _width > cube._z - cube._width &&
		_position.z - _width < cube._z + cube._width); 
}

void Arrow::init()
{

	if (_skin != "NONE")
	{
		_texture.id = _textureLoader.loadGLTexture(_skin);	
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
    vertexData[0].setPosUV(-_width + _position.x,-_width + _position.y,-_width + _position.z,   0.0f, 0.0f);
    vertexData[1].setPosUV( _width + _position.x,-_width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[2].setPosUV(-_width + _position.x,-_width + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[3].setPosUV( _width + _position.x,-_width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[4].setPosUV( _width + _position.x,-_width + _position.y, _width + _position.z,   1.0f, 1.0f);
    vertexData[5].setPosUV(-_width + _position.x,-_width + _position.y, _width + _position.z,   0.0f, 1.0f);

    // top
    vertexData[6].setPosUV(-_width + _position.x, _width + _position.y,-_width + _position.z,   0.0f, 0.0f);
    vertexData[7].setPosUV(-_width + _position.x, _width + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[8].setPosUV( _width + _position.x, _width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[9].setPosUV( _width + _position.x, _width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[10].setPosUV(-_width + _position.x, _width + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[11].setPosUV( _width + _position.x, _width + _position.y, _width + _position.z,   1.0f, 1.0f);

    // right
    vertexData[12].setPosUV( _width + _position.x,-_width + _position.y, _width + _position.z,   1.0f, 0.0f); 
    vertexData[13].setPosUV( _width + _position.x,-_width + _position.y,-_width + _position.z,   0.0f, 0.0f); 
    vertexData[14].setPosUV( _width + _position.x, _width + _position.y,-_width + _position.z,   0.0f, 1.0f); 
    vertexData[15].setPosUV( _width + _position.x,-_width + _position.y, _width + _position.z,   1.0f, 0.0f); 
    vertexData[16].setPosUV( _width + _position.x, _width + _position.y,-_width + _position.z,   0.0f, 1.0f); 
    vertexData[17].setPosUV( _width + _position.x, _width + _position.y, _width + _position.z,   1.0f, 1.0f); 

	// left
    vertexData[18].setPosUV(-_width + _position.x,-_width + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[19].setPosUV(-_width + _position.x, _width + _position.y,-_width + _position.z,   1.0f, 1.0f);
    vertexData[20].setPosUV(-_width + _position.x,-_width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[21].setPosUV(-_width + _position.x,-_width + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[22].setPosUV(-_width + _position.x, _width + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[23].setPosUV(-_width + _position.x, _width + _position.y,-_width + _position.z,   1.0f, 1.0f);

    // front
    vertexData[24].setPosUV(-_width + _position.x,-_width + _position.y, _width + _position.z,   1.0f, 0.0f);
    vertexData[25].setPosUV( _width + _position.x,-_width + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[26].setPosUV(-_width + _position.x, _width + _position.y, _width + _position.z,   1.0f, 1.0f);
    vertexData[27].setPosUV( _width + _position.x,-_width + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[28].setPosUV( _width + _position.x, _width + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[29].setPosUV(-_width + _position.x, _width + _position.y, _width + _position.z,   1.0f, 1.0f);

    // back
    vertexData[30].setPosUV(-_width + _position.x,-_width + _position.y,-_width + _position.z,   0.0f, 0.0f);
    vertexData[31].setPosUV(-_width + _position.x, _width + _position.y,-_width + _position.z,   0.0f, 1.0f);
    vertexData[32].setPosUV( _width + _position.x,-_width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[33].setPosUV( _width + _position.x,-_width + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[34].setPosUV(-_width + _position.x, _width + _position.y,-_width + _position.z,   0.0f, 1.0f);
    vertexData[35].setPosUV( _width + _position.x, _width + _position.y,-_width + _position.z,   1.0f, 1.0f);

	for (int i = 0; i < 36; i++) {
		vertexData[i].setColor(255, 255, 255, 255);
	}

	_vertexSize = sizeof(vertexData);
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, _vertexSize, vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Arrow::draw()
{	
		//bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Activating and binding the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

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
	glDrawArrays(GL_TRIANGLES, 0, _vertexSize);

	//disable the vertex attrib array. Not optional
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//unbind the  texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}