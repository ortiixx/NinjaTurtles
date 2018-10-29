#pragma once
#include "Damageable.h"
class HammerDamageable :
	public Damageable
{
public:
	HammerDamageable(float ammount);
	~HammerDamageable();
	virtual void AddDamage(float ammount, glm::fvec2 fDir, int sender); //Adds damage and pushes entity to fDir
	virtual void Die();
};

