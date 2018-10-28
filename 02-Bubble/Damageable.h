#include "EntityComponent.h"
#pragma once
class Damageable : public EntityComponent
{
public:
	Damageable(float health);
	~Damageable();

	virtual void AddDamage(float ammount, glm::fvec2 fDir); //Adds damage and pushes entity to fDir
	virtual void Die();
private:
	float health;

};

