#version 410 core
// first attribute is the vertex values from VAO
layout (location=0) in vec3 inVert;
// second attribute is the UV values from VAO
layout (location=1)in vec2 inUV;

out vec2 vertUV;

void main()
{
    gl_Position = vec4(inVert,1.0);
    vertUV=inUV.st;
}
