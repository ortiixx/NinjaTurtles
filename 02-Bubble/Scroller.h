#pragma once
#include "Entity.h"
#include "Sprite.h"

class Scroller :
	public Entity
{
public:
	Scroller(ShaderProgram &prog);
	void update(int deltaTime);
	~Scroller();
	Sprite* spr;
};

