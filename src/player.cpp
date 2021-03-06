#include "player.hpp"

#include <glm/glm.hpp>

Player::Player()
{}

void Player::moveUp()
{
    uv_=glm::vec4(0.f, 0.f, 1.f, 1.f);
    position_+=glm::vec2(0.f, speed_.y);
    animation_.start(AnimationState::IDLE);
}

void Player::moveRight()
{
    uv_=glm::vec4(0.f, 0.f, 1.f, 1.f);
    position_+=glm::vec2(speed_.x, 0.f);
    animation_.start(AnimationState::MOVING);
}

void Player::moveDown()
{
    uv_=glm::vec4(0.f, 0.f, 1.f, 1.f);
    position_+=glm::vec2(0.f, -speed_.y);
    animation_.start(AnimationState::IDLE);
}

void Player::moveLeft()
{
    uv_=glm::vec4(1.f, 0.f, -1.f, 1.f);    
    position_+=glm::vec2(-speed_.x, 0.f);
    animation_.start(AnimationState::MOVING);
}

void Player::idle()
{
    uv_=glm::vec4(1.f, 0.f, -1.f, 1.f);
    animation_.start(AnimationState::IDLE);
}
