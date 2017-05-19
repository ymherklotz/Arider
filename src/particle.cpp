#include "particle.hpp"

#include <YAGE/resourcemanager.hpp>

Particle::Particle() : particle_body_(glm::vec2(200.f/70.f, 600.f/70.f))
{}

Particle::~Particle()
{}

void Particle::setTexture(const std::string &texture_path)
{
	texture_=yage::ResourceManager::getTexture(texture_path);
}

void Particle::renderSprite(yage::SpriteBatch &sprite_batch)
{
	sprite_batch.draw(glm::vec4(70*particle_body_.xPosition(), 70*particle_body_.yPosition(), 50, 50), glm::vec4(0.f, 0.f, 1.f, 1.f), texture_.id, yage::Color(255, 255, 255, 255), 0.f);
	particle_body_.update();
}
