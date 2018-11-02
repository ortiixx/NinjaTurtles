#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"

class Level_2 : public Entity
{
public:
	Level_2(ShaderProgram &shaderProgram);
	~Level_2();
	Texture tex;
	void update(int deltatime);
};

