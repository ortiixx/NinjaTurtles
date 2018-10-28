#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"


Entity::~Entity()
{
}

EntityComponent * Entity::GetComponent(std::string name)
{
	for (int i = 0; i < components.size(); i++) 
		if (components[i]->GetComponentName() == name) return components[i];
	
	return nullptr;
}

void Entity::update(int deltaTime) {
	for (int i = 0; i < components.size(); i++)
		components[i]->update(deltaTime);
}

void Entity::render() {
	Sprite* spr = (Sprite*)GetComponent("Sprite");
	spr->render();
}

void Entity::setId(int id)
{
	for (int i = 0; i < components.size(); i++)
		components[i]->setEntityId(id);
}

void Entity::AddComponent(EntityComponent* comp) {
	components.push_back(comp);
	comp->transform = &transform;
}

Entity::Entity() {
	transform = Transform(glm::ivec2(0, 0), glm::ivec2(1, 1));
}