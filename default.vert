#version 330 core

// positions / Coordinates.
layout (location = 0) in vec3 aPos;
// colours.
layout (location = 1) in vec3 aColour;


// outputs the colour for the Fragment Shader.
out vec3 colour;
// controls the scale of the vertices.
uniform float scale;


void main()
{
	// outputs the positions/coordinates of all vertices.
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// assigns the colours from the Vertex Data to "colour".
	colour = aColour;
}