#version 130

in vec2 fragment_position;
in vec4 fragment_color;
in vec2 fragment_uv;

out vec4 color;

// uniform float time;
uniform sampler2D texture_sampler;

void main()
{
    vec4 texture_color = texture(texture_sampler, fragment_uv);

    // color = texture_color * fragment_color;
    // color = texture_color * vec4(fragment_color.g*(cos(fragment_position.x*4.0+time)+1.0)/2.0,
    //  		 fragment_color.r*(cos(fragment_position.y*8.0+time)+1.0)/2.0,
    //  		 fragment_color.r*(sin(fragment_position.x*2.0+time)+1.0)/2.0,
    //  		 0.0);
    color=texture_color;
}
