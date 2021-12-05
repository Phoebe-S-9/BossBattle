/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */

#ifndef NAIL_HPP_
#define NAIL_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Nail: public Shape {
protected:
	GLfloat vertex[5][3];
	GLint face[4][4];
	Vector faceNormal[4];


public:
	Nail();
	void draw(); //like prymid but dif size
	bool isFrontface(int faceindex, Camera camera);
	void setColor(GLfloat red, GLfloat green, GLfloat blue);
private:
	void drawFace(GLint i);
};

#endif  /* NAIL_HPP_ */


