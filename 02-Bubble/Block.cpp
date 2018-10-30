#include "Block.h"
#include "Sprite.h"
#include "Collider.h"
#include "Damageable.h"

Block::Block(ShaderProgram &shaderProgram)
{
	tex.loadFromFile("images/Characters/donatellos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	AddComponent(new Sprite(glm::fvec2(12800, 128), glm::dvec2(1.f / 9.f, 1.f / 14.f), 9, 21, &tex, &shaderProgram));
	Collider* c = new Collider(glm::fvec2(12800/2, 128/2));
	c->l = Collider::Level;
	AddComponent(c);
}

void Block::update(int deltaTime) {
	Entity::update(deltaTime);
}

Block::~Block()
{
}
