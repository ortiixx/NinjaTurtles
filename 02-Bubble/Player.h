#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"



class Player : public Entity
{

public:
	Player();
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void Attack(float damage);
private:
	float jumpMax;
	float jumpTime = 0;
	Sprite* sprite;
	bool bJumping;
	enum Dir;
	glm::ivec2 tileMapDispl, inp, vel, friction;
	int jumpAngle, startY;
	Texture spritesheet;
	TileMap *map;
	int lookDir;
};


#endif // _PLAYER_INCLUDE


