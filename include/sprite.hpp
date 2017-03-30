#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <GL/glew.h>

class Sprite
{
private:
    float x_;
    float y_;
    float width_;
    float height_;
    GLuint vbo_id_ = 0;
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height);
    void draw();
};

#endif
