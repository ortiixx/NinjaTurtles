#pragma once
#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
class Level_1 : public Entity
{
public:
	Level_1(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	Texture tex;
	~Level_1();

};

