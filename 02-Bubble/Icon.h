#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"

class Icon : public Entity
{
public:
	Icon(ShaderProgram &shaderProgram);
	~Icon();
	void update(int deltatime);
	Texture tex;
	int sel = 0;
};

