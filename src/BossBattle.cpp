/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */


#include <GL/glew.h>
#include "GL/glaux.h"

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "HealthCalculator.hpp"

GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0, xbegin = 0, csType = 1, /* coordinate system type: 1 for MCS, 2 for WCS, 3 for VCS */
transType = 4; /* depends on csType  */

CullMode cullMode = BACKFACE; // GLCULLDEPTHBUFFER-no;  /* culling option */
RenderMode renderMode = CONSTANT; /* shade option  */

World myWorld;
Camera myCamera;
Light myLight;
Shape *selectObj = NULL;  // pointer to select object

HealthCalculator hc;  //global object--can call

GLint displayOption = 0;   //now 0: world, 1 lose, 2 win

GLint isInfecting = 0; //0 for no. 1 to make ball attack
GLint isJumping = 0; //0 for no. 1 to make 1 jump
GLint knightIsCollided = 0, noskIsCollided = 0; //IsCollided for nosk and knight so not double hit

GLint flipNosk = 1; //head translate //1: going right. 2: going left
GLfloat direction = 0.0, direction2 = 0.0; //global for animaiton //nosk direcion, jump direction
GLint soundOn = 0; //off ///use for nail swing? cant find sound effect..


void init(void) {
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearColor(0.0, 0.2, 0.3, 1.0); //background color
	selectObj = myWorld.searchById(1);

}

void drawWCSAxes() { // debug //red = x, green = y. z = blue
	;
//	glBegin(GL_LINES);
//	//x-axis red
//	glColor3f(1.0, 0.0, 0.0);
//	glVertex3f(-2, 0, 0);
//	glVertex3f(4, 0, 0);
//	//y-axis green
//	glColor3f(0.0, 1.0, 0.0);
//	glVertex3f(0, -2, 0);
//	glVertex3f(0, 4, 0);
//	//z-axis blue
//	glColor3f(0.0, 0.0, 1.0);
//	glVertex3f(0, 0, -2);
//	glVertex3f(0, 0, 4);
//	glEnd();
}

void message(char str[], GLint x, GLint y) { //print a message to screen
	glRasterPos2i(x, y);
	int i = 0;
	while (str[i]) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		i++;
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (displayOption) {

	case 0: //show game
		myCamera.setProjectionMatrix();
		drawWCSAxes();
		myWorld.draw();
		myLight.draw();
		break;

	case 1: //dispaly  lose too
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		message("LOSE", 4, 1);

		myCamera.setProjectionMatrix();
		drawWCSAxes();
		myWorld.draw();
		myLight.draw();
		animateMenu(4); //stop moving
		break;

	case 2: //dispaly  win too
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		message("WIN", 4, 1);

		myCamera.setProjectionMatrix();
		drawWCSAxes();
		myWorld.draw();
		myLight.draw();
		animateMenu(4); //stop
		break;
	}

	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

/*
 * knight movment  ( id 1). move nail( id 2) at same rate
 * wasd to move. space to jump
 */

void movement(GLubyte key, GLint x, GLint y) {
	GLfloat moveDist = 1;

	if (displayOption == 0) { //only  moving during game

		switch (key) { //id 1 for knight

		case 'w': //tranlaste "forward"
			myWorld.searchById(1)->translate(-moveDist, 0, 0); //move knihgt (1)
			myWorld.searchById(2)->translate(-moveDist, 0, 0); //move nail(2) at same rate
			animateMenu(1); //let nosk move
			glutPostRedisplay();
			break;

		case 'a': //move left.
			myWorld.searchById(1)->translate(0, -moveDist, 0);
			myWorld.searchById(2)->translate(0, -moveDist, 0);
			animateMenu(1);
			glutPostRedisplay();
			break;

		case 's': //tranlaste backward
			myWorld.searchById(1)->translate(moveDist, 0, 0);
			myWorld.searchById(2)->translate(moveDist, 0, 0);
			animateMenu(1);
			glutPostRedisplay();
			break;

		case 'd': //move right
			myWorld.searchById(1)->translate(0, moveDist, 0);
			myWorld.searchById(2)->translate(0, moveDist, 0);
			animateMenu(1);
			glutPostRedisplay();
			break;

		case ' ': //jump
			isJumping = 1;
			animateMenu(2);
			isJumping = 0;
			break;

		default:
			animateMenu(1); //nosk moving
			glutPostRedisplay();
			break;
		}

	};
	glFlush();
}

/*
 * left clicK:swing nail
 * right click: menu
 */
void mouseActionFcn(int button, int state, int xMouse, int yMouse) {

	if (displayOption == 0) { //only  moving during game
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { //swing nail (id = 2)

			myWorld.searchById(2)->rotate(
					myWorld.searchById(2)->getMC().mat[0][3],
					myWorld.searchById(2)->getMC().mat[1][3],
					myWorld.searchById(2)->getMC().mat[2][3], 45); //roate xyz angle

			//myWorld.searchById(2)->translate(0, 0, -0.5);
			glutPostRedisplay();
		}

		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {	//swing back up
			myWorld.searchById(2)->rotate(
					myWorld.searchById(2)->getMC().mat[0][3],
					myWorld.searchById(2)->getMC().mat[1][3],
					myWorld.searchById(2)->getMC().mat[2][3], -45);

			//myWorld.searchById(2)->translate(0, 0, 0.5);
			glutPostRedisplay();

		}
	}

	//camera
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isInMove = 1;
		xbegin = xMouse;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isInMove = 0;
	}

}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {//camera debug -light will exit it
	if (isInMove) {
		if (csType == 3) {
			;	//VCSTransform(xMouse);
		}
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Boss Battle: by Phoebe S.");

	menu();
	init();

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutMouseFunc(mouseActionFcn);
	glutKeyboardFunc(movement);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

