#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>

class Enemy3 : public Entity
{
public:
	Enemy3(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	Texture tex;
	void setObjective(Entity* e) { player = e; }
	virtual void GetDamage();
	~Enemy3();
protected:
	float attackTimer = 0;
	float recoveryTimer = 0;
	float hideTimer = 0;
	Sprite* spr;
	enum State {
		CHASE,
		ATTACKING,
		EVADE,
		UNDERGROUND
	};
	enum Animations {
		WALK,
		ATTACK,
		DIE,
		HURT,
		SPAWN,
		UNSPAWN
	};
	State currentState;
	glm::fvec2 GetSpawnPoint();
	glm::fvec2 vel = glm::fvec2(0);
	Entity* player = nullptr;
	glm::fvec2 CalculateDir();
	virtual void Attack();
};

