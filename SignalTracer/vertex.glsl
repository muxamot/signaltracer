#version 330

layout (location = 0) in vec3 Position; 
layout (location = 1) in vec2 TexCoord; 

uniform mat4 gWorld; 

out vec4 Color;

void main() 
{ 
	float cl = clamp(fract(abs(Position.x + Position.y + Position.z)), 0.1, 0.9);
	gl_Position = gWorld * vec4(Position, 1.0); 
	Color = vec4(cl, cl, cl, 1.0);
}