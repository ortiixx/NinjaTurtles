#include "Enemy.h"
#include "Block.h"
#include "Sprite.h"
#include "Collider.h"
#include "HammerDamageable.h"
#include "Scene.h"

#define ATTACK_DELAY 500
#define ATTACK_RANGE 30
#define ATTACK_DIST 30
#define DAMAGE 30
#define SPEED 80
enum Animations {
	WALK,
	ATTACK,
	DIE,
	HURT
};

enum Enemy::State{
	CHASE,
	ATTACK,
	EVADE,
};

Enemy::Enemy(ShaderProgram &shaderProgram)
{
	currentState = CHASE;
	tex.loadFromFile("images/Characters/Ninja_pink.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::fvec2(128, 128), glm::dvec2(1.f / 5.f, 1.f / 3.f), 5, 4, &tex, &shaderProgram);
	Collider* c = new Collider(glm::fvec2(128/2, 128/2));
	c->ignoreScene = true;
	AddComponent(c);
	AddComponent(new HammerDamageable(300));
	AddComponent(spr);
	spr->setAnimation(WALK, 0, 5,13, false);
	spr->setAnimation(ATTACK, 5, 5, 7, true);
	spr->setAnimation(DIE, 10, 5, 7, true);
	spr->setAnimation(HURT, 10, 2, 7, true);
	spr->changeAnimation(WALK);
	spr->setDieAnim(DIE);
}

glm::fvec2 Enemy::CalculateDir() {
	glm::fvec2 tpos = transform.GetPosition();
	glm::fvec2 ppos = player->transform.GetPosition();
	int x, y;
	if (tpos.x - ppos.x > 0) x = -1; else x = 1;
	if (tpos.y - ppos.y > 0) y = -1; else y = 1;
	return glm::fvec2(x, y);
}


void Enemy::Attack() {
	PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
	glm::fvec2 pos = transform.GetPosition() + CalculateDir();
	glm::fvec2 bounds = glm::fvec2(128/3);
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

void Enemy::update(int deltaTime) {
	Entity::update(deltaTime);
	if (!alive) return;
	if (player == nullptr) player = Scene::GetPlayer(); //Player always the first entity

	if (glm::distance((glm::fvec2)player->transform.GetPosition(), (glm::fvec2)transform.GetPosition()) < ATTACK_DIST) {
		currentState = ATTACK;
	}
	else if (spr->animation() != ATTACK) {
		currentState = CHASE;
		attackTimer = 0;
	}
	if (spr->animation() == ATTACK) {
		attackTimer += deltaTime;
		if (attackTimer > ATTACK_DELAY) {
			attackTimer = 0;
			Attack();
		}
	}
	glm::fvec2 dir = CalculateDir();
	glm::fvec2 scale = transform.GetScale();
	scale.x = -dir.x;
	transform.SetScale(scale);
	if(currentState == CHASE)
		transform.SetPosition(transform.GetPosition() + dir * float(SPEED) * float(deltaTime) / 1000.f);
	if (currentState == ATTACK && spr->animation() != ATTACK)
		spr->changeAnimation(ATTACK);
}

void Enemy::GetDamage() {
	spr->changeAnimation(HURT);
}

Enemy::~Enemy()
{
}
