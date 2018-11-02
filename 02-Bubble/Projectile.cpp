#include "Projectile.h"
#include "PhysicsEngine.h"
#include "Scene.h"
#include "Player.h"
#include "Damageable.h"

#define PROJECTILESPEED 170
#define DETECTIONDELAY 300

float detectionTimer = 0;

Projectile::Projectile(ShaderProgram &shaderProgram, glm::fvec2 dir)
{
	tex.loadFromFile("images/Characters/fire.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* spr = new Sprite(glm::fvec2(50, 50), glm::dvec2(1.f/3.f, 1.f), 3, 3, &tex, &shaderProgram);
	spr->setAnimation(0, 0, 3, 9, false);
	spr->changeAnimation(0);
	AddComponent(spr);
	this->dir = dir;
}

void Projectile::update(int deltaTime) {
	Entity::update(deltaTime);
	glm::fvec2 newPos = transform.GetPosition();
	detectionTimer += deltaTime;

	if (detectionTimer > DETECTIONDELAY) {
		detectionTimer = 0;
		std::vector<Collider*> cols = PhysicsEngine::PhysicsGetInstance()->CastCollision(transform.GetPosition(), glm::fvec2(25),std::vector<Collider*>());
		for (int i = 0; i < cols.size(); i++) {
			if (cols[i]->getEntityId() != 0) continue;
			Entity* p = Scene::GetEntity(cols[i]->getEntityId());
            ((Damageable*)p->GetComponent("Damageable"))->AddDamage(10, dir, 0);
			break;
		}
	}

	newPos += float(PROJECTILESPEED) * dir * float(deltaTime) / 1000.f;
	transform.SetPosition(newPos);
}

void Projectile::render()
{
	((Sprite*)GetComponent("Sprite"))->render();
}


Projectile::~Projectile()
{
}
