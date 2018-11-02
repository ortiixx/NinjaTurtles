#include "Icon.h"
#include "Sprite.h"
#include "Game.h"

#define CURSORTIMER 400
Icon::Icon(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Levels/Icon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* spr = new Sprite(glm::ivec2(58, 65), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram);
	spr->customZ = true;
	spr->layer = 2;
	AddComponent(spr);
	sel = 0;
}


Icon::~Icon()
{
}
float timer = 0;
std::vector<int> pos{ 10, 55, 105 };
void Icon::update(int deltaTime) {
	Entity::update(deltaTime);
	if (timer >= 0) { timer -= deltaTime; return; }
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
	sel++;
		if (sel == pos.size()) sel = 0;
		transform.SetPosition(glm::fvec2(270, pos[sel]));
		timer = CURSORTIMER;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		sel--;
		if (sel < 0) sel = pos.size()-1;
		transform.SetPosition(glm::fvec2(270, pos[sel]));
		timer = CURSORTIMER;
	}
	
}