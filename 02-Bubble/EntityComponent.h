#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Transform.h"
#pragma once

class EntityComponent
{
public:
	~EntityComponent();
	std::string GetComponentName() { return name; }
	glm::ivec2 position;
	glm::ivec2 scale;
	Transform* transform;
	virtual void update(int deltaTime);
protected:
	std::string name;

};

