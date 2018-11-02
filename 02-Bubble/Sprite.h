#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include "Texture.h"
#include "ShaderProgram.h"
#include "EntityComponent.h"
// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 

class Sprite : public EntityComponent
{

public:
	// Textured quads can only be created inside an OpenGL context
	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, int columns, int animations, Texture *spritesheet, ShaderProgram *program);
	Sprite();
	void update(int deltaTime);
	void render() const;
	void free();
	void setNumberAnimations(int nAnimations);
	void setAnimation(int animId, int sKey, int length, int keyframesPerSec, bool once);
	void changeAnimation(int animId);
	void setDieAnim(int anim) { dieAnim = anim; }
	void Die();
	int animation() const;
	float layer = 0;
	bool customZ;
	void setCoord(glm::fvec2 c) { texCoordDispl = c; }
private:
	struct Anim {
		float speed;
		bool once;
		int keyframes;
		int startframe;
	};

	Texture *texture;
	ShaderProgram *shaderProgram;
	glm::vec2 quadSize, framesize;
	GLuint vao;
	GLuint vbo;
	GLint posLocation;
	GLint texCoordLocation;
	float columns, timeAnimation;
	glm::fvec2 texCoordDispl;
	int currentAnimation;
	int currentFrame;
	int dieAnim = -10;
	vector<Anim> animations;
	glm::fvec2 position, scale;
	bool playingOnce = false;
};


#endif // _SPRITE_INCLUDE

