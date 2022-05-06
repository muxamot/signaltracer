#version 330

layout (location = 0) in vec3 Position; 
layout (location = 1) in vec2 TexCoord; 

uniform mat4 gWorld; 
uniform int SamplingEnabled;
uniform int MonocolorEnabled;

out vec4 Color;
out vec2 TexCoord0;
flat out int SamplingNeeded;
flat out int MonocolorEnabled0;

void main() 
{ 
	if(SamplingEnabled != 0) {
		TexCoord0 = TexCoord;
	} else {
		float cl = clamp(fract(abs(Position.x + Position.y + Position.z)), 0.1, 0.9);
		Color = vec4(cl, cl, cl, 1.0);
	}

	SamplingNeeded = SamplingEnabled;
	MonocolorEnabled0 = MonocolorEnabled;
	gl_Position = gWorld * vec4(Position, 1.0); 
}