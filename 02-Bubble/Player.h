#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"



class Player : public Entity
{

public:
	Player();
	void init(const glm::fvec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void Attack(float damage);
	void ManageAnims(int deltaTime);
private:
	float jumpMax;
	float jumpTime = 0;
	float jumpAttackTimer = 0;
	float slowAttackTimer = 0;
	Sprite* sprite;
	bool bJumping;
	enum Dir;
	glm::fvec2 tileMapDispl, inp, vel, friction;
	bool CheckUp(float t);
	int jumpAngle, startY;
	Texture spritesheet;
	TileMap *map;
	int lookDir;
};


#endif // _PLAYER_INCLUDE


