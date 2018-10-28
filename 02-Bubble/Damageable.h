#include "EntityComponent.h"
#pragma once
class Damageable : public EntityComponent
{
public:
	Damageable(float health);
	~Damageable();

	virtual void AddDamage(float ammount, glm::ivec2 fDir); //Adds damage and pushes entity to fDir
	virtual void Die();
private:
	float health;

};

