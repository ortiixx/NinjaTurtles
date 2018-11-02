#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Entity.h"
#include "Collider.h"
#include "Menu.h"
#include "PhysicsEngine.h"
#include <map>
#include "Icon.h"
#include "Text.h"
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
	void Clean();
	static void AddEntity(Entity* ent);
	static Entity* GetEntity(int id);
	static void RemoveEntity(int id);
	static void SetCombat();
	static Entity* GetPlayer() { return player; }
	static int encount;
	static bool inCombat;
	static float camPX;

private:
	void initShaders();
	void moveCamera(int deltaTime);

private:
	static bool moveC;
	float camPY;
	glm::fvec2 lppos;
	static int lastId;
	void loadlevel1();
	void loadlevel2();
	Menu* menu;
	TileMap *map;
	static Player *player;
	Icon *icon;
	ShaderProgram texProgram;
	static	PhysicsEngine* ps;
	float currentTime;
	glm::mat4 projection;
	static std::map<int, Entity*> entities;
	bool intro, choose, intro_level_1, level_1, intro_level_2, level_2, end_game;
	Text * character;
	Text * how_to_play;
	Text * credits;
	Text* intro1;
};


#endif // _SCENE_INCLUDE

