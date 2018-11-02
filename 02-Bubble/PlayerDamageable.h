#pragma once
#include "Damageable.h"
class PlayerDamageable :
	public Damageable
{
public:
	PlayerDamageable(float ammount);
	~PlayerDamageable();
	virtual void AddDamage(float ammount, glm::fvec2 fDir, int sender); //Adds damage and pushes entity to fDir
	virtual void Die();
};

