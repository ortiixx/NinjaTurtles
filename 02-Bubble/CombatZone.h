#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Boss1.h"
#include "Player.h"
#include "Game.h"
#include "ShaderProgram.h"
class CombatZone : public Entity
{
public:
	CombatZone(float x, int e1, int e2, int e3, int b1, int b2, Player* p, ShaderProgram prog);
	void update(int deltaTime);
	~CombatZone();
private:
	float x;
	float time;
	int e1, e2, e3, b1, b2; //enemyCount
	ShaderProgram prog;
	Player* player;
	void render();
	bool entered = false;
	bool active = true;
	void Check();
	void Spawn();
};

