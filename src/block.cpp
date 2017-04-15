#include "block.hpp"

#include <YAGE/vertex.hpp>

Block::Block(const std::string &texture, int x, int y, int width, int height):
	x_(x), y_(y),
	width_(width), height_(height)
{
	animation_.pushFrame(AnimationState::STILL, texture);
}

Block::Block(Animation animation, int x, int y, int width, int height) :
	animation_(animation),
	x_(x), y_(y),
	width_(width), height_(height)
{}

void Block::render(yage::SpriteBatch &sprite_batch, float depth) const
{
	sprite_batch.draw(glm::vec4(x_, y_, width_, height_), glm::vec4(0.f, 0.f, 1.f, 1.f), animation_.currentFrame().id, yage::Color(255, 255, 255, 255), depth);
}
