#pragma once
#include <glm/glm.hpp>
#include "EntityComponent.h"

class Collider : public EntityComponent
{
public:
	enum Layer {
		Character,
		Cast
	};
	Layer l = Character;
	Collider();
	Collider(glm::ivec2 bounds);
	glm::ivec2 GetBounds() { return this->bounds; }
	~Collider();
private:
	glm::ivec2 bounds;
};

