#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// samplers de texturas
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
	// interpola de forma linear entre cada textura (usando mixvalue)
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}