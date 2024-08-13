#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// vertex Shader source code.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// fragment Shader source code.
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
	// initialize GLFW.
	glfwInit();

	// tell GLFW what version of OpenGL we are using .
	// in this case OpenGL 3.3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// tell GLFW we are using the CORE profile.
	// so that means we only have the modern functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL".
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// error check if the window fails to create.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// introduce the window into the current context.
	glfwMakeContextCurrent(window);

	// load GLAD so it configures OpenGL.
	gladLoadGL();
	// specify the viewport of OpenGL in the Window.
	// in this case the viewport goes from x = 0, y = 0, to x = 800, y = 800.
	glViewport(0, 0, 800, 800);



	// create Vertex Shader Object and get its reference.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach Vertex Shader source to the Vertex Shader Object.
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile the Vertex Shader into machine code.
	glCompileShader(vertexShader);

	// create Fragment Shader Object and get its reference.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach Fragment Shader source to the Fragment Shader Object.
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile the Vertex Shader into machine code.
	glCompileShader(fragmentShader);

	// create Shader Program Object and get its reference.
	GLuint shaderProgram = glCreateProgram();
	// attach the Vertex and Fragment Shaders to the Shader Program.
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// wrap-up/Link all the shaders together into the Shader Program.
	glLinkProgram(shaderProgram);

	// delete the now useless Vertex and Fragment Shader objects.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	// create reference containers for the Vertex Array Object and the Vertex Buffer Object.
	GLuint VAO, VBO;

	// generate the VAO and VBO with only 1 object each.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// make the VAO the current Vertex Array Object by binding it.
	glBindVertexArray(VAO);

	// bind the VBO specifying it's a GL_ARRAY_BUFFER.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// introduce the vertices into the VBO.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// configure the Vertex Attribute so that OpenGL knows how to read the VBO.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// enable the Vertex Attribute so that OpenGL knows to use it.
	glEnableVertexAttribArray(0);

	// bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Main loop.
	while (!glfwWindowShouldClose(window))
	{
		// specify the color of the background.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean the back buffer and assign the new color to it.
		glClear(GL_COLOR_BUFFER_BIT);
		// tell OpenGL which Shader Program we want to use.
		glUseProgram(shaderProgram);
		// bind the VAO so OpenGL knows to use it.
		glBindVertexArray(VAO);
		// draw the triangle using the GL_TRIANGLES primitive.
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// swap the back buffer with the front buffer.
		glfwSwapBuffers(window);
		// take care of all GLFW events.
		glfwPollEvents();
	}



	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}