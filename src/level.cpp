#include "level.hpp"

#include <YAGE/resourcemanager.hpp>
#include <YAGE/vertex.hpp>

#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <stdexcept>

void Level::loadLevel(const std::string &level_path)
{
    std::ifstream level_file(level_path);

    if(!level_file.is_open())
	throw std::runtime_error("Could not load level: '"+level_path+"'");

    // initialize inputs to be empty
    level_="";
    width_=0;
    height_=0;
    
    std::string level_line;
    while(getline(level_file, level_line))
    {	
	int width=0;
	for(auto &&character : level_line)
	    if(character!=' ')
	    {
		level_+=character;
		++width;
	    }
	
	if(width>width_)
	    width_=width;
	++height_;
    }
}

void Level::drawLevel(yage::SpriteBatch &sprite_batch)
{
    const float block_size=70.f;
    for(int i=0; i<(int)level_.size(); ++i)
    {
	switch(level_[i])
	{
	case 'b': // brick
	    sprite_batch.draw(glm::vec4(block_size*(i%width_), block_size*(height_-i/width_-1), block_size, block_size), glm::vec4(0.f, 0.f, 1.f, 1.f), yage::ResourceManager::getTexture("res/textures/Tiles/stoneCenter.png").id, yage::Color(255, 255, 255, 255), -1.f);
	case 't': // top brick
	    sprite_batch.draw(glm::vec4(block_size*(i%width_), block_size*(height_-i/width_-1), block_size, block_size), glm::vec4(0.f, 0.f, 1.f, 1.f), yage::ResourceManager::getTexture("res/textures/Tiles/stoneMid.png").id, yage::Color(255, 255, 255, 255), -1.f);
	    break;
	case '.': // empty
	    break;
	case '@': // player
	    break;
	case ' ':
	    break;
	default:
	    throw std::runtime_error("Could not recognize '"+std::to_string((const char)level_[i])+"' in level file");
	}
    }
}
