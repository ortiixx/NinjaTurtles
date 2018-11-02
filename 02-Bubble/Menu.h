#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
class Menu : public Entity
{
public:
	Menu(ShaderProgram &shaderProgram);
	~Menu();
	void update(int deltatime);
	Texture tex;
};

