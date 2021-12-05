/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CNOSK_H
#define CNOSK_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "Nail.hpp"


extern GLint flipNosk;

/*
 *nosK:
 *
 *body: orange sphere.
 *legs: 4 long legs.
 *head:white cube.  2 arcs (horns)
 */
class Nosk: public Shape { //inheirt sahpe
protected:
	//instance vars
	Light *body;
	Nail *spike1, *spike2;
	//Pyramid* tail;
	Nail * leg1, *leg2, *leg4, *leg; // *leg3
	//Nail * arm1, *arm2;
	//Sphere *eye1, *eye2;
	Nail *horn1, *horn2;
	Light *head;

public:
	Nosk();
	void draw();
	void reset();

};

#endif

