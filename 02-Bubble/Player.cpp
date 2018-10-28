#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Collider.h"
#include "PhysicsEngine.h"
#include "Scene.h"
#include "Damageable.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define INPUT_SENSITIVITY 80
#define ATTACK_RANGE 20
#define FAST_DAMAGE_AMMOUNT 5
#define SLOW_DAMAGE_AMMOUNT 20
#define FORCE 20
#define ATTACK_TIMER 600
#define JUMP_HEIGHT 500
#define ROLL_BOOST 100
#define JUMP_ATTACK_DELAY 400
#define SLOW_ATTACK_DELAY 400


const double pi = 3.14159265358979323846;


/*
CONTROLS:
Z- FAST ATTACK
X- SLOW ATTACK
C- JUMP
V- ROLL
*/


enum PlayerAnims
{
	IDLE,
	KICK,
	WALK1,
	WALK2,
	HIT,
	ROLL,
	ROLL2,
	ATTACK1,
	ATTACK2,
	JUMP_ATTACK1,
	JUMP_ATTACK2,
	HIT1,
	HITHARD,
	DIE
};

enum Player::Dir
{
	LOOKING_LEFT, LOOKING_RIGHT
};

void Player::init(const glm::fvec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	lookDir = LOOKING_RIGHT;
	spritesheet.loadFromFile("images/Characters/donatello.png", TEXTURE_PIXEL_FORMAT_RGBA);
	transform.SetPosition(glm::vec2(69, 69));
	AddComponent(new Sprite (glm::fvec2(128, 128), glm::dvec2(1.f/9.f, 1.f/14.f), 9, 21, &spritesheet, &shaderProgram));
	AddComponent(new Collider(glm::fvec2(128/4, 128/3)));
	AddComponent(new Damageable(0));
	sprite = (Sprite*)GetComponent("Sprite");
	sprite->setAnimation(IDLE, 0, 5, 9, false);
	sprite->setAnimation(WALK1, 59, 8, 9, false);
	sprite->setAnimation(WALK2, 67, 8, 9, false);
	sprite->setAnimation(ATTACK1, 17, 4, 9, true);
	sprite->setAnimation(ATTACK2, 20, 7, 9, true);
	sprite->setAnimation(JUMP_ATTACK2, 52, 7, 9, true);
	sprite->setAnimation(JUMP_ATTACK1, 46, 3, 9, true);
	sprite->setAnimation(ROLL, 36, 10, 12, true);
	sprite->setAnimation(ROLL2, 36, 10, 12, true);
	sprite->setAnimation(HIT1, 36, 10, 3, true);
	sprite->setAnimation(HITHARD, 112, 10, 9, true);
	sprite->setAnimation(DIE, 85, 6, 9, true);
	sprite->setDieAnim(DIE);
	tileMapDispl = tileMapPos;
	friction = glm::vec2(2,3);
	transform.SetPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void Player::Attack(float damage) {

	PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
	glm::fvec2 pos = transform.GetPosition() + glm::fvec2(ATTACK_RANGE, 0) * transform.GetScale().x;
	glm::fvec2 bounds = glm::fvec2(128 / 3);
	std::vector<Collider*> ign;
	ign.push_back((Collider*)GetComponent("Collider"));
	std::vector<Collider*> cols = ps->CastCollision(pos, bounds, ign);
	for (int i = 0; i < cols.size(); i++) {
		Entity* e = Scene::GetEntity(cols[i]->getEntityId());
		if (e == nullptr) continue;
		Damageable* dmg = (Damageable*)e->GetComponent("Damageable");
		glm::fvec2 dir = glm::fvec2(FORCE, 0) * transform.GetScale().x;
		if (dmg != nullptr)
			dmg->AddDamage(damage, dir);
	}
}


void Player::ManageAnims(int deltaTime) {
	if (sprite->animation() == ROLL2) vel.x += ROLL_BOOST * transform.GetScale().x;
	else if (sprite->animation() == JUMP_ATTACK1) {
		if (jumpAttackTimer > JUMP_ATTACK_DELAY) {
			Attack(SLOW_DAMAGE_AMMOUNT * 2);
			jumpAttackTimer = 0;
		}
		vel.x += ROLL_BOOST * transform.GetScale().x;
		jumpAttackTimer += deltaTime;
	}
	else if (sprite->animation() == ATTACK2) {
		if (slowAttackTimer > SLOW_ATTACK_DELAY) {
			Attack(SLOW_DAMAGE_AMMOUNT);
			slowAttackTimer = 0;
		}
		slowAttackTimer += deltaTime;
	}
	else { //Reset all timers here
		jumpAttackTimer = 0;
	}
}


void Player::update(int deltaTime)
{
	Entity::update(deltaTime);
	ManageAnims(deltaTime);
	if (!alive) return;
	bool attacking = sprite->animation() == ATTACK1 || sprite->animation() == ATTACK2;
	bool rolling = sprite->animation() == ROLL2;
	jumpMax = 2 * pi;
	if (bJumping) {
		jumpTime += 9*(float)deltaTime/1000.f;
		vel.y -= sin(jumpTime) * JUMP_HEIGHT;
		if (jumpTime > jumpMax) {
			vel.y -= sin(jumpMax) * JUMP_HEIGHT;
			bJumping = false;
		}
	}
	glm::fvec2 inp = glm::fvec2(0, 0);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		lookDir = LOOKING_LEFT;
		inp.x -= INPUT_SENSITIVITY;
	}
	if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		inp.x += INPUT_SENSITIVITY;
		lookDir = LOOKING_RIGHT;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		inp.y += INPUT_SENSITIVITY;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		inp.y -= INPUT_SENSITIVITY;
	}
	if (Game::instance().getSpecialKey(GLUT_ACTIVE_CTRL)) {
		inp.y -= INPUT_SENSITIVITY;
	}
	if (!rolling && !bJumping && Game::instance().getKey('c')) {
		sprite->changeAnimation(ROLL);
		bJumping = true;
		jumpTime = 0;
	}
	if (!rolling && !attacking && Game::instance().getKey('z')) {
		if (bJumping) { sprite->changeAnimation(JUMP_ATTACK1);}
		else sprite->changeAnimation(ATTACK1);
		Attack(FAST_DAMAGE_AMMOUNT);
	}
	if (!rolling && !attacking && Game::instance().getKey('x')) {
		if (bJumping) sprite->changeAnimation(JUMP_ATTACK2);
		else sprite->changeAnimation(ATTACK2);
	}
	if (sprite->animation() != ROLL2 && !bJumping && Game::instance().getKey('v')) {
		sprite->changeAnimation(ROLL2);
	}
	if (lookDir == LOOKING_LEFT)
		transform.SetScale(glm::vec2(-1,1));
	else transform.SetScale(glm::vec2(1, 1));
	vel += inp;
	if (abs(vel.x) > 0.25 || abs(vel.y) > 0.25)
		sprite->changeAnimation(WALK1);
	if (vel.y < -0.25)
		sprite->changeAnimation(WALK2);
	if(abs(vel.x) < 0.25 && abs(vel.y) < 0.25)
		sprite->changeAnimation(IDLE);
	transform.SetPosition(transform.GetPosition() + vel * (float)deltaTime/1000.f);
	vel /= friction; //Lastly, we apply the friction
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

Player::Player() {
	Entity::Entity();
}


