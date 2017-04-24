#include <glut.h>
#include <ilut.h>

const char* cWindowTitle = "Textures Example";

const GLint cWindowSizeX = 640;
const GLint cWindowSizeY = 480;

const GLclampf cBackgroundColourR = 0.0f;
const GLclampf cBackgroundColourG = 0.0f;
const GLclampf cBackgroundColourB = 0.0f;
const GLclampf cBackgroundColourA = 1.0f;

const GLclampf cClearDepth = 1.0f;

GLuint imgFaceOne;
char* imgFaceOnePath = "1.jpg";

GLuint imgFaceTwo;
char* imgFaceTwoPath = "2.jpg";

GLuint imgFaceThree;
char* imgFaceThreePath = "3.jpg";

GLuint imgFaceFour;
char* imgFaceFourPath = "4.jpg";

GLuint imgFaceFive;
char* imgFaceFivePath = "5.jpg";

GLuint imgFaceSix;
char* imgFaceSixPath = "6.jpg";

GLfloat currentRotation = 0.0f;

int rotationAxis = 0;

GLfloat rotationSpeed = 0.2f;


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	switch(rotationAxis)
	{
		case 0:
			glRotatef(currentRotation, 1.0f, 0.0f, 0.0f);
			break;
		case 1:
			glRotatef(currentRotation, 0.0f, 1.0f, 0.0f);
			break;
		case 2:
			glRotatef(currentRotation, 0.0f, 0.0f, 1.0f);
			break;
	}

	currentRotation += rotationSpeed;

	if(currentRotation >= 360.0f)
	{
		rotationAxis = rotationAxis + 1 < 3 ? rotationAxis + 1 : 0;
		currentRotation = 0.0f;
	}

	glBindTexture(GL_TEXTURE_2D, imgFaceOne);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, imgFaceTwo);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, imgFaceThree);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, imgFaceFour);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, imgFaceFive);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, imgFaceSix);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();
}

void initializeTextures()
{
	/* Define wrapping behaviour for material */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/* Define texture Filtering behaviour for material */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);


	/* Load the textures */
	imgFaceOne = ilutGLLoadImage(imgFaceOnePath);
	imgFaceTwo = ilutGLLoadImage(imgFaceTwoPath);
	imgFaceThree = ilutGLLoadImage(imgFaceThreePath);
	imgFaceFour = ilutGLLoadImage(imgFaceFourPath);
	imgFaceFive = ilutGLLoadImage(imgFaceFivePath);
	imgFaceSix = ilutGLLoadImage(imgFaceSixPath);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void initializeOpenILUT()
{
	ilInit();
	ilClearColour(255, 255, 255, 000);

	iluInit();
	ilutRenderer(ILUT_OPENGL);
}

void initializeOpenGL()
{
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);


	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glClearColor(cBackgroundColourR, cBackgroundColourG, cBackgroundColourB, cBackgroundColourA);
	glClearDepth(cClearDepth);
}

int main(int argc, char** argv)
{
	/* Initialize Glut */
	glutInit(&argc, argv);

	/* Initialize Glut's display mode to be double buffered */
	glutInitDisplayMode(GLUT_DOUBLE);

	/* Set the window size */
	glutInitWindowSize(cWindowSizeX, cWindowSizeY);

	/* Create the window and set it stitle */
	glutCreateWindow(cWindowTitle);

	initializeOpenGL();

	initializeOpenILUT();

	initializeTextures();

	glutDisplayFunc(draw);
	glutMainLoop();
}