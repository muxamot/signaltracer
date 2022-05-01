#version 330 

in vec4 Color;
in vec2 TexCoord0;
flat in int SamplingNeeded;

out vec4 FragColor; 

uniform sampler2D Sampler0;

void main()
{ 
	if(SamplingNeeded != 0) {
		FragColor = texture2D(Sampler0, TexCoord0.xy);
	} else {
		FragColor = Color;
	}
}
