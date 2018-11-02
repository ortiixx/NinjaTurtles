#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>

class Enemy2 : public Entity
{
public:
	Enemy2(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	Texture tex;
	void setObjective(Entity* e) { player = e; }
	virtual void GetDamage();
	~Enemy2();
protected:
	float attackTimer = 0;
	float recoveryTimer = 0;
	Sprite* spr;
	glm::fvec2 vel = glm::fvec2(0);
	Entity* player = nullptr;
	enum Animations {
		WALK,
		ATTACK,
		DIE,
		HURT
	};

	enum State {
		CHASE,
		ATTACKING,
		EVADE,
	};

	State currentState;
	glm::fvec2 CalculateDir();
	virtual void Attack();
};

