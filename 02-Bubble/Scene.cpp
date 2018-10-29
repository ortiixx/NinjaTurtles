#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Block.h"
#include "Enemy.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

std::map<int, Entity*> Scene::entities = std::map<int, Entity*>();

Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}

Entity* Scene::GetEntity(int id) {
	if(!entities.count(id)) return nullptr;
	return entities[id];
}

PhysicsEngine* Scene::ps = PhysicsEngine::PhysicsGetInstance();


void Scene::RemoveEntity(int id)
{
	if (!entities.count(id)) return;
	Entity* ent = entities[id];
	Collider* c = (Collider*)ent->GetComponent("Collider");
	if (c != nullptr) {
		//PhysicsEngine* ps = PhysicsEngine::PhysicsGetInstance();
		ps->RemoveSceneCollider(c);
	}
	entities.erase(id);
	
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
	ent->setId(lastId);
	p.first = lastId;
	p.second = ent;
	entities.insert(p);
	lastId += 1;
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::fvec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setTileMap(map);
	Block* bl = new Block(texProgram);
	bl->transform.SetPosition(player->transform.GetPosition()+glm::fvec2(80,0));

	//Adding Entities
	AddEntity(player); //Player always the first entity
	AddEntity(bl);
	for (int i = 0; i < 2; i++) {
		Enemy* en = new Enemy(texProgram);
		en->transform.SetPosition(player->transform.GetPosition() + glm::fvec2(160+i*100, +i*10));
		AddEntity(en);
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	UpdateSceneColliders();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	for (auto const& x : entities) 
		x.second->update(deltaTime);
	projection = glm::translate(projection, glm::vec3(camPX, 0, camPY));
	moveCamera();
	ps->physicsLoop();
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
	map->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


void Scene::moveCamera() {
}

