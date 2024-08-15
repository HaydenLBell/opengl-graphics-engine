#version 330 core

// outputs colors in RGBA.
out vec4 FragColor;

// inputs the color from the Vertex Shader.
in vec3 colour;

void main()
{
   FragColor = vec4(colour, 1.0f);
}