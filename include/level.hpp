#ifndef LEVEL_LOADER_HPP
#define LEVEL_LOADER_HPP

#include "player.hpp"

#include <YAGE/spritebatch.hpp>

#include <string>

class Level {
private:
    int width_;
    int height_;
    std::string level_;
    
public:
    void loadLevel(const std::string &level_path);
    void drawLevel(yage::SpriteBatch &sprite_batch);
};

#endif
