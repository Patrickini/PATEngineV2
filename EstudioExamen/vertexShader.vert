#version 450 core                           
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 texCoord;
 
 out vec4 color;

void main()
{
  color = inColor;
  gl_Position = vec4(inPosition, 1.0);
}