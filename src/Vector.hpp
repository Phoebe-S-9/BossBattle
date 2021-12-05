/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CVECTOR_H
#define CVECTOR_H

#include <GL/glut.h>
#include "Point.hpp"

class Vector {
 public:
	GLfloat x,y,z; 			// the coordinates
	Vector();               // constructor
	Vector(GLfloat dx, GLfloat dy, GLfloat dz);
	void set(GLfloat dx, GLfloat yy, GLfloat dz);
	void set(Vector& v);
	void setDiff(Point& a, Point& b);
	void flip(); 			// reverse this vector
	void normalize();		// adjust this vector to unit length
	Vector diff(Point& a, Point& b);
	Vector cross(Vector b); //return this cross b
	GLfloat dot(Vector b); 	//return this dotted with b
	void build4tuple(GLfloat v[]); //v[0]=x,v[1]=y,v[2]=z,v[3]=0 for homogeneous system
	void printVector();
};

#endif
