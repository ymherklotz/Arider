#include "animation.hpp"

#include <iostream>

Animation::Animation() : current_animation_(AnimationState::IDLE)
{}

void Animation::pushFrame(AnimationState state, const std::string &texture_path)
{
	frame_animations_[state].push_back(yage::ResourceManager::getTexture(texture_path));
}

yage::Texture Animation::currentFrame() const
{
	int current_index=current_index_;
	if(current_index_>(int)frame_animations_.find(current_animation_)->second.size()-1)
		current_index=0;
	return frame_animations_.find(current_animation_)->second[current_index];
}

void Animation::start(AnimationState state)
{
	if(current_animation_!=state)
		current_animation_=state;
}

void Animation::nextFrame()
{
	if(current_index_+1<(int)frame_animations_.find(current_animation_)->second.size())
		++current_index_;
	else
		current_index_=0;
}
