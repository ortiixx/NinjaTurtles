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
	void Attack();
private:
	int jumpMax = 10;
	int jumpAdd = 0;
	Sprite* sprite;
	bool bJumping;
	enum Dir;
	glm::ivec2 tileMapDispl, inp, vel, friction;
	int jumpAngle, startY;
	Texture spritesheet;
	TileMap *map;
	int lookDir;
	int attackTimer;
};


#endif // _PLAYER_INCLUDE


