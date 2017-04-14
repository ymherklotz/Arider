#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "animation.hpp"

#include <YAGE/spritebatch.hpp>

class Block
{
private:
    Animation animation_;    
    int x_;
    int y_;
    int width_;
    int height_;

    // adding physics elements
    double mass_=7850.0/*kg*/;
    // assuming it's a 1mx1mx1m block of steel
    double velocity_=0.0;
    
public:
    Block(const std::string &texture, int x, int y, int width=70, int height=70);
    Block(Animation animation, int x, int y, int width=70, int height=70);

    void render(yage::SpriteBatch &sprite_batch, float depth) const;
};


#endif
