#include "levelloader.hpp"

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
	level_+=level_line;
	if(width_<(int)level_line.length())
	    width_=level_line.length();
	++height_;
    }
}

void Level::drawLevel(yage::SpriteBatch &sprite_batch)
{
    for(int i=0; i<(int)level_.size(); ++i)
    {
	switch(level_[i])
	{
	case 'b': // brick
	    sprite_batch.draw(glm::vec4(70*(i%width_), 70*(height_-i/width_-1), 70.f, 70.f), glm::vec4(0.f, 0.f, 1.f, 1.f), yage::ResourceManager::getTexture("res/textures/Tiles/stoneMid.png").id, yage::Color(255, 255, 255, 255), 5.f);
	    break;
	case 'e': // empty
	    break;
	case '@': // player
	    break;
	case ' ':
	    break;
	default:
	    throw std::runtime_error("Could not recognize '"+std::to_string(level_[i])+"' in level file");
	}
    }
}
