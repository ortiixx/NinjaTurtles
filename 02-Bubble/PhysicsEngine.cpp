#include "PhysicsEngine.h"

PhysicsEngine* PhysicsEngine::instance = nullptr;


PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::RemoveSceneCollider(Collider* c) {
	for (int i = 0; i < sceneColliders.size(); i++) {
		if (sceneColliders[i] == c)
			sceneColliders.erase(sceneColliders.begin()+i);
		sceneColliders;
	}
}

void PhysicsEngine::AddSceneCollider(Collider* c)
{
	//All scene colliders should be added at the beginning frame!
	sceneColliders.push_back(c);
}

std::vector<Collider*> PhysicsEngine::CastCollision(glm::fvec2 pos, glm::fvec2 bounds, const std::vector<Collider *> &ignore)
{
	std::vector<Collider*> output;
	Collider* c1 = new Collider(bounds);
	c1->l = Collider::Cast;
	c1->transform = new Transform(pos, glm::fvec2(1, 1));
	for (int i = 0; i < sceneColliders.size(); i++) {
		Collider* c2 = sceneColliders[i];
		bool b = false;
		for (int j = 0; j < ignore.size(); j++) if (c2 == ignore[j]) b = true;
		if (b) continue;
		if (checkConflict(c1, c2))
			output.push_back(c2);
	}
	return output;
}


void PhysicsEngine::solveConflict(Collider * c1, Collider * c2)
{
	if (c1->transform->GetLastPosition() != c1->transform->GetPosition()) 
		c1->transform->SetPosition(c1->transform->GetLastPosition());
	
	if (c2->transform->GetLastPosition() != c2->transform->GetPosition()) 
		c2->transform->SetPosition(c2->transform->GetLastPosition());
	
}

bool PhysicsEngine::checkConflict(Collider* c1, Collider* c2){
	if ( !c1->isActive() || !c2->isActive() || c1->l == c2->l) return false;
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
		Collider * c1 = movedColliders[i];
		for (int j = 0; j < sceneColliders.size(); j++) {
			if (sceneColliders[j] == movedColliders[i]) continue;
			Collider * c2 = sceneColliders[j];
			if (checkConflict(c1, c2))
				solveConflict(c1, c2);
		}
	}
	movedColliders = std::vector<Collider*>();
}
