#include "Level_2.h"
#include "Sprite.h"
#include "Collider.h"


Level_2::Level_2(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Levels/Level_2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	AddComponent(new Sprite(glm::ivec2(1251, 300), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
}

void Level_2::update(int deltaTime) {
	Entity::update(deltaTime);
}

Level_2::~Level_2()
{
}
