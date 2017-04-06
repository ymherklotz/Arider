#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

#include <YAGE/resourcemanager.hpp>
#include <YAGE/texture.hpp>

#include <glm/glm.hpp>

class Player : public Character
{
public:
    Player();

    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();
    void idle();
};

#endif
