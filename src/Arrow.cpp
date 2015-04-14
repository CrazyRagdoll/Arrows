#include "Arrow.h"

Arrow::Arrow(glm::vec3 pos, glm::vec3 dir, float speed, float width, int lifeTime) :
	_gravity(-0.002f),
	_floorTime(100),
	_stuck(false)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
	_width = width;
	_velocity = dir * speed;
}

Arrow::~Arrow()
{

}

void Arrow::init()
{
	Cube::init(_position.x, _position.y, _position.z, _width, "NONE");

/*
	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

    // Make a cube out of triangles (two triangles per side)
	Vertex vertexData[18];
    //  X     Y     Z       U     V
    // bottom
    vertexData[0].setPosUV(x       , y       , z       ,   0.0f, 0.0f);
    vertexData[1].setPosUV(x       , y + 0.5f, z - 1.0f,   0.0f, 0.0f);
    vertexData[2].setPosUV(x + 0.1f, y + 0.1f, z - 1.0f,   0.0f, 0.0f);
    vertexData[3].setPosUV(x       , y       , z       ,   0.0f, 0.0f);
    vertexData[4].setPosUV(x + 0.1f, y + 0.1f, z - 1.0f,   0.0f, 0.0f);
    vertexData[5].setPosUV(x + 0.4f, y - 0.2f, z - 1.0f,   0.0f, 0.0f);
    vertexData[6].setPosUV(x       , y       , z       ,   0.0f, 0.0f);
    vertexData[7].setPosUV(x + 0.4f, y - 0.4f, z - 1.0f,   0.0f, 0.0f);
    vertexData[8].setPosUV(x       , y - 0.1f, z - 1.0f,   0.0f, 0.0f);
    vertexData[9].setPosUV(x       , y       , z       ,   0.0f, 0.0f);
    vertexData[10].setPosUV(x       , y - 0.1f, z - 1.0f,   0.0f, 0.0f);
    vertexData[11].setPosUV(x - 0.4f, y - 0.4f, z - 1.0f,   0.0f, 0.0f);
    vertexData[12].setPosUV(x       , y       , z       ,   0.0f, 0.0f);
    vertexData[13].setPosUV(x - 0.4f, y - 0.4f, z - 1.0f,   0.0f, 0.0f);
    vertexData[14].setPosUV(x + 0.1f, y + 0.1f, z - 1.0f,   0.0f, 0.0f);
    vertexData[15].setPosUV(x       , y       , z       ,   0.0f, 0.0f);
    vertexData[16].setPosUV(x + 0.1f, y + 0.1f, z - 1.0f,   0.0f, 0.0f);
    vertexData[17].setPosUV(x       , y + 0.5f, z - 1.0f,   0.0f, 0.0f);


	for (int i = 0; i < 18; i++) {
		vertexData[i].setColor(255, 255, 255, 255);
	}
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
}

void Arrow::draw()
{	
	Cube::draw();
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

	if(_lifeTime == 0 || _floorTime == 0) { return true; }
	return false;
}

void Arrow::clean()
{

}

bool Arrow::checkFloorCollision(Floor& floor)
{
	//if(_crouched) { _playerHeight = 5.0f; } else { _playerHeight = 10.0f; }
	return(_position.y - _width < floor._y &&
		   _position.x < floor._x + floor._width &&
		   _position.x > floor._x - floor._width &&
		   _position.z < floor._z + floor._width &&
		   _position.z > floor._z - floor._width); 
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