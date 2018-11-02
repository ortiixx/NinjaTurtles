#include "PlayerDamageable.h"
#include "Scene.h"
#include "Player.h"

PlayerDamageable::PlayerDamageable(float ammount)
{
	health = ammount;
	name = "Damageable";
}

PlayerDamageable::~PlayerDamageable()
{
}

void PlayerDamageable::AddDamage(float ammount, glm::fvec2 fDir, int sender)
{
	Damageable::AddDamage(ammount, fDir, sender);
	Player* p = (Player*)Scene::GetEntity(entityId);
	if (health>0) p->GetDamage();
}

void PlayerDamageable::Die()
{
	Damageable::Die();
	Scene::encount--;
	//DIE CODE
}
