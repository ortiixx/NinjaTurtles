#include "Collider.h"

Collider::Collider()
{
}

Collider::Collider(glm::ivec2 bounds)
{
	name = "Collider";
	this->bounds = bounds;
}

Collider::~Collider()
{

}
