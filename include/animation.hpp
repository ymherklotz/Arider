#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <YAGE/resourcemanager.hpp>
#include <YAGE/texture.hpp>

#include <glm/glm.hpp>

#include <iostream>
#include <unordered_map>
#include <vector>

enum class AnimationState
{
    STILL,
    IDLE,
    MOVING,
    JUMPING,
    CROUCHING,
    FALLING,
};

class Animation
{
private:
    std::unordered_map<AnimationState, std::vector<yage::Texture>> frame_animations_;
    AnimationState current_animation_;
    int current_index_=0;
public:
    Animation(); 

    void pushFrame(AnimationState state, const std::string &texture_path);
    yage::Texture currentFrame() const;
    void start(AnimationState state);
    void nextFrame();

    template<typename First, typename Second, typename ...Rest>
    void initializeAnimation(AnimationState state, First &&first, Second &&second, Rest &&...rest)
    {
	frame_animations_[state].push_back(yage::ResourceManager::getTexture(std::forward<First>(first)));
	initializeAnimation(std::forward<Second>(second), std::forward<Rest>(rest)...);
    }

    template<typename Last>
    void initializeAnimation(AnimationState state, Last &&last)
    {
	frame_animations_[state].push_back(yage::ResourceManager::getTexture(std::forward<Last>(last)));
    }
};

#endif
