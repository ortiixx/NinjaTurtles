#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Block.h"
#include "Enemy.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Icon.h"
#include "Text.h"
#include <Mmsystem.h>
#include <mciapi.h>
#include "CombatZone.h"
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

#define SCREEN_X 32
#define SCREEN_Y 32

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

std::map<int, Entity*> Scene::entities = std::map<int, Entity*>();
int Scene::lastId = 0;
bool Scene::moveC = true;
Player* Scene::player = nullptr;
int Scene::encount = 0;
bool Scene::inCombat = false;

std::vector<string> players{
	"images/Characters/Donatello_gamma.png",
	"images/Characters/Michelangelo_gamma.png",
	"images/Characters/Leonardo_gamma.png",
	"images/Characters/Raphael_gamma.png"
};
Scene::Scene()
{

}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

Entity* Scene::GetEntity(int id) {
	if (!entities.count(id)) return nullptr;
	return entities[id];
}

PhysicsEngine* Scene::ps = PhysicsEngine::PhysicsGetInstance();


void Scene::RemoveEntity(int id)
{
	if (entities.count(id) == 0 ) return;
	Entity* ent = entities[id];
	Collider* c = (Collider*)ent->GetComponent("Collider");
	((Sprite*)ent->GetComponent("Sprite"))->setActive(false);
	if (c != nullptr) {
		//PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
		ps->RemoveSceneCollider(c);
	}
	entities.erase(id);
	delete ent;

}

void Scene::SetCombat()
{
	moveC = false;
	inCombat = true;
}

void Scene::UpdateSceneColliders() {

	for (auto const& x : entities) {
		Collider* c = (Collider *)x.second->GetComponent("Collider");
		if (c != nullptr) ps->AddSceneCollider(c);
	}
}

void Scene::AddEntity(Entity * ent)
{
	std::pair<int, Entity*> p;
	Collider* c = (Collider*)ent->GetComponent("Collider");
	if(c != nullptr) ps->AddSceneCollider(c);
	ent->setId(lastId);
	p.first = lastId;
	p.second = ent;
	entities.insert(p);
	lastId += 1;
}

void Scene::Clean() {
	entities = std::map<int, Entity*>();
}

void Scene::init()
{
	Clean();
	initShaders();
	map = NULL;
	player = NULL;
	intro = choose = intro_level_1 = level_1 = intro_level_2 = level_2 = end_game = false;
	//PlaySound(TEXT("Sounds/Teenage_Mutant_Ninja_Turtles_Theme.wav"), NULL, SND_ASYNC | SND_LOOP);
	//map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	menu = new Menu(texProgram);
	icon = new Icon(texProgram);
	icon->transform.SetPosition(glm::fvec2(270, 10));

	
	/*Level_1* level1 = new Level_1(texProgram);
	player = new Player();
	player->init(glm::fvec2(SCREEN_X, SCREEN_Y), texProgram);
	//player->setTileMap(map);
	Block* bl = new Block(texProgram);
	bl->transform.SetPosition(player->transform.GetPosition() + glm::fvec2(80, 0));

	//Adding Entities
	AddEntity(level1);
	AddEntity(player); //Player always the first entity
	AddEntity(bl);
	for (int i = 0; i < 2; i++) {
		Enemy* en = new Enemy(texProgram);
		en->transform.SetPosition(player->transform.GetPosition() + glm::fvec2(160 + i * 100, +i * 10));
		AddEntity(en);
	}*/
	AddEntity(menu);
	AddEntity(icon);
	//PlaySound(TEXT("images/Sounds/Teenage_Mutant_Ninja_Turtles_Theme.wav"), NULL, SND_ASYNC | SND_LOOP);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 15), float(SCREEN_HEIGHT - 15), 0.f, -10000.f, 10000.f);
	currentTime = 0.0f;
	character = new Text(texProgram, 4);
	how_to_play = new Text(texProgram, 5);
	credits = new Text(texProgram, 6);
	UpdateSceneColliders();
}


void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	int selected = 1;
	for (auto const& x : entities)
		x.second->update(deltaTime);
	if (!intro){
		if (Game::instance().getKey(' ')){
			int sel = icon->sel;
			switch (sel) {
				case 0: { 
					AddEntity(character);
					menu->GetComponent("Sprite")->setActive(false);
					icon->GetComponent("Sprite")->setActive(false);
					intro = true;
					choose = true;
					break;
				}
				case 1: {
					AddEntity(how_to_play);
					intro = true;
					end_game = true;
					break;
				}
				case 2: { 
					AddEntity(credits);
					intro = true;
					end_game = true;
					break;
				}
			}
		}
	}
	if (choose){
		if (Game::instance().getKey('1') || Game::instance().getKey('2') || Game::instance().getKey('3') || Game::instance().getKey('4')){ ///Possar aqui selected
			character->GetComponent("Sprite")->setActive(false);
			intro1 = new Text(texProgram, 1);
			AddEntity(intro1);
			intro_level_1 = true;
			choose = false;
			
		}
	}
	if (intro_level_1){
		if (Game::instance().getKey(' ')){
			PlaySound(NULL, 0, 0);
			intro1->GetComponent("Sprite")->setActive(false);
			Level_1* level1 = new Level_1(texProgram);
			player = new Player();
			player->init(glm::fvec2(SCREEN_X, SCREEN_Y), texProgram, players[selected]);
			lppos = player->GetPosition();
			AddEntity(level1);
			AddEntity(player);
			intro_level_1 = false;
			level_1 = true;
			loadlevel1();
		}
	}
	if (level_1){
		if (Game::instance().getKey('q')){ //When Rocksteady Die
			Clean();
			Text* intro = new Text(texProgram, 2);
			AddEntity(intro);
			level_1 = false;
			intro_level_2 = true;
		}
	}
	if (intro_level_2){
		if (Game::instance().getKey(' ')){
			//PlaySound(NULL, 0, 0);
			Clean();
			Level_2* level2 = new Level_2(texProgram);
			player = new Player();
			player->init(glm::fvec2(SCREEN_X, SCREEN_Y), texProgram,players[selected]);
			AddEntity(level2);
			AddEntity(player);
			intro_level_2 = false;
			level_2 = true;
		}
	}
	if (level_2){
		//PlaySound(TEXT("images/Sounds/Carpenter_Brut_-_Roller_Mobster.wav"), NULL, SND_ASYNC | SND_LOOP);
		if (Game::instance().getKey('q')){ //When Shredder Die
			Text* intro = new Text(texProgram, 3);
			AddEntity(intro);
			level_2 = false;
			end_game = true;
		}
	}
	if (end_game){
		if (Game::instance().getKey(' ')){
			/*PlaySound(NULL, 0, 0);
			PlaySound(TEXT("images/Sounds/Teenage_Mutant_Ninja_Turtles_Theme.wav"), NULL, SND_ASYNC | SND_LOOP);*/
			Menu* menu = new Menu(texProgram);
			icon = new Icon(texProgram);
			icon->transform.SetPosition(glm::fvec2(270, 10));
			AddEntity(menu);
			AddEntity(icon);
			intro = false;
			end_game = false;
		}
	}
	projection = glm::translate(projection, glm::vec3(camPX, 0, camPY));
	moveCamera(deltaTime);
	ps->physicsLoop();
	if (encount == 0) {
		moveC = true;
		inCombat = false;
	}
	if (player != nullptr && player->transform.GetPosition().x > SCREEN_X + 1500 && !inCombat) {
		intro_level_2 = true;
		Clean();
	}
}

void Scene::render()
{
	glm::mat4 modelview;
	for (auto const& x : entities)
		x.second->render();
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	//map->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


void Scene::moveCamera(int deltaTime) {
	if (!moveC) { camPX = 0; return; }
	if (player != nullptr) {
		if (player->GetVel().x < 0) camPX = 0;
		else camPX = -(float)player->GetVel().x * 1.2 * deltaTime/1000.f;
	}
}

void Scene::loadlevel1()
{
	Block* b1 = new Block(texProgram);
	glm::fvec2 p = player->transform.GetPosition();
	b1->transform.SetPosition(glm::fvec2(SCREEN_X, SCREEN_Y));
	AddEntity(b1);
	Block* b2 = new Block(texProgram);
	b2->transform.SetPosition(glm::fvec2(SCREEN_X, SCREEN_Y+300));
	AddEntity(b2);
	CombatZone* c = new CombatZone(p.x + 50, 3, 0, 0, 0, 0, player, texProgram);
	AddEntity(c);
	CombatZone* c2 = new CombatZone(p.x + 250, 5, 0, 0, 0, 0, player, texProgram);
	AddEntity(c2);
	CombatZone* c3 = new CombatZone(p.x + 500, 3, 0, 1, 0, 0, player, texProgram);
	AddEntity(c3);
	CombatZone* c4 = new CombatZone(p.x + 800, 0, 1, 2, 0, 0, player, texProgram);
	AddEntity(c4);
	CombatZone* c5 = new CombatZone(p.x + 1400, 0, 0, 0, 1, 0, player, texProgram);
	AddEntity(c5);
}

