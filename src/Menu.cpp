/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#include <windows.h>  // for playing sound
#include <mmsystem.h> //

#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "HealthCalculator.hpp"
extern GLfloat direction, direction2;

extern GLint csType;
extern Shape* selectObj;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;

extern CullMode cullMode;
extern RenderMode renderMode;

extern GLint displayOption;
extern GLint isInfecting; //global vars
extern GLint isJumping, knightIsCollided, noskIsCollided;
extern HealthCalculator hc;
extern GLint flipNosk;
extern GLint soundOn;

void menu() {

	//GLint Shading_Menu = glutCreateMenu(shadeMenu);
	//glutAddMenuEntry("My constant shading", 2);

	GLint Animate_Menu = glutCreateMenu(animateMenu);
	glutAddMenuEntry("Start enemy movement", 1);
	glutAddMenuEntry("Knight jump", 2);
	glutAddMenuEntry("Start enemy attack", 3);
	glutAddMenuEntry("Stop animation", 4);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	//glutAddSubMenu("Shading", Shading_Menu);
	glutAddSubMenu("Animation", Animate_Menu);
	glutAddMenuEntry("Play Nosk OST", 3);
	glutAddMenuEntry("Play Nightmare OST", 4);
	glutAddMenuEntry("Stop playing sound", 5);
	glutAddMenuEntry("Quit", 2);
}

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		reset();
		break;
	case 2:
		exit(0);
		break;

	case 3: //enable sounds
		soundOn = 1;
		PlaySound((LPCSTR) "Hollow Knight OST - Nosk.wav", NULL,
		SND_FILENAME | SND_ASYNC);
		//PlaySound((LPCSTR) "test.wav", NULL, SND_FILENAME | SND_ASYNC);
		break;

	case 4: //enable sounds
		soundOn = 1;
		PlaySound(
				(LPCSTR) "Nightmare King (Hollow Knight - The Grimm Troupe).wav",
				NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 5:
		PlaySound(NULL, NULL, NULL);
		break;
	}
	glutPostRedisplay();
}

void shadeMenu(GLint option) {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable( GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);

	switch (option) {

	case 2:
		renderMode = CONSTANT;
		break;

	case 6: //unused
		renderMode = PHONE;
		break;
	}

	glutPostRedisplay();
}

void infection() {
	GLfloat FALL = -0.05;  //fall rate
	GLfloat FALLBORDER = -10;

	//translate = movment //trans down = falling //set pos = reset where they are
	myWorld.searchById(5)->translate(0, 0, FALL);
	myWorld.searchById(6)->translate(0, 0, FALL);
	myWorld.searchById(7)->translate(0, 0, FALL);

	if (myWorld.searchById(5)->getMC().mat[2][3] <= FALLBORDER) { //reset postions--like they are in world//just off screen
		myWorld.searchById(5)->setPos(-2.5, 0, 4);
		myWorld.searchById(6)->setPos(-3.5, 0, 5);
		myWorld.searchById(7)->setPos(-4.5, 0, 6);
	}

	GLfloat EP = 0.0005, BORDER = 3;

	//let nosk move too

	GLfloat currentX = myWorld.searchById(3)->getMC().mat[1][3];
	if (BORDER - EP < currentX && currentX < BORDER + EP) { //epsilon //close enough to border
		direction = -0.01;
		flipNosk = 0; 	 //at edge- turn arround
	} else if (-BORDER - EP < currentX && currentX < -BORDER + EP) {
		direction = 0.01;
		flipNosk = 1; 	 //at edge- turn arround
	} else if (direction == 0.0) { //start off
		direction = 0.01;
	}
	myWorld.searchById(3)->translate(0, direction, 0);

	glutPostRedisplay();
}

void noskMove(void) {
	GLfloat EP = 0.0005, BORDER = 3; //epsilon - check if about same //close enough to border
	GLfloat currentX = myWorld.searchById(3)->getMC().mat[1][3]; //is actauly moving on y axis

	if (BORDER - EP < currentX && currentX < BORDER + EP) {
		direction = -0.01;
		flipNosk = 0; 	 //at edge- turn arround// flip var  for drawing

	} else if (-BORDER - EP < currentX && currentX < -BORDER + EP) {
		direction = 0.01;
		flipNosk = 1; 	 //at edge- turn arround

	} else if (direction == 0.0) { //start off
		direction = 0.01;
	}

	myWorld.searchById(3)->translate(0, direction, 0);

	//infection animation
	if (isInfecting == 1) {
		//infection();
		GLfloat FALL = -0.05;  //fall rate
		GLfloat FALLBORDER = -10;

		//translate = movment //trans down = falling //set pos = reset where they are
		myWorld.searchById(5)->translate(0, 0, FALL);
		myWorld.searchById(6)->translate(0, 0, FALL);
		myWorld.searchById(7)->translate(0, 0, FALL);

		if (myWorld.searchById(5)->getMC().mat[2][3] <= FALLBORDER) { //reset postions--like they are in world//just off screen
			myWorld.searchById(5)->setPos(-2.5, 0, 4);
			myWorld.searchById(6)->setPos(-3.5, 0, 5);
			myWorld.searchById(7)->setPos(-4.5, 0, 6);
		}
	}
	glutPostRedisplay();
}

void knightJumpUp(void) {
	GLfloat EP = 0.0005, BORDER = 3; //epsilon//knight id = 1
	GLfloat currentZ = myWorld.searchById(1)->getMC().mat[2][3];

	direction2 = 0.01; //start

	if (BORDER - EP < currentZ && currentZ < BORDER + EP) { //close enough to border// moving object z postion
		glutIdleFunc(knightJumpDown);
	}

	myWorld.searchById(1)->translate(0, 0, direction2); //knight move
	myWorld.searchById(2)->translate(0, 0, direction2); //nail move

	//let nosk move too
	//noskMove();
	//GLfloat EP = 0.0005, BORDER = 3; //epsilon - check if about same //close enough to border
	GLfloat currentX = myWorld.searchById(3)->getMC().mat[1][3]; //is actauly moving on y axis

	if (BORDER - EP < currentX && currentX < BORDER + EP) {
		direction = -0.01;
		flipNosk = 0; 	 //at edge- turn arround// flip var  for drawing

	} else if (-BORDER - EP < currentX && currentX < -BORDER + EP) {
		direction = 0.01;
		flipNosk = 1; 	 //at edge- turn arround

	} else if (direction == 0.0) { //start off
		direction = 0.01;
	}

	myWorld.searchById(3)->translate(0, direction, 0);

	//infection animation
	if (isInfecting == 1) {
		//infection();
		GLfloat FALL = -0.05;  //fall rate
		GLfloat FALLBORDER = -10;

		//translate = movment //trans down = falling //set pos = reset where they are
		myWorld.searchById(5)->translate(0, 0, FALL);
		myWorld.searchById(6)->translate(0, 0, FALL);
		myWorld.searchById(7)->translate(0, 0, FALL);

		if (myWorld.searchById(5)->getMC().mat[2][3] <= FALLBORDER) { //reset postions--like they are in world//just off screen
			myWorld.searchById(5)->setPos(-2.5, 0, 4);
			myWorld.searchById(6)->setPos(-3.5, 0, 5);
			myWorld.searchById(7)->setPos(-4.5, 0, 6);
		}

	}
	glutPostRedisplay();
}

void knightJumpDown(void) {
	GLfloat EP = 0.0005, BORDER = 3; //epsilon
	GLfloat currentZ = myWorld.searchById(1)->getMC().mat[2][3]; //knight id = 1

	direction2 = -0.01; //start
	if (0 - EP < currentZ && currentZ < 0 + EP) { //after 1 jump go to nosks aniamtion instead
		glutIdleFunc(noskMove);
	}

	myWorld.searchById(1)->translate(0, 0, direction2); //knight move
	myWorld.searchById(2)->translate(0, 0, direction2); //nail move

	//let nosk move too
	//noskMove();
	//GLfloat EP = 0.0005, BORDER = 3; //epsilon - check if about same //close enough to border
	GLfloat currentX = myWorld.searchById(3)->getMC().mat[1][3]; //is actauly moving on y axis

	if (BORDER - EP < currentX && currentX < BORDER + EP) {
		direction = -0.01;
		flipNosk = 0; 	 //at edge- turn arround// flip var  for drawing

	} else if (-BORDER - EP < currentX && currentX < -BORDER + EP) {
		direction = 0.01;
		flipNosk = 1; 	 //at edge- turn arround

	} else if (direction == 0.0) { //start off
		direction = 0.01;
	}

	myWorld.searchById(3)->translate(0, direction, 0);

	//infection animation
	if (isInfecting == 1) {
		//infection();
		GLfloat FALL = -0.05;  //fall rate
		GLfloat FALLBORDER = -10;

		//translate = movment //trans down = falling //set pos = reset where they are
		myWorld.searchById(5)->translate(0, 0, FALL);
		myWorld.searchById(6)->translate(0, 0, FALL);
		myWorld.searchById(7)->translate(0, 0, FALL);

		if (myWorld.searchById(5)->getMC().mat[2][3] <= FALLBORDER) { //reset postions--like they are in world//just off screen
			myWorld.searchById(5)->setPos(-2.5, 0, 4);
			myWorld.searchById(6)->setPos(-3.5, 0, 5);
			myWorld.searchById(7)->setPos(-4.5, 0, 6);
		}

	}
	glutPostRedisplay();
}

void animateMenu(GLint option) {

	switch (option) {
	case 1: //nosk move
		displayOption = 0;
		glutIdleFunc(noskMove);
		break;

	case 2: //knight jump --only 1jump
		displayOption = 0;
		glutIdleFunc(knightJumpUp); //calls jump up,calls jump down, calls idle func nosk
		break;

	case 3: //infection
		displayOption = 0;
		isInfecting = 1; //global
		glutIdleFunc(infection);
		break;

	case 4: //stop
		isInfecting = 0; //turn off infection
		glutIdleFunc(NULL);
		break;
	}

	glutPostRedisplay();
}

void reset() { //reset all  global vars

	direction = 0.0;
	direction2 = 0.0;

	csType = 1;
	selectObj = NULL;
	transType = 4, xbegin = 0;
	myWorld.~World(); //destroy old one first
	myWorld.reset();
	myCamera.reset();
	myLight.reset();

	cullMode = BACKFACE;
	renderMode = CONSTANT;

	displayOption = 0;

	isInfecting = 0;
	isJumping = 0; //0 for no. 1 to make 1 jump
	knightIsCollided = 0;
	noskIsCollided = 0;
	flipNosk = 1;
	hc.reset();
	soundOn = 0;

	//PlaySound(NULL, NULL, NULL);
	glutIdleFunc(NULL);

}
