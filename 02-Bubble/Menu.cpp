#include "Menu.h"
#include "Sprite.h"
#include "Game.h"
#include <Mmsystem.h>
#include <mciapi.h>
Menu::Menu(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Levels/begin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* spr = new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram);
	spr->customZ = true;
	spr->layer = 1;
	AddComponent(spr);
	//
}

void Menu::update(int deltaTime) {
	Entity::update(deltaTime);

}

Menu::~Menu()
{
}
