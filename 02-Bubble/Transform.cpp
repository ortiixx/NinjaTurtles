#include "Transform.h"



Transform::Transform(glm::ivec2 position, glm::ivec2 scale)
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
