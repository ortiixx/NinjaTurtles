#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
class Enemy : public Entity
{
public:
	Enemy(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	Texture tex;
	~Enemy();
private:
	Sprite* spr;
	glm::ivec2 vel = glm::ivec2(0);
	Entity* player;
};

