/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CPOINT_H
#define CPOINT_H

#include <GL/glut.h>

class Point {
 public:
	GLfloat x,y,z; //the coordinates
	Point();
	void set(GLfloat x, GLfloat y, GLfloat z);
	void set(Point p);
	void Normalize();
	Point CalcNormal(Point, Point);
	void CrossProduct(Point, Point);
	void printPoint();
};

#endif
