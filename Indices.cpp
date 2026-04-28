#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.27f, 0.51f, 0.70f, 1.0f);\n"
"}\n\0";

int main() {

	glfwInit();  //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Tell GLFW what version of OpenGL we're using, in this case we're using version 3.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tell GLFW we're using the CORE(for modern functions alone) profile not COMPATIBILITY(for both modern and legacy functions)

	GLfloat vertices[] =   // vertices coordination
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // bottom left corner of triangle
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // bottom right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // top corner
		-0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner right
		0.0f, -0.5f * float(sqrt(3)) /3, 0.0f //Inner down
	};

	GLuint indices[] =
	{
		0,3,5,// lower left trangle
		3,2,4, // lower triangle
		5,4,1 //upper triangle
	};



	GLFWwindow* window = glfwCreateWindow(800, 800, "My First Window", NULL, NULL);  //creating a GLFWwindow object of 800(width) by 800(length) pixels, and naming it
	if (window == NULL)
	{
		std::cout << "Failed t create GLFW window" << std::endl;  // error to check if the window fails to crete
		return -1;
	}
	glfwMakeContextCurrent(window);  // introduce the window to the current context

	gladLoadGL();  //loading GLAD so it configure OpenGL
	glViewport(0, 0, 800, 800);  //specify the veiwport of OpenGL in the window. In this case, the veiwpoint goes from x=0, y=0 to x=800, y=800


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);  // Create Vertex Shader Object and get its reference
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);  // Attach Vertex Shader source to the Vertex Shader Object
	glCompileShader(vertexShader);// Compile the Vertex Shader into machine code


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);  // Create Fragment Shader Object and get its reference
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);  // Attach Fragment Shader source to the Fragment Shader Object
	glCompileShader(fragmentShader);  // Compile the Vertex Shader into machine code

	GLuint shaderProgram = glCreateProgram();  // Create Shader Program Object and get its reference
	glAttachShader(shaderProgram, vertexShader);  // Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);// Wrap-up/Link all the shaders together into the Shader Program


	glDeleteShader(vertexShader);  // Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(fragmentShader);



	GLuint VAO, VBO, EBO;// create reference containers for the vartex array object and the vertex buffer object

	glGenVertexArrays(1, &VAO);  // Generate the VAO and VBO with only 1 object each
	glGenBuffers(1, &VBO);
	glad_glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);   // Make the VAO the current Vertex Array Object by binding it

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);  //specify the background color
	glClear(GL_COLOR_BUFFER_BIT);  // clean the back buffer with the front buffer
	glfwSwapBuffers(window);  // swap the back buffer with the front buffer

	while (!glfwWindowShouldClose(window))   // while loop to make sure window stays open
	{
		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();  // necessarry stuff to take care of all glfw events ig 
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);  // delete window before ending program
	glfwTerminate();  // terminate GFLW before ending the program

	return 0;
}