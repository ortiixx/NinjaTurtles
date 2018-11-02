#include "CombatZone.h"
#include "Scene.h"

#define CHECKRATIO 300
#define DISPERSION 100
CombatZone::CombatZone(float x, int e1, int e2, int e3, int b1, int b2, Player* p, ShaderProgram prog)
{
	this->x = x;
	this->e1 = e1;
	this->e2 = e2;
	this->e3 = e3;
	this->b1 = b1;
	this->b2 = b2;
	this->prog = prog;
	time = 0;
	player = p;
}

void CombatZone::update(int deltaTime)
{
	Entity::update(deltaTime);
	if (!active || Scene::inCombat) return;
	if (!entered && time <= 0) Check();
	if (time > 0) time -= deltaTime;
}

void CombatZone::Spawn() {
	float inc = SCREEN_WIDTH;
	Scene::encount += e1 + e2 + e3 + b1 + b2;
	for (int i = 0; i < e1; i++) {
		Enemy* e = new Enemy(prog);
		glm::fvec2 pos = glm::fvec2(player->transform.GetPosition().x, player->transform.GetPosition().y);
		if (i % 2 == 0) pos.x -= SCREEN_WIDTH + rand()%DISPERSION*2;
		else pos.x += SCREEN_WIDTH + rand()%DISPERSION*4;
		e->transform.SetPosition(pos);
		Scene::AddEntity(e);
	}
	for (int i = 0; i < e2; i++) {
		Enemy2* e = new Enemy2(prog);
		glm::fvec2 pos = glm::fvec2(player->transform.GetPosition().x, player->transform.GetPosition().y);
		if (i % 2 == 0) pos.x -= SCREEN_WIDTH / 2 - rand() % DISPERSION * 2;
		else pos.x += SCREEN_WIDTH + rand() % DISPERSION * 4;
		e->transform.SetPosition(pos);
		Scene::AddEntity(e);
	}
	for (int i = 0; i < e3; i++) {
		Enemy3* e = new Enemy3(prog);
		glm::fvec2 pos = glm::fvec2(player->transform.GetPosition().x, player->transform.GetPosition().y);
		if (i % 2 == 0) pos.x -= SCREEN_WIDTH / 2 - rand() % DISPERSION * 2;
		else pos.x += SCREEN_WIDTH + rand() % DISPERSION * 2;
		e->transform.SetPosition(pos);
		Scene::AddEntity(e);
	}
	if (b1 != 0) {
		Boss1* b = new Boss1(prog);
		glm::fvec2 pos = glm::fvec2(player->transform.GetPosition().x, player->transform.GetPosition().y);
		pos.x -= SCREEN_WIDTH / 2 - rand() % DISPERSION * 2;
		b->transform.SetPosition(pos);
		Scene::AddEntity(b);
	}

	active = false;
}

void CombatZone::Check()
{
	time = CHECKRATIO;
	if (player->transform.GetPosition().x > this->x) {
		entered = true;
		Scene::SetCombat();
		Spawn();
	}

}

void CombatZone::render() {
	return;
}

CombatZone::~CombatZone()
{
}