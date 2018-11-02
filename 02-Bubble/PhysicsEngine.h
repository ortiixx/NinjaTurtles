#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Collider.h"

static class PhysicsEngine
{
public:
	
	~PhysicsEngine();
	void AddSceneCollider(Collider* c);
	void RemoveSceneCollider(Collider* c);
	void physicsLoop();
	static void Clean() { sceneColliders = std::vector<Collider*>(); }
	static PhysicsEngine* PhysicsGetInstance() {
		if (instance == nullptr) 
			instance = new PhysicsEngine();
		return instance;
	}
	std::vector<Collider * > CastCollision(glm::fvec2 pos, glm::fvec2 bounds, const std::vector<Collider *> &ignore);

private:
	static std::vector<Collider * > sceneColliders;
	std::vector<Collider * > movedColliders;
	void solveConflict(Collider* c1, Collider* c2);
	bool checkConflict(Collider* c1, Collider* c2);
	static PhysicsEngine* instance;
	PhysicsEngine();
};