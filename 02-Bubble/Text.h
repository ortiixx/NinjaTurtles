#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
class Text : public Entity
{
public:
	Text(ShaderProgram &shaderProgram, int value);
	~Text();
	void update(int deltaTime);
	Texture tex;
};

