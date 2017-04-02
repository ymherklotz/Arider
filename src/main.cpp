#include "arider_config.hpp"
#include "game.hpp"

#include <GL/glew.h>

#include <exception>
#include <iostream>

int main()
{
    std::cout<<"Arider\nVersion: "<<ARIDER_MAJOR_VERSION<<"."<<ARIDER_MINOR_VERSION
	     <<"."<<ARIDER_PATCH_VERSION<<'\n';

    Game game;

    try
    {
	game.run();
    }
    catch(std::exception &e)
    {
	std::cerr<<"Error : "<<e.what()<<'\n';
    }
    catch(...)
    {
	std::cerr<<"Error : Exception occured\n";
    }

    return 0;
}
