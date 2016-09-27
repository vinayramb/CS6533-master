#include "glsupport.h"
#include <freeglut\freeglut.h>

GLuint program;

GLuint vertPositionVBO;
GLuint vertTexCoordVBO;

GLuint emojiTexture;
GLuint faciltyTexture;

GLuint timeUniform;
GLuint positionUniform;
GLuint colourUniform;

GLuint positionAttribute;
GLuint texCoordAttribute;

float textureOffset = 0.0;
float colourOffset = 0.0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glUniform1f(timeUniform, textureOffset);
	glUniform1f(colourUniform, colourOffset);

	glBindBuffer(GL_ARRAY_BUFFER, vertPositionVBO);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);
	glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, emojiTexture);
	glUniform2f(positionUniform, 0.0, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, faciltyTexture);
	glUniform2f(positionUniform, 0.0, -0.5);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glDisableVertexAttribArray(positionAttribute);
	glDisableVertexAttribArray(texCoordAttribute);

    glutSwapBuffers();
}

void init() {
	program = glCreateProgram();
	readAndCompileShader(program, "vertex.glsl", "fragment.glsl");

	glUseProgram(program);
	
	timeUniform = glGetUniformLocation(program, "time");
	positionUniform = glGetUniformLocation(program, "modelPosition");
	colourUniform = glGetUniformLocation(program, "anger");

	positionAttribute = glGetAttribLocation(program, "position");
	texCoordAttribute = glGetAttribLocation(program, "texCoord");

	glGenBuffers(1, &vertPositionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertPositionVBO);
	GLfloat sqVerts[12] = {
		-0.5f,-0.5f,
		0.5f,0.5f,
		0.5f,-0.5f,

		-0.5f,-0.5f,
		-0.5f,0.5f,
		0.5f,0.5
	};
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), sqVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &vertTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);

	GLfloat sqTexCoords[12] = {
		0.0f,1.0f,
		1.0f,0.0f,
		1.0f,1.0f,

		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), sqTexCoords, GL_STATIC_DRAW);
	
	emojiTexture = loadGLTexture("emoji.png");
	faciltyTexture = loadGLTexture("facility.png");
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		textureOffset += 0.02;
		break;
	case 's':
		textureOffset -= 0.02;
		break;
	case '+':
		colourOffset += 0.02;
		break;
	case '-':
		colourOffset -= 0.02;
		break;
	}
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CS-6533: Assignment 1 (Vinay)");

    glewInit();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
	glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
    return 0;
}