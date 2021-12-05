/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef HEALTHCALCULATOR_HPP_
#define HEALTHCALCULATOR_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Sphere.hpp"
class HealthCalculator {

protected:
	int KnightHealth, NoskHealth;

public:

	void reset();
	HealthCalculator();
	int getKnightHealth(); //getter funcs
	int getNoskHealth();
	int isCollision(); /*check for collision. 1 = knight . 2 = nosk. 0 = none. */
	//idea:create some boundary spheres

};

#endif /* HEALTHCALCULATOR_HPP_ */
