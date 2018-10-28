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
#define INPUT_SENSITIVITY 2
#define ATTACK_RANGE 2
#define DAMAGE_AMMOUNT 20
#define FORCE 20
#define ATTACK_TIMER 600

enum PlayerAnims
{
	IDLE,
	KICK,
	WALK1,
	WALK2,
	HIT,
	ROLL,
	ATTACK1
};

enum Player::Dir
{
	LOOKING_LEFT, LOOKING_RIGHT
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	attackTimer = 0;
	bJumping = false;
	lookDir = LOOKING_RIGHT;
	spritesheet.loadFromFile("images/Characters/donatello.png", TEXTURE_PIXEL_FORMAT_RGBA);
	transform.SetPosition(glm::vec2(69, 69));
	AddComponent(new Sprite (glm::ivec2(128, 128), glm::dvec2(1.f/9.f, 1.f/14.f), 9, 21, &spritesheet, &shaderProgram));
	AddComponent(new Collider(glm::ivec2(128/4, 128/3)));
	sprite = (Sprite*)GetComponent("Sprite");
	sprite->setAnimation(IDLE, 0, 5, 490, false);
	sprite->setAnimation(WALK1, 59, 8, 160, false);
	sprite->setAnimation(WALK2, 67, 8, 160, false);
	sprite->setAnimation(ATTACK1, 17, 4, 230, true);
	tileMapDispl = tileMapPos;
	friction = glm::vec2(2,3);
	transform.SetPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void Player::Attack() {
	if (attackTimer < ATTACK_TIMER) return;
	sprite->changeAnimation(ATTACK1);
	attackTimer = 0;
	PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
	glm::ivec2 pos = transform.GetPosition() + glm::ivec2(ATTACK_RANGE, 0) * transform.GetScale().x;
	glm::ivec2 bounds = glm::ivec2(128 / 2);
	std::vector<Collider*> ign;
	ign.push_back((Collider*)GetComponent("Collider"));
	std::vector<Collider*> cols = ps->CastCollision(pos, bounds, ign);
	for (int i = 0; i < cols.size(); i++) {
		Entity* e = Scene::GetEntity(cols[i]->getEntityId());
		if (e == nullptr) continue;
		Damageable* dmg = (Damageable*)e->GetComponent("Damageable");
		glm::ivec2 dir = glm::ivec2(FORCE*3, 0) * transform.GetScale().x;
		if (dmg != nullptr)
			dmg->AddDamage(DAMAGE_AMMOUNT, dir);
	}
}
int Jump(int x) {
	int a, b, c;
	a = b = c = 2;
	return a * pow(x, 2) + b * x + c;
}

void Player::update(int deltaTime)
{
	attackTimer += deltaTime;
	if (jumpAdd > 0) jumpAdd -= 1;
	sprite->update(deltaTime);
	Entity::update(deltaTime);
	glm::ivec2 inp = glm::ivec2(0, 0);
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
	if (Game::instance().getKey(' ')) {
		jumpAdd = jumpMax;
	}
	if (Game::instance().getKey('z')|| Game::instance().getKey('Z')) {
		Attack();
	}
	vel.y = Jump(-jumpAdd);
	if (lookDir == LOOKING_LEFT)
		transform.SetScale(glm::vec2(-1,1));
	else transform.SetScale(glm::vec2(1, 1));
	vel += inp;
	glm::ivec2 posPlayer = transform.GetPosition();
	posPlayer += vel;
	if (abs(vel.x) > 0.25) 
		sprite->changeAnimation(WALK1);
	if (vel.y < -0.25)
		sprite->changeAnimation(WALK2);
	else if(abs(vel.x) < 0.25 && abs(vel.y) < 0.25)
		sprite->changeAnimation(IDLE);
	//transform->position += (glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	transform.SetPosition(transform.GetPosition() + vel);
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


