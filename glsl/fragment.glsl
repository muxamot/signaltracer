#version 330 

in vec4 Color;
in vec2 TexCoord0;
flat in int SamplingNeeded;
flat in int MonocolorEnabled0;

out vec4 FragColor; 

uniform sampler2D Sampler0;

void main()
{ 
	if(SamplingNeeded != 0) {
		FragColor = texture2D(Sampler0, TexCoord0.xy);
	} else {
		if(MonocolorEnabled0 != 0){
			FragColor = vec4(0.0, 1.0, 0.0, 1.0);
		} else {
			FragColor = Color;
		}
	}
}
