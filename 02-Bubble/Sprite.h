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
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, int columns, int animations, Texture *spritesheet, ShaderProgram *program);

	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, int columns, int animations, Texture *spritesheet, ShaderProgram *program);
	Sprite();
	void update(int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimation(int animId, int sKey, int length, int keyframesPerSec);
	void changeAnimation(int animId);
	int animation() const;

private:
	struct Anim {
		float speed;
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
	vector<Anim> animations;
};


#endif // _SPRITE_INCLUDE

