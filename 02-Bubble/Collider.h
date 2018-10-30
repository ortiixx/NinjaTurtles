#pragma once
#include <glm/glm.hpp>
#include "EntityComponent.h"

class Collider : public EntityComponent
{
public:
	enum Layer {
		Character,
		Cast,
		Level
	};
	Layer l = Character;
	Collider();
	Collider(glm::fvec2 bounds);
	glm::fvec2 GetBounds() { return this->bounds; }
	~Collider();
private:
	glm::fvec2 bounds;
};

