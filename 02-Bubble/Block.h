#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
class Block : public Entity
{
public:
	Block(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	Texture tex;
	~Block();
};

