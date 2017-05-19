#ifndef ARIDER_PARTICLE_HPP
#define ARIDER_PARTICLE_HPP

#include <glm/glm.hpp>

#include <YAGE/Physics/particlebody.hpp>
#include <YAGE/texturecache.hpp>
#include <YAGE/spritebatch.hpp>


class Particle
{
private:
	yage::ParticleBody particle_body_;
	yage::Texture texture_;
	
public:
	Particle();
	~Particle();

	void setTexture(const std::string &texture_path);
	void renderSprite(yage::SpriteBatch &sprite_batch);
};

#endif
