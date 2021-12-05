/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef SPHERE_H
#define SPHERE_H

#include <windows.h>
#include <GL/glut.h>
#include "Shape.hpp"

class Sphere: public Shape {
public:
	GLdouble radius; // radius
	GLint splices, stacks;

	GLuint textureID;
	GLUquadric *quad;
	Sphere(GLdouble);
	void draw();

	void setColor(GLfloat red, GLfloat green, GLfloat blue);
};

#endif
