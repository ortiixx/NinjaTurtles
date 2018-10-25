#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Block.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

PhysicsEngine* PhysicsEngine::instance = nullptr;

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

void Scene::UpdateSceneColliders() {
	for (int i = 0; i < entities.size(); i++) {
		Collider* c = (Collider *)entities[i]->GetComponent("Collider");
		if (c != nullptr) ps->AddSceneCollider(c);
	}
}

void Scene::init()
{
	initShaders();
	ps = PhysicsEngine::PhysicsGetInstance();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setTileMap(map);
	Block* bl = new Block(texProgram);
	bl->transform.SetPosition(player->transform.GetPosition());
	entities.push_back(player);
	entities.push_back(bl);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	UpdateSceneColliders();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	for (int i = 0; i < entities.size(); i++)
		entities[i]->update(deltaTime);
	projection = glm::translate(projection, glm::vec3(camPX, 0, camPY));
	moveCamera();
	ps->physicsLoop();
}

void Scene::render()
{
	glm::mat4 modelview;
	for (int i = 0; i < entities.size(); i++)
		entities[i]->render();
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

