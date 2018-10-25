#pragma once
#include <glm/glm.hpp>
class Transform 
{
public:
	Transform(glm::ivec2 position, glm::ivec2 scale);
	Transform();
	~Transform();
	glm::ivec2 GetScale() { return this->scale; }
	void SetScale(const glm::ivec2 &scale) { this->scale = scale; }
	void SetPosition(const glm::ivec2 &position) { this->lastPosition = this->position;  this->position = position; }
	void SetLastPosition(const glm::ivec2 &position) { this->lastPosition = position; }
	glm::ivec2 GetPosition() { return position; }
	glm::ivec2 GetLastPosition() { return lastPosition; }
private:
	glm::ivec2 position;
	glm::ivec2 lastPosition;
	glm::ivec2 scale;

};

