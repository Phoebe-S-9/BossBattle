/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CKNIGHT_H
#define CKNIGHT_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Light.hpp"

#include "Cube.hpp"
#include "Nail.hpp" //dif size pyridmd

class Knight: public Shape { //inheirt sahpe
protected:
	//instance vars
	Cube * body;
	Nail * leg, leg1, *leg2;
	//Pyramid * arm1, *arm2;
	Nail *horn1, *horn2;
	// Sphere *eye1, *eye2;
	Light *head;

public:
	Knight();
	void draw();
	void reset();

};

#endif

