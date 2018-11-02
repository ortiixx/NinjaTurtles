#include "Enemy3.h"
#include "Block.h"
#include "Sprite.h"
#include "Collider.h"
#include "HammerDamageable.h"
#include "Scene.h"
#include <cmath>

#define ATTACK_DELAY 400
#define ATTACK_RANGE 30
#define ATTACK_DIST 160
#define DAMAGE 15
#define SPEED 100
#define IMPULSE 1
#define RECOVERYTIME 1500
#define HEALTH 340
#define UNSPAWNCHANCE 40
#define SPAWNCHANCE 70
#define HIDERATIO 0.6
#define MAXSPAWNDIST 70


Enemy3::Enemy3(ShaderProgram &shaderProgram)
{
	currentState = CHASE;
	tex.loadFromFile("images/Characters/Ninja_white_knife.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::fvec2(128, 128), glm::dvec2(1.f / 5.f, 1.f / 5.f), 5, 6, &tex, &shaderProgram);
	AddComponent(new Collider(glm::fvec2(128 / 2, 128 / 2)));
	AddComponent(new HammerDamageable(HEALTH));
	AddComponent(spr);
	spr->setAnimation(WALK, 0, 5, 9, false);
	spr->setAnimation(ATTACK, 5, 5, 7, true);
	spr->setAnimation(DIE, 20, 5, 7, true);
	spr->setAnimation(HURT, 15, 3, 7, true);
	spr->setAnimation(SPAWN, 10, 5, 7, true);
	spr->setAnimation(UNSPAWN, 20, 5, 7, true);
	spr->changeAnimation(WALK);
	spr->setDieAnim(DIE);
}

glm::fvec2 Enemy3::GetSpawnPoint()
{
	glm::fvec2 ppos = player->GetPosition()+glm::fvec2(-100,6);
	glm::fvec2 dest;
	glm::fvec2 bounds = ((Collider*)GetComponent("Collider"))->GetBounds();
	PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
	bool b = false;
	int iterLimit = 100;
	while (!b && iterLimit >= 0) {
		dest = ppos + glm::fvec2((rand() % MAXSPAWNDIST) - MAXSPAWNDIST / 2.f, (rand() % MAXSPAWNDIST) - MAXSPAWNDIST /2.f);
		vector<Collider*> cols = ps->CastCollision(dest, bounds, vector<Collider*>());
		b = true;
		for (int i = 0; i < cols.size(); i++)
			if (cols[i]->l == Collider::Level) b = false;
		iterLimit--;
		if (b) return dest;
	}
	return ppos;
}

glm::fvec2 Enemy3::CalculateDir() {
	glm::fvec2 tpos = transform.GetPosition();
	glm::fvec2 ppos = player->transform.GetPosition();
	int x, y;
	float margin = 1;
	if (tpos.x - ppos.x > margin) x = -1; else if (tpos.x - ppos.x < -margin) x = 1; else x = 0;
	if (tpos.y - ppos.y > margin)y = -1; else if (tpos.y - ppos.y < -margin) y = 1; else y = 0;
	return glm::fvec2(x, y);
}


void Enemy3::Attack() {
	PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
	glm::fvec2 pos = transform.GetPosition() + CalculateDir();
	glm::fvec2 bounds = glm::fvec2(128 / 3);
	std::vector<Collider*> ign;
	ign.push_back((Collider*)GetComponent("Collider"));
	std::vector<Collider*> cols = ps->CastCollision(pos, bounds, ign);
	for (int i = 0; i < cols.size(); i++) {
		Entity* e = Scene::GetEntity(cols[i]->getEntityId());
		if (e == nullptr) continue;
		Damageable* dmg = (Damageable*)e->GetComponent("Damageable");
		glm::fvec2 dir = glm::fvec2(0, 0);
		if (dmg != nullptr)
			dmg->AddDamage(DAMAGE, dir, id);
	}
}

void Enemy3::update(int deltaTime) {
	Entity::update(deltaTime);
	hideTimer += (float)deltaTime/1000.f;
	if (player == nullptr) player = Scene::GetPlayer(); //Player always the first entity
	if (!alive) return;
	glm::fvec2 dir = CalculateDir();
	glm::fvec2 scale = transform.GetScale();
	float dist = glm::distance((glm::fvec2)player->transform.GetPosition(), (glm::fvec2)transform.GetPosition());
	if (currentState == UNDERGROUND && spr->animation() == WALK) {
		GetComponent("Sprite")->setActive(false);
		GetComponent("Collider")->setActive(false);
	}
	if (spr->animation() == ATTACK) {
		dir.x -= scale.x * IMPULSE;
		dir.y = 0;
	}
	else if (dir.x != 0)
		scale.x = -dir.x;

	if (currentState != UNDERGROUND && dist < ATTACK_DIST && recoveryTimer <= 0 && spr->animation() != SPAWN) {
		currentState = ATTACKING;
	}
	else if (currentState != UNDERGROUND && spr->animation() != ATTACK) {
		currentState = CHASE;
		attackTimer = 0;
	}
	if (spr->animation() == ATTACK) {
		attackTimer += deltaTime;
		if (attackTimer > ATTACK_DELAY) {
			recoveryTimer = RECOVERYTIME;
			attackTimer = 0;
			Attack();
		}
	}
	if (hideTimer > HIDERATIO) {
		hideTimer = 0;
		if (currentState == CHASE && rand() % 100 < UNSPAWNCHANCE) {
			currentState = UNDERGROUND;
			spr->changeAnimation(UNSPAWN);
		}
		else if (currentState == UNDERGROUND && rand() % 100 > SPAWNCHANCE) {
			transform.SetPosition(GetSpawnPoint());
			this->spr->setActive(true);
			GetComponent("Collider")->setActive(true);
			this->spr->changeAnimation(SPAWN);
			currentState = CHASE;
		}
	}
	transform.SetScale(scale);
	if(currentState != UNDERGROUND) transform.SetPosition(transform.GetPosition() + dir * glm::fvec2(SPEED, SPEED / 3) * float(deltaTime) / 1000.f);
	if (currentState == ATTACK && spr->animation() != ATTACK)
		spr->changeAnimation(ATTACK);
	recoveryTimer -= deltaTime;
}

void Enemy3::GetDamage() {
	spr->changeAnimation(HURT);
}

Enemy3::~Enemy3()
{
}