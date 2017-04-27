#include <glew.h>
#include <glut.h>
#include "ioutility.h"

const GLint cWindowWidth = 600;
const GLint cWindowHeight = 600;

const char* cWindowTitle = "Shader Example";

const char* cVertexShader = "VertexShader.vert";
const char* cFragmentshader = "FragmentShader.frag";

const GLclampf cBackgroundColourR = 0.0f;
const GLclampf cBackgroundColourG = 0.0f;
const GLclampf cBackgroundColourB = 0.0f;
const GLclampf cBackgroundColourA = 0.0f;

float currentRotation = 0.0f;

GLint window1ID;

GLuint shaderProgramID;
GLuint vaoHandle = 0;

float positionData[] =
{
	-0.75f, -0.75f, 0.0f,
	0.75f, -0.75f, 0.0f,
	0.0f, 0.75f, 0.0f
};

float colourData[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

float toggleData[9] = { false };

char* vertexShader = nullptr;
char* fragmentShader = nullptr;

void resize(GLsizei width, GLsizei height)
{
	GLfloat aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
	glViewport(0, 0, width, height);
}

void initializeGL()
{
	/* Set the window's background colour */
	glClearColor(cBackgroundColourR, cBackgroundColourG, cBackgroundColourB, cBackgroundColourA);

	/* Set the window's clear depth */
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_PROJECTION);

}

/**
 * \brief Check if a shader has compiled successfully
 * \param id shader id
 * \return True if shader compiled successfully
 */
bool isShaderCompiled(const GLuint& id)
{
	GLint compileStatus;

	/* Obtain the compile status of the shader */
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);  // Return the compile status from the shader

	if (compileStatus == GL_FALSE)
	{		
		/* Create a char buffer to store the error message */
		GLchar errorMessage[512];

		/* Obtain the error message */
		glGetProgramInfoLog(id, sizeof(errorMessage), nullptr, &errorMessage[0]);

		/* Output the error message */
		printf("Error: Shader compilation failed: %s\n", errorMessage);

		return false;
	}

	return true;
}

/*
 * \brief Checks if a shader is linked to the application correctly
 * \param id shader id
 * \return True if the shader is linked correctly
 */
bool isShaderLinked(const GLuint& id)
{
	/* Obtain the linker status of the shader */
	GLint linkerStatus;
	glGetProgramiv(id, GL_LINK_STATUS, &linkerStatus);

	if(linkerStatus == GL_FALSE)
	{
		/* Create a char buffer to store the error message */
		GLchar errorMessage[512];

		/* Obtain the error message */
		glGetProgramInfoLog(id, sizeof(errorMessage), nullptr, &errorMessage[0]);

		/* Output the error message */
		printf("Error: Shader linking failed: %s\n", errorMessage);

		return false;
	}

	/* Check if the application is valid */
	glValidateProgram(id);

	/* Obtain the result of the validation process*/
	GLint validateStatus;
	glGetProgramiv(id, GL_VALIDATE_STATUS, &validateStatus); // Return the result of the validation process.

	if(validateStatus == GL_FALSE)
	{
		/* Create a char buffer to store the error message */
		GLchar errorMessage[512];

		/* Obtain the error message */
		glGetProgramInfoLog(id, sizeof(errorMessage), nullptr, &errorMessage[0]);

		/* Output the error message */
		printf("Error: Shader validation failed: %s\n", errorMessage);

		return false;
	}

	return true;
}

bool initializeShaders()
{
	/* Create a program object for shaders to attach to */
	shaderProgramID = glCreateProgram();

	/* Create an empty vertex shader program */
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	/* Create an empty fragment shader program */
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	/* Load the vertex shader file */
	vertexShader = IOUtility::readFile(cVertexShader);

	/* Transfer the contents of the loaded vertex shader file into the empty vertex shader program */
	glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);

	/* Compile the vertex shader */
	glCompileShader(vertexShaderID);

	/* Check for compile errors in the vertex shader */
	if(!isShaderCompiled(vertexShaderID))
	{
		return -1;
	}


	/* Attach the vertex shader to the main program */
	glAttachShader(shaderProgramID, vertexShaderID);
	
	/* Load the fragment shader file */
	fragmentShader = IOUtility::readFile(cFragmentshader);

	/* Transfer the contents of the loaded fragment shader file into the empty fragment shader program */
	glShaderSource(fragmentShaderID, 1, &fragmentShader, nullptr);

	/* Compile the fragment shader */
	glCompileShader(fragmentShaderID);

	/* Check for compile errors in the fragment shader */
	if (!isShaderCompiled(fragmentShaderID))
	{
		return false;
	}

	/* Attach the fragment shader to the shader program */
	glAttachShader(shaderProgramID, fragmentShaderID);

	/* Bind index 0 to the shader input variable "VertexPosition" */
	glBindAttribLocation(shaderProgramID, 0, "VertexPosition");

	/* Bind index 1 to the shader input variable "VertexColour" */
	glBindAttribLocation(shaderProgramID, 1, "VertexColor");

	/* Set the shader program */
	glUseProgram(shaderProgramID);

	/* Create Vertex Buffer Objects */
	GLuint vboHandles[2];

	glGenBuffers(2, vboHandles);

	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];

	/* Populate the position buffer */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

	/* Populate the colour buffer */
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colourData), colourData, GL_STATIC_DRAW);

	/* Generate a name for the vertex array */
	glGenVertexArrays(1, &vaoHandle);

	// Bind the vertex arary object
	glBindVertexArray(vaoHandle);

	// Enable the vertex array
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Map index 0 to the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<GLubyte *>(nullptr));

	// Map index 1 to the colour buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, static_cast<GLubyte*>(nullptr));

	// Send the vertex shader program to the GPU vertex processor, and the fragment shader program to the GPU fragment processor
	glLinkProgram(shaderProgramID);

	// Check for Linker errors
	if(!isShaderLinked(shaderProgramID))
	{
		return false;
	}

	return true;
}

void paint()
{
	/* Clear the colour and depth buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Use shader program which has already been setup in main()
	glUseProgram(shaderProgramID);

	// Increment the shaders rotation
	GLint rotationUniform = glGetUniformLocation(shaderProgramID, "angle");
	glUniform1f(rotationUniform, currentRotation);
	currentRotation += 0.005f;
	
	// Draw the triangle
	glBindVertexArray(vaoHandle);

	glPointSize(10.0f);
	glDrawArrays(GL_POLYGON, 0, 3);

	//Unbind the shader program
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	/* Initialize the Glut library */
	glutInit(&argc, argv);

	/* Set the display mode */
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	/* Set the window size */
	glutInitWindowSize(cWindowWidth, cWindowHeight);

	/* Create the window */
	glutCreateWindow(cWindowTitle);

	/* Initialize OpenGL */
	initializeGL();

	/* Initialize Glew */
	glewInit();

	/* Check if the OpenGL Shading Language is supported */
	if (!GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		printf("Error: OpenGL Shading Language is not supported.\n");
		return -1;
	}

	/* Initialize the vertex and fragment shaders */
	if(!initializeShaders())
	{
		return -1;
	}

	/* Set Glut's display callback function */
	glutDisplayFunc(paint);

	/* Set Glut's resize callback function */
	glutReshapeFunc(resize);

	/* Enter the Glut processing loop */
	glutMainLoop();

	return 0;
}