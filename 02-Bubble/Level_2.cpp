#include "Level_2.h"
#include "Sprite.h"
#include "Collider.h"
#include "Scroller.h"
#include "Scene.h"

Level_2::Level_2(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Levels/Level_2_no_background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* spr = new Sprite(glm::ivec2(1251*2.5, 500), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram);
	spr->customZ = true;
	spr->layer = -999;
	AddComponent(spr);
	Scroller* scr = new Scroller(shaderProgram);
	Scene::AddEntity(scr);
}

void Level_2::update(int deltaTime) {
	Entity::update(deltaTime);
}

Level_2::~Level_2()
{
}
