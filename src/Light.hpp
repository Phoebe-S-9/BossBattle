/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/glut.h>
#include "Shape.hpp"

class Light: public Shape {
public:
	GLfloat I, Rd; /* point light intensity and reflection diffusion */
	GLfloat size; /* radius of sphere to represent the size of light for rendering */
	GLboolean on;

	Light();
	void reset();
	void draw();


	void setScale(GLfloat s); //new //override from set size of shpae
};
#endif /* LIGHT_HPP_ */
