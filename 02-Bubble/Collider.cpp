#include "Collider.h"

Collider::Collider()
{
}

Collider::Collider(glm::fvec2 bounds)
{
	name = "Collider";
	this->bounds = bounds;
}

Collider::~Collider()
{

}
