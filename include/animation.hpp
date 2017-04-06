#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <YAGE/resourcemanager.hpp>
#include <YAGE/texture.hpp>

#include <glm/glm.hpp>

#include <iostream>
#include <unordered_map>
#include <vector>

class Animation
{
private:
    std::unordered_map<std::string, std::vector<yage::Texture>> frame_animations_;
    std::string current_animation_;
    int current_index_=0;
public:
    Animation() {}

    void pushFrame(const std::string &animation_name, const std::string &texture_path);
    yage::Texture currentFrame() const;
    void start(const std::string &animation_name);
    void nextFrame();

    template<typename First, typename Second, typename ...Rest>
    void initializeAnimation(const std::string &animation_name, First &&first, Second &&second, Rest &&...rest)
    {
	frame_animations_[animation_name].push_back(yage::ResourceManager::getTexture(std::forward<First>(first)));
	initializeAnimation(std::forward<Second>(second), std::forward<Rest>(rest)...);
    }

    template<typename Last>
    void initializeAnimation(const std::string &animation_name, Last &&last)
    {
	frame_animations_[animation_name].push_back(yage::ResourceManager::getTexture(std::forward<Last>(last)));
    }
};

#endif
