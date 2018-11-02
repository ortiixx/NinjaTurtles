#pragma once
#include "Entity.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"

class Projectile :
	public Entity
{
public:
	Projectile(ShaderProgram &shaderProgram, glm::fvec2 dir);
	~Projectile();
	void update(int deltaTime);
	void render();
	Texture tex;
	glm::fvec2 dir;
};

