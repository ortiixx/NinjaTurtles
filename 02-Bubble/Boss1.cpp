#include "Boss1.h"
#include "Block.h"
#include "Sprite.h"
#include "Collider.h"
#include "HammerDamageable.h"
#include "Scene.h"
#include <glm/gtx/rotate_vector.hpp>
#define ATTACK_DELAY 300
#define SHOOT_DELAY 40
#define ATTACK_RANGE 40 //30
#define ATTACK_DIST 20
#define CHASE_DIST 300
#define DAMAGE 1500
#define SPEED 100
#define HEALTH 1500
#define SHOOTREFILL 500
#define SHOOTRANGE 200
enum Animations {
	WALK,
	ATTACK,
	ATTACK2,
	DIE,
	HURT
};

enum Boss1::State {
	CHASE,
	ATTACK,
	SHOOT,
};

Boss1::Boss1(ShaderProgram &shaderProgram)
{
	prog = shaderProgram;
	currentState = CHASE;
	speed = SPEED;
	tex.loadFromFile("images/Characters/boss1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::fvec2(128, 128), glm::dvec2(1.f / 6.f, 1.f / 5.f), 6, 5, &tex, &shaderProgram);
	AddComponent(new Collider(glm::fvec2(128 / 2, 128*1.2 / 2)));
	AddComponent(new HammerDamageable(HEALTH));
	AddComponent(spr);
	spr->setAnimation(WALK, 12, 6, speed/7, false);
	spr->setAnimation(ATTACK, 18, 4, 8, true);
	spr->setAnimation(ATTACK2, 7, 1, 4000, true);
	spr->setAnimation(DIE, 24, 3, 12, true);
	spr->setAnimation(HURT, 24, 1, 7, true);
	spr->changeAnimation(WALK);
	spr->setDieAnim(DIE);
}

glm::fvec2 Boss1::CalculateDir() {
	glm::fvec2 tpos = transform.GetPosition();
	glm::fvec2 ppos = player->transform.GetPosition();
	int x, y;
	if (tpos.x - ppos.x > 0) x = -1; else x = 1;
	if (tpos.y - ppos.y > 0) y = -1; else y = 1;
	return glm::fvec2(x, y);
}


void Boss1::Attack() {
	PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
	glm::fvec2 pos = transform.GetPosition() + CalculateDir();
	glm::fvec2 bounds = glm::fvec2(128/2, 128/2);
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

void Boss1::UpdateProjectiles(int deltaTime)
{
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->update(deltaTime);
		projectiles[i]->render();
	}
}

glm::fvec2 rotate(glm::fvec2 vec) {
	glm::fvec2 d = glm::normalize(vec);
	float angle = 170;
	float val = rand()%int(angle) - (angle/2.f);
	vec.y += val;
	vec.x += val;
	return glm::normalize(vec);
}

void Boss1::Shoot()
{
	Projectile* p = new Projectile(prog, rotate(player->GetPosition()-transform.GetPosition()));
	glm::fvec2 offset1 = glm::fvec2(-20.f, 10.f);
	glm::fvec2 offset2 = glm::fvec2(85.f, 10.f);
	glm::fvec2 offset;
	if (transform.GetScale().x == -1) offset = offset1;
	else offset = offset2;
	p->transform.SetPosition(transform.GetPosition()+offset);
	Scene::AddEntity(p);
}

bool dontShoot = false;

void Boss1::update(int deltaTime) {
	Entity::update(deltaTime);
	if (!alive) return;
	UpdateProjectiles(deltaTime);
	if (player == nullptr) player = Scene::GetPlayer(); //Player always the first entity
	float dist = glm::distance(player->transform.GetPosition(), transform.GetPosition());

	if (dist < ATTACK_DIST) {
		currentState = ATTACK;
	}
	else if (!dontShoot &&  dist >= SHOOTRANGE && dist <= CHASE_DIST) {
		currentState = SHOOT;
	}
	else if (dist >= CHASE_DIST || spr->animation() != ATTACK) {
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
	else if (spr->animation() == ATTACK2) {
		attackTimer += deltaTime;
		if (attackTimer > SHOOT_DELAY) {
			attackTimer = 0;
			Shoot();
		}
	}
	glm::fvec2 dir = CalculateDir();
	glm::fvec2 scale = transform.GetScale();
	scale.x = dir.x;
	transform.SetScale(scale);
	dir.y /= 4;
	if (currentState == CHASE) {
		transform.SetPosition(transform.GetPosition() + dir * speed * float(deltaTime) / 1000.f);
	}
	if (currentState == ATTACK && spr->animation() != ATTACK)
		spr->changeAnimation(ATTACK);
	else if (currentState == SHOOT && spr->animation() != ATTACK2)
		spr->changeAnimation(SHOOT);
}


void Boss1::GetDamage() {
	spr->changeAnimation(HURT);
	HammerDamageable* dmg = (HammerDamageable*)GetComponent("Damageable");
	if (dmg->getHealth() <= HEALTH / 3) {
		speed = SPEED * 2.6;
		dontShoot = true;
	}
}

Boss1::~Boss1()
{
}
