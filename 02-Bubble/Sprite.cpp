#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"
#include <iostream>
#include "Scene.h"

Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, int columns, int animations, Texture *spritesheet, ShaderProgram *program)
{
	this->columns = columns;
	this->quadSize = quadSize;
	name = "Sprite";
	timeAnimation = 0;
	for (int i = 0; i < animations; i++) {
		Anim a;
		this->animations.push_back(a);
	}
	scale = glm::vec2(1.f, 1.f);
	currentFrame = 0;
	framesize = sizeInSpritesheet;
	float vertices[24] = {0.f, 0.f, 0.f, 0.f, 
												quadSize.x, 0.f, sizeInSpritesheet.x, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, 0.f, 0.f, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, quadSize.y, 0.f, sizeInSpritesheet.y};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	position = glm::vec2(0.f);
}

Sprite::Sprite()
{
}

void Sprite::update(int deltaTime)
{
	
	if(currentAnimation >= 0)
	{
		timeAnimation += deltaTime;
		if (
			currentFrame < animations[currentAnimation].startframe
			||
			currentFrame >= animations[currentAnimation].startframe +
			animations[currentAnimation].keyframes
			)
		{
			if (dieAnim == currentAnimation && currentFrame >= animations[currentAnimation].startframe +
				animations[currentAnimation].keyframes) return;
			if (playingOnce) currentAnimation = 0;
			if (animations[currentAnimation].once) playingOnce = true;
			currentFrame = animations[currentAnimation].startframe;
		}
		if(timeAnimation > animations[currentAnimation].speed)
		{
			timeAnimation = 0;
			texCoordDispl.x = (currentFrame % (int)columns)*framesize.x;
			texCoordDispl.y = framesize.y* (int)(currentFrame / columns);
			currentFrame++;
		}

	}
}

void Sprite::render() const
{
	transform->SetLastPosition(transform->GetPosition());
	glm::fvec2 scale = transform->GetScale();
	glm::fvec2 position = transform->GetPosition();
	glm::mat4 modelview = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, layer));
	modelview = glm::translate(modelview, glm::vec3(quadSize.x / 2.f, quadSize.y / 2.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(scale.x, scale.y, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-quadSize.x / 2.f, -quadSize.y / 2.f, 0.f));


	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimation(int animId, int sKey, int length, int keyframesPerSec, bool once)
{
	Anim a;
	a.startframe = sKey;
	a.keyframes = length;
	a.speed = 1000.f / keyframesPerSec;
	a.once = once;
	animations[animId] = a;
}

void Sprite::changeAnimation(int animId)
{
	if (animId != dieAnim && (currentAnimation >= 0 && animations[currentAnimation].once && !animations[animId].once)) return;
	currentAnimation = animId;
	playingOnce = false;
}

void Sprite::Die()
{
	changeAnimation(dieAnim);
	Collider* c = (Collider*)Scene::GetEntity(entityId)->GetComponent("Collider");
	if (c != nullptr)
		c->setActive(false);
}

int Sprite::animation() const
{
	return currentAnimation;
}
