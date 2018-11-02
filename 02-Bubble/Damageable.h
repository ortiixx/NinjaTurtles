#include "EntityComponent.h"
#pragma once
class Damageable : public EntityComponent
{
public:
	Damageable();
	Damageable(float health);
	~Damageable();

	virtual void AddDamage(float ammount, glm::fvec2 fDir, int sender); //Adds damage and pushes entity to fDir
	virtual void Die();
	float getHealth(){ return health; }
protected:
	float health;

};

