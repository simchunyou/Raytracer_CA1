#version 410 core
//Pointer to the current 2D texture object
uniform sampler2D tex;

//uniform int screenWidth;
//uniform int screenHeight;
//the vertex uv
in vec2 vertUV;
// the final fragment colour
layout (location =0) out vec4 outColour;

void main()
{
    /*fragmentColour = vec4(0.0,0.0,0.0,0.0);
    int newWidth = 512*screenWidth/1024;
    if(gl_FragCoord.x>(newWidth))
    {
        fragmentColour = vec4(1,0,1,0);
    }*/
     outColour = texture(tex,vertUV);
}
