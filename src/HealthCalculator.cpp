#include "HealthCalculator.hpp"
#include "World.hpp"
//#include "stdio.h"

extern GLint knightIsCollided, noskIsCollided; //global vars
extern World myWorld;
extern GLint isInfecting;

HealthCalculator::HealthCalculator() { //initial
	reset();
}

void HealthCalculator::reset() {
	KnightHealth = 3;
	NoskHealth = 3;
}

int HealthCalculator::getKnightHealth() {
	return KnightHealth;
}
int HealthCalculator::getNoskHealth() {
	return NoskHealth;
}

int HealthCalculator::isCollision() {
	GLfloat x1 = myWorld.searchById(1)->getMC().mat[0][3], y1 =
			myWorld.searchById(1)->getMC().mat[1][3], z1 =
			myWorld.searchById(1)->getMC().mat[2][3];  //knight

	GLfloat x2 = myWorld.searchById(2)->getMC().mat[0][3], y2 =
			myWorld.searchById(2)->getMC().mat[1][3], z2 =
			myWorld.searchById(2)->getMC().mat[2][3]; //nail

	GLfloat x3 = myWorld.searchById(3)->getMC().mat[0][3], y3 =
			myWorld.searchById(3)->getMC().mat[1][3], z3 =
			myWorld.searchById(3)->getMC().mat[2][3]; //nosk

	GLfloat x4 = myWorld.searchById(5)->getMC().mat[0][3], y4 =
			myWorld.searchById(5)->getMC().mat[1][3], z4 =
			myWorld.searchById(5)->getMC().mat[2][3]; //infection //first ball willl rep them all

	GLfloat r1 = 0.5, r2 = 0.7, r3 = 0.5, r4 = 0.1; //make up radius for knight, nail, nosk,infection

	GLint itCollides = 0, itCollides2 = 0; //false 0 true 1

	float x, y, centerDistanceSq; // squared distance
	float radius, radiusSq;

	//check kngiht and nosk
	x = x1 - x3;
	y = y1 - y3;
	centerDistanceSq = x * x + y * y;
	radius = r1 + r3;
	radiusSq = radius * radius;
	itCollides = (centerDistanceSq <= radiusSq);

	if (isInfecting == 1) {
		//check  knight and first ball
		x = x1 - x4;
		y = y1 - y4;
		centerDistanceSq = x * x + y * y;
		radius = r1 + r4;
		radiusSq = radius * radius;

		itCollides2 = (centerDistanceSq <= radiusSq);
		//itCollides2 = 0; //debug
	}

	//hit by ball or nosk
	if ((itCollides == 1 || itCollides2 == 1) && knightIsCollided == 0) { //hit and wasnt hit before ->lose health
	//	if (itCollides2 == 1) printf("ball"); //debug
	//printf("\n%sHIT KNIGHT\n", ""); //debug
		KnightHealth -= 1;
		knightIsCollided = 1; //currently  begin hit
		return 1;

	} else if (itCollides == 0 && itCollides2 == 0 && knightIsCollided == 1) { //currlty begin hit = true but not overlaping. can reset
		knightIsCollided = 0;
	}

	if (itCollides == 1 || itCollides2 == 1) //knioght collided but no effect
		return 0;

	//check nail and nosk
	x = x2 - x3;
	y = y2 - y3;
	centerDistanceSq = x * x + y * y;
	radius = r2 + r3;
	radiusSq = radius * radius;

	itCollides = (centerDistanceSq <= radiusSq);

	if (itCollides == 1 && noskIsCollided == 0) { //can also check mouse button is donw(have isswinging = true
	//printf("\n%sHIT NOSK!!\n", ""); //debug
		NoskHealth -= 1;
		noskIsCollided = 1;
		return 2;

	} else if (itCollides == 0 && noskIsCollided == 1) {
		noskIsCollided = 0;
	}
	if (itCollides == 1) //nosk collided but no effect
		return 0;

	return 0;

}

