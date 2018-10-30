#include "Transform.h"



Transform::Transform(glm::fvec2 position, glm::fvec2 scale)
{
	this->position = position;
	this->scale = scale;
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
