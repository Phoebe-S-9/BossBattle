/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CHEALTHBAR_H
#define CHEALTHBAR_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Sphere.hpp"

class Healthbar: public Shape { //inheirt sahpe
protected:
	//instance vars
	Sphere *eye1, *eye2, *head;

public:
	Healthbar(); //soul bar will be same
	void draw(); /* drawing  health bar: head (white) and 2 eyes(black) at top left */
	void reset();
};

#endif
