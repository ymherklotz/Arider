#include "animation.hpp"

#include <iostream>

void Animation::pushFrame(const std::string &animation_name, const std::string &texture_path)
{
    frame_animations_[animation_name].push_back(yage::ResourceManager::getTexture(texture_path));
}

yage::Texture Animation::currentFrame() const
{
    return frame_animations_.find(current_animation_)->second[current_index_];
}

void Animation::start(const std::string &animation_name)
{
    if(current_animation_!=animation_name)
    {
	current_animation_=animation_name;
    }
}

void Animation::nextFrame()
{
    if(current_index_+1<(int)frame_animations_.find(current_animation_)->second.size())
	++current_index_;
    else
	current_index_=0;
    std::cout<<"id: "<<frame_animations_.find(current_animation_)->second[current_index_].id<<'\n';
    std::cout<<"index: "<<current_index_<<'\n';
    std::cout<<"size: "<<(int)frame_animations_.find(current_animation_)->second.size()<<'\n';
}
