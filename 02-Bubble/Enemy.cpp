#include "Enemy.h"
#include "Block.h"
#include "Sprite.h"
#include "Collider.h"
#include "Damageable.h"

enum Animations {
	WALK,
	ATTACK,
	DIE
};

Enemy::Enemy(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Characters/Ninja_pink.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::ivec2(128, 128), glm::dvec2(1.f / 5.f, 1.f / 3.f), 5, 3, &tex, &shaderProgram);
	AddComponent(new Collider(glm::ivec2(128/2, 128/2)));
	AddComponent(new Damageable(30));
	AddComponent(spr);
	spr->setAnimation(WALK, 0, 5,120, false);
	spr->setAnimation(ATTACK, 5, 5, 120, true);
	spr->setAnimation(DIE, 10, 5, 120, true);
	spr->changeAnimation(WALK);
	spr->setDieAnim(DIE);
}

void Enemy::update(int deltaTime) {
	Entity::update(deltaTime);
	//glm::ivec2 dir = 
}


Enemy::~Enemy()
{
}
