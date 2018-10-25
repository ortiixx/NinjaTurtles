#include "Collider.h"

Collider::Collider()
{
}
/*
void Collider:: SetLastPosition(glm::ivec2 position)
{
	lastposition = position;
}*/

Collider::Collider(glm::ivec2 bounds)
{
	name = "Collider";
	this->bounds = bounds;
}

Collider::~Collider()
{

}
