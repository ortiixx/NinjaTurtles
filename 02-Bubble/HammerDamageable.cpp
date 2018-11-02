#include "HammerDamageable.h"
#include "Scene.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Boss1.h"

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
	if(health>0) e->GetDamage();
}

void HammerDamageable::Die()
{
	Damageable::Die();
	Scene::encount--;
}
