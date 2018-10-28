#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>

class Enemy : public Entity
{
public:
	Enemy(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	Texture tex;
	~Enemy();
private:
	float attackTimer = 0;
	Sprite* spr;
	glm::fvec2 vel = glm::fvec2(0);
	Entity* player = nullptr;
	enum State;
	State currentState;
	glm::fvec2 CalculateDir();
	void Attack();
};

