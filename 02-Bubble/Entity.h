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
	glm::fvec2 GetPosition() { return transform.GetPosition(); }
	void AddComponent(EntityComponent* comp);
	virtual void update(int deltaTime);
	virtual void render();
	void setDead() { alive = false; }
	void setId(int id);
	int getId() { return id; }
	Transform transform;
	bool isPlayer = false;
protected:
	std::vector <EntityComponent*> components;
	bool alive = true;
	glm::fvec2 position;
	glm::fvec2 scale;
	int id; 
};
