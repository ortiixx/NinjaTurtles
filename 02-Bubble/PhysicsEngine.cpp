#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddSceneCollider(Collider* c)
{
	//All scene colliders should be added at the beginning frame!
	sceneColliders.push_back(c);
}

std::vector<Collider*> PhysicsEngine::CastCollision(Collider c)
{
	return std::vector<Collider*>();
}


void PhysicsEngine::solveConflict(Collider * c1, Collider * c2)
{
	if (c1->transform->GetLastPosition() != c1->transform->GetPosition())
		c1->transform->SetPosition(c1->transform->GetLastPosition());
	if(c2->transform->GetLastPosition() != c2->transform->GetPosition())
		c2->transform->SetPosition(c2->transform->GetLastPosition());
}

bool PhysicsEngine::checkConflict(Collider* c1, Collider* c2){
	glm::vec2 pos1 = c1->transform->GetPosition();
	glm::vec2 pos2 = c2->transform->GetPosition();
	glm::vec2 ext1 = c2->GetBounds();
	glm::vec2 ext2 = c2->GetBounds();
	return pos1.x < pos2.x + ext2.x &&
		pos1.x + ext1.x > pos2.x &&
		pos1.y < pos2.y + ext2.y &&
		ext1.y + pos1.y > pos2.y;
}

void PhysicsEngine::physicsLoop()
{
	for (int i = 0; i < sceneColliders.size(); i++) {
		if (sceneColliders[i]->transform->GetPosition() != sceneColliders[i]->transform->GetLastPosition())
			movedColliders.push_back(sceneColliders[i]);
	}
	for (int i = 0; i < movedColliders.size(); i++) {
		for (int j = 0; j < sceneColliders.size(); j++) {
			if (sceneColliders[j] == movedColliders[i]) continue;
			Collider * c1 = movedColliders[i];
			Collider * c2 = sceneColliders[j];
			if (checkConflict(c1, c2))
				solveConflict(c1, c2);
		}
	}
	movedColliders.empty();
}