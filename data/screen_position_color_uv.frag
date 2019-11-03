#version 330 core
out vec4 FragColor;
in vec3 Color;
in vec2 UV;
uniform sampler2D ourTexture;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //FragColor = vec4(Color.rgb, 1.0f);
	FragColor = texture(ourTexture, UV) * vec4(Color.rgb, 1.0f);
};