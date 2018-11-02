#include "Level_1.h"
#include "Sprite.h"
#include "Collider.h"
#include "Game.h"


Level_1::Level_1(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Levels/sewer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* spr = new Sprite(glm::ivec2(1251*1.4, 282*1.4), glm::dvec2(1, 1 / 3.f), 1, 1, &tex, &shaderProgram);
	spr->setAnimation(0, 0, 3, 9, false);
	spr->changeAnimation(0);
	spr->customZ = true;
	spr->layer = -1000;
	AddComponent(spr);
	AddComponent(new Collider(glm::fvec2(0,300)));
	
	
}

void Level_1::update(int deltaTime) {
	Entity::update(deltaTime);
}

Level_1::~Level_1()
{
}
