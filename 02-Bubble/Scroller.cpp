#include "Scroller.h"
#include "Texture.h"
#include "Scene.h"

Texture tex;
Scroller::Scroller(ShaderProgram &prog)
{
	tex.loadFromFile("images/Levels/background_city.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::fvec2(700, 700), glm::fvec2(1, 1), 1, 1, &tex, &prog);
	spr->customZ = true;
	spr->layer = -1000;
	AddComponent(spr);
}

void Scroller::update(int deltaTime) {
	Entity::update(deltaTime);
	Player* pl = (Player*)Scene::GetPlayer();
	glm::fvec2 pos= transform.GetPosition();
	glm::fvec2 vel = pl->GetVel();
	pos.x -= Scene::camPX;
	transform.SetPosition(pos);
}

Scroller::~Scroller()
{
}
