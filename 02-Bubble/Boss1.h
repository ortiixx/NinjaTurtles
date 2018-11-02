#pragma once
#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>
#include "Projectile.h"

class Boss1 : public Entity
{
public:
	Boss1(ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	Texture tex;
	void setObjective(Entity* e) { player = e; }
	virtual void GetDamage();
	~Boss1();
protected:
	float attackTimer = 0;
	float speed = 4;
	ShaderProgram prog;
	std::vector<Projectile*> projectiles;
	Sprite* spr;
	glm::fvec2 vel = glm::fvec2(0);
	Entity* player = nullptr;
	enum State;
	State currentState;
	glm::fvec2 CalculateDir();
	void Attack();
	void UpdateProjectiles(int deltaTime);
	void Shoot();
};

