#include "Enemy2.h"
#include "Block.h"
#include "Sprite.h"
#include "Collider.h"
#include "HammerDamageable.h"
#include "Scene.h"

#define ATTACK_DELAY 100
#define ATTACK_RANGE 30
#define ATTACK_DIST 160
#define DAMAGE 15
#define SPEED 130
#define IMPULSE 2
#define RECOVERYTIME 1500
#define HEALTH 100

Enemy2::Enemy2(ShaderProgram &shaderProgram)
{
	currentState = CHASE;
	tex.loadFromFile("images/Characters/Ninja_purple.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::fvec2(128, 128), glm::dvec2(1.f / 5.f, 1.f / 3.f), 5, 4, &tex, &shaderProgram);
	AddComponent(new Collider(glm::fvec2(128 / 2, 128 / 2)));
	AddComponent(new HammerDamageable(HEALTH));
	AddComponent(spr);
	spr->setAnimation(WALK, 0, 5, 9, false);
	spr->setAnimation(ATTACK, 5, 5, 7, true);
	spr->setAnimation(DIE, 10, 5, 7, true);
	spr->setAnimation(HURT, 10, 3, 7, true);
	spr->changeAnimation(WALK);
	spr->setDieAnim(DIE);
}

glm::fvec2 Enemy2::CalculateDir() {
	glm::fvec2 tpos = transform.GetPosition();
	glm::fvec2 ppos = player->transform.GetPosition();
	int x, y;
	float margin = 1;
	if (tpos.x - ppos.x > margin) x = -1; else if (tpos.x - ppos.x < -margin) x = 1; else x = 0;
	if (tpos.y - ppos.y > margin)y = -1; else if (tpos.y - ppos.y < -margin) y = 1; else y = 0;
	return glm::fvec2(x, y);
}


void Enemy2::Attack() {
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

void Enemy2::update(int deltaTime) {
	Entity::update(deltaTime);
	if (player == nullptr) player = Scene::GetPlayer(); //Player always the first entity
	if (!alive) return;
	glm::fvec2 dir = CalculateDir();
	glm::fvec2 scale = transform.GetScale();
	if (spr->animation() == ATTACK) {
		dir.x -= scale.x * IMPULSE;
		dir.y = 0;
	}
	else if(dir.x != 0)
		scale.x = -dir.x;

	if (glm::distance((glm::fvec2)player->transform.GetPosition(), (glm::fvec2)transform.GetPosition()) < ATTACK_DIST && recoveryTimer <= 0) {
		currentState = ATTACKING;
	}
	else if (spr->animation() != ATTACK) {
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
	transform.SetScale(scale);
	transform.SetPosition(transform.GetPosition() + dir * glm::fvec2(SPEED,SPEED/3) * float(deltaTime)/1000.f);
	if (currentState == ATTACKING && spr->animation() != ATTACK)
		spr->changeAnimation(ATTACK);
	recoveryTimer -= deltaTime;
}

void Enemy2::GetDamage() {
	spr->changeAnimation(HURT);
}

Enemy2::~Enemy2()
{
}