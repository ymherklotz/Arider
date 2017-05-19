#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "animation.hpp"

#include <glm/glm.hpp>

#include <YAGE/spritebatch.hpp>
#include <YAGE/texture.hpp>

#include <string>
#include <vector>

class Character
{
public:
	Animation animation_;    
protected:
	glm::vec4 uv_;
	glm::vec2 position_;
	glm::vec2 size_;
	glm::vec2 speed_;
    
public:
	Character() {}
	virtual ~Character() {}

	virtual void moveUp()=0;
	virtual void moveRight()=0;
	virtual void moveDown()=0;
	virtual void moveLeft()=0;
	virtual void idle()=0;

	void create(const glm::vec2 &position=glm::vec2(0.f, 0.f),
	            const glm::vec2 &size=glm::vec2(50.f, 50.f),
	            const glm::vec2 &speed=glm::vec2(1.f, 1.f));
	void renderSprite(yage::SpriteBatch &sprite_batch) const;
};

#endif
