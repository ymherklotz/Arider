#ifndef LEVEL_LOADER_HPP
#define LEVEL_LOADER_HPP

#include "player.hpp"

#include <YAGE/spritebatch.hpp>

#include <string>

class LevelLoader {
public:
    static void loadLevel(const std::string &level_path, std::string &level, int &level_width, int &level_height);
    static void drawLevel(yage::SpriteBatch &sprite_batch, const std::string &level, int level_width);
};

#endif
