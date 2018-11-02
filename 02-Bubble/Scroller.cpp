#include "Scroller.h"
#include "Texture.h"


Scroller::Scroller(ShaderProgram prog)
{
	Texture tex;
	tex.loadFromFile("images/Levels/background_city.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spr = new Sprite(glm::fvec2(500, 500), glm::fvec2(1, 1), 1, 1, &tex, &prog);
	spr->customZ = true;
	spr->layer = -999;
	AddComponent(spr);
}


Scroller::~Scroller()
{
}
