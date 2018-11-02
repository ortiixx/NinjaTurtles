#pragma once
#include "Entity.h"
#include "Sprite.h"

class Scroller :
	public Entity
{
public:
	Scroller(ShaderProgram prog);
	~Scroller();
	Sprite* spr;
};

