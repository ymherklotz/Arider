#include "arider_config.hpp"
#include "game.hpp"

#include <exception>
#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    std::cout<<"Arider\nVersion: "<<ARIDER_MAJOR_VERSION<<"."<<ARIDER_MINOR_VERSION
	     <<"."<<ARIDER_PATCH_VERSION<<std::endl;

    Game game;

    try
    {
	game.run();
    }
    catch(std::exception &e)
    {
	std::cerr<<"Error : "<<e.what()<<std::endl;
    }
    catch(...)
    {
	std::cerr<<"Error : Exception occured"<<std::endl;
    }

    return 0;
}
