#include "sprite.hpp"

Sprite::Sprite()
{}

Sprite::~Sprite()
{
    if(vbo_id_ != 0)
	glDeleteBuffers(1, &vbo_id_);
}

void Sprite::init(float x, float y, float width, float height)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;

    if(vbo_id_ == 0)
    {
	glGenBuffers(1, &vbo_id_);
    }

    float vertex_data[12];

    vertex_data[0] = x+width;
    vertex_data[1] = y+height;

    vertex_data[2] = x;
    vertex_data[3] = y+height;

    vertex_data[4] = x;
    vertex_data[5] = y;

    vertex_data[6] = x+width;
    vertex_data[7] = y;

    vertex_data[8] = x;
    vertex_data[9] = y;

    vertex_data[10] = x+width;
    vertex_data[11] = y+height;

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);    
}
