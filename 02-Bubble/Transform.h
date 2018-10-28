#pragma once
#include <glm/glm.hpp>
class Transform 
{
public:
	Transform(glm::fvec2 position, glm::fvec2 scale);
	Transform();
	~Transform();
	glm::fvec2 GetScale() { return this->scale; }
	void SetScale(const glm::fvec2 &scale) { this->scale = scale; }
	void SetPosition(const glm::fvec2 &position) { this->lastPosition = this->position;  this->position = position; }
	void SetLastPosition(const glm::fvec2 &position) { this->lastPosition = position; }
	glm::fvec2 GetPosition() { return position; }
	glm::fvec2 GetLastPosition() { return lastPosition; }
private:
	glm::fvec2 position;
	glm::fvec2 lastPosition;
	glm::fvec2 scale;

};

