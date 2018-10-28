#include "Damageable.h"
#include "Scene.h"

Damageable::Damageable(float health)
{
	this->health = health;
	name = "Damageable";
}

void Damageable::AddDamage(float ammount, glm::ivec2 fDir)
{
	this->health -= ammount;
	glm::ivec2 newPos = transform->GetPosition() + fDir;
	this->transform->SetPosition(newPos);
	if (health <= 0) Die();
}

void Damageable::Die() {
	Entity* e = Scene::GetEntity(entityId);
	Sprite* spr = (Sprite*)e->GetComponent("Sprite");
	spr->Die();
	Scene::GetEntity(entityId)->setDead();
}

Damageable::~Damageable()
{
}
