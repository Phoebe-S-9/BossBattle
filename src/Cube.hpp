/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

#include "Camera.hpp"
#include "Light.hpp"

class Cube: public Shape {

protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceNormal[6][3];

public:
	Cube();
	void draw();
	void drawFace(int);
	bool isFrontface(int faceindex, Camera camera);
	void setColor(GLfloat red, GLfloat green, GLfloat blue);

};

#endif
