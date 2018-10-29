#include "Damageable.h"
#include "Scene.h"

Damageable::Damageable()
{
}

Damageable::Damageable(float health)
{
	this->health = health;
	name = "Damageable";
}

void Damageable::AddDamage(float ammount, glm::fvec2 fDir, int sender)
{
	this->health -= ammount;
	glm::fvec2 newPos = transform->GetPosition() + fDir;
	this->transform->SetPosition(newPos);
	if (health <= 0) Die();
}

void Damageable::Die() {
	Entity* e = Scene::GetEntity(entityId);
	Sprite* spr = (Sprite*)e->GetComponent("Sprite");
	Scene::GetEntity(entityId)->setDead();
	spr->Die();
}

Damageable::~Damageable()
{
}
