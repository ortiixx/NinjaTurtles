#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Entity.h"
#include "Collider.h"
#include "PhysicsEngine.h"
// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();
	void init();
	void update(int deltaTime);
	void render();
	void UpdateSceneColliders();
private:
	void initShaders();
	void moveCamera();


private:
	float camPX;
	float camPY;
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	PhysicsEngine* ps;
	float currentTime;
	glm::mat4 projection;
	std::vector<Entity*> entities;
};


#endif // _SCENE_INCLUDE

