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
	Transform* transform;
	virtual void update(int deltaTime);
	void setEntityId(int id);
	int getEntityId() { return this->entityId; }
	void setActive(bool b) { active = b; }
	bool isActive(){ return active; }
protected:
	std::string name;
	int entityId;
	bool active = true;
};

