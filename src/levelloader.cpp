#include "levelloader.hpp"

#include <fstream>
#include <stdexcept>

void LevelLoader::loadLevel(const std::string &level_path, std::string &level, int &level_width, int &level_height)
{
    std::ifstream level_file(level_path);

    if(!level_file.is_open())
	throw std::runtime_error("Could not load level: '"+level_path+"'");

    // initialize inputs to be empty
    level="";
    level_width=0;
    level_height=0;
    
    std::string level_line;
    while(getline(level_file, level_line))
    {	
	level+=level_line;
	if(level_width<(int)level_line.length())
	    level_width=level_line.length();
	++level_height;
    }
}

void LevelLoader::drawLevel(yage::SpriteBatch &sprite_batch, const std::string &level, int level_width)
{
    for(int i=0; i<(int)level.size(); ++i)
    {
	switch(level[i])
	{
	case 'b': // brick
	    break;
	case 'e': // empty
	    break;
	case '@': // player
	    break;
	case ' ':
	    break;
	default:
	    throw std::runtime_error("Could not recognize '"+std::to_string(level[i])+"' in level file");
	}
    }
}
