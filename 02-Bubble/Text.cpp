#include "Text.h"


Text::Text(ShaderProgram &shaderProgram, int value)
{
	if (value == 1){
		tex.loadFromFile("images/Levels/intro_level_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		AddComponent(new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
	}
	else if (value == 2){
		tex.loadFromFile("images/Levels/intro_level_2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		AddComponent(new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
	}
	else if (value == 3){
		tex.loadFromFile("images/Levels/end_game.png", TEXTURE_PIXEL_FORMAT_RGBA);
		AddComponent(new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
	}
	else if (value == 4){
		tex.loadFromFile("images/Levels/character.png", TEXTURE_PIXEL_FORMAT_RGBA);
		AddComponent(new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
	}
	else if (value == 5){
		tex.loadFromFile("images/Levels/how_to_play.png", TEXTURE_PIXEL_FORMAT_RGBA);
		AddComponent(new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
	}
	else if (value == 6){
		tex.loadFromFile("images/Levels/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
		AddComponent(new Sprite(glm::ivec2(640, 282), glm::dvec2(1, 1), 1, 1, &tex, &shaderProgram));
	}
}


Text::~Text()
{
}

void Text::update(int deltaTime) {
	Entity::update(deltaTime);
}
