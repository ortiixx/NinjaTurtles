#include "EntityComponent.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Transform.h"
#pragma once

class Entity
{
public:
	Entity();
	~Entity();
	EntityComponent* GetComponent(std::string name);
	glm::ivec2 GetPosition() { return transform.GetPosition(); }
	void AddComponent(EntityComponent* comp);
	virtual void update(int deltaTime);
	virtual void render();
	Transform transform;

protected:
	std::vector <EntityComponent*> components;
	glm::ivec2 position;
	glm::ivec2 scale;
};

