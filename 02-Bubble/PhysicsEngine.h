#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Collider.h"

class PhysicsEngine
{
public:
	
	PhysicsEngine();
	~PhysicsEngine();
	void AddSceneCollider(Collider* c);
	void physicsLoop();
	static PhysicsEngine* PhysicsGetInstance() {
		if (instance == nullptr) 
			instance = new PhysicsEngine();
		return instance;
	}
	std::vector<Collider * > CastCollision(Collider c);

private:
	std::vector<Collider * > sceneColliders;
	std::vector<Collider * > movedColliders;
	void solveConflict(Collider* c1, Collider* c2);
	bool checkConflict(Collider* c1, Collider* c2);
	static PhysicsEngine* instance;
};