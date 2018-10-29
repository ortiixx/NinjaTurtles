#include "HammerDamageable.h"
#include "Scene.h"
#include "Enemy.h"

HammerDamageable::HammerDamageable(float ammount)
{
	health = ammount;
	name = "Damageable";
}

HammerDamageable::~HammerDamageable()
{
}

void HammerDamageable::AddDamage(float ammount, glm::fvec2 fDir, int sender)
{
	Damageable::AddDamage(ammount, fDir, sender);
	Enemy* e = (Enemy*)(Scene::GetEntity(entityId));
	e->setObjective(Scene::GetEntity(sender));
}

void HammerDamageable::Die()
{
	Damageable::Die();
}
