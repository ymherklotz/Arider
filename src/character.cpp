#include "character.hpp"

#include <YAGE/vertex.hpp>

void Character::create(const glm::vec2 &position/*=glm::vec2(0.f, 0.f)*/,
		       const glm::vec2 &size/*=glm::vec2(50.f, 50.f)*/,
		       const glm::vec2 &speed/*=glm::vec2(1.f, 1.f)*/)
{
    uv_=glm::vec4(0.f, 0.f, 1.f, 1.f);
    position_=position;
    size_=size;
    speed_=speed;
}

void Character::renderSprite(yage::SpriteBatch &sprite_batch) const
{
    sprite_batch.draw(glm::vec4(position_.x, position_.y, size_.x, size_.y), uv_, animation_.currentFrame().id, yage::Color(255, 255, 255, 255), 0.f);
}
