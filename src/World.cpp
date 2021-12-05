#include "World.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"

#include "Knight.hpp"
#include "Nosk.hpp"
#include "Nail.hpp"
#include "Healthbar.hpp"

#include "HealthCalculator.hpp"
#include "stdio.h"
using namespace std;

extern GLint isInfecting, displayOption;
extern HealthCalculator hc;
extern World myWorld;

GLint numPops = 0; //global - track health pops
World::World() {
	reset();
}

void World::reset() {

	//ids:
	//knight  = 1 nail = 2 nosk  = 3
	//soulbar = 4
	//infection balls = 5-7 -starts off active but off screen
	//health bars =  8-11 when starting. else will be removed
	//11 items to start- with 3 off screen

	Shape *obj = NULL;
	int idNum = 0;

	idNum += 1;
	obj = new Nail();	//change push order for drawing
	obj->setId(2);
	obj->translate(2.5, 0, 0);
	obj->scaleChange(-0.5);
	obj->rotate(obj->getMC().mat[0][3], obj->getMC().mat[1][3],
			obj->getMC().mat[2][3], 45);
	objlist.push_back(obj);

	idNum += 1;
	obj = new Knight();
	obj->setId(1);
	obj->translate(2.5, 0, 0);
	objlist.push_back(obj);

	idNum += 1;
	obj = new Nosk();
	obj->setId(idNum);
	objlist.push_back(obj);

	//soul bar	//change color based on nosk health
	idNum += 1;
	obj = new Healthbar();
	obj->setId(idNum);
	obj->translate(2, -0.8, 5);
	obj->setColor(0, 0, 1); //bklue to start
	obj->scaleChange(-0.5);
	objlist.push_back(obj);

	//infection //orang ball of light //start off screen either way
	//when animate- drop them into screen. after animaion put them back at top
	idNum += 1;
	obj = new Light();
	obj->setId(idNum);
	obj->setPos(2, 2, 2);
	obj->translate(-2.5, 0, 4.5);
	obj->setColor(1, 0.65, 0);	//organge
	obj->scaleChange(-0.5);
	objlist.push_back(obj);

	idNum += 1;
	obj = new Light();
	obj->setId(idNum);
	obj->setPos(2, 2, 2);
	obj->translate(-3.5, 0, 4);
	obj->setColor(1, 0.65, 0);
	obj->scaleChange(-0.5);
	objlist.push_back(obj);

	idNum += 1;
	obj = new Light();
	obj->setId(idNum);
	obj->setPos(2, 2, 2);
	obj->translate(-4.5, 0, 4);
	obj->setColor(1, 0.65, 0);
	obj->scaleChange(-0.5);
	objlist.push_back(obj);

	//draw 3 health bars //intilaly at full health
	GLfloat healthPosX = 0.5, healthPosY = -1., healthPosZ = 4.1;

	idNum += 1;
	obj = new Healthbar();
	obj->setId(idNum);
	obj->translate(healthPosX, healthPosY, healthPosZ);
	obj->setColor(1, 1, 1);
	obj->scaleChange(-0.5);
	objlist.push_back(obj);

	idNum += 1;
	obj = new Healthbar();
	obj->setId(idNum);
	obj->translate(healthPosX - 2, healthPosY, healthPosZ - 0.9);
	obj->setColor(1, 1, 1);
	obj->scaleChange(-0.45);	//more in dist . so shrink less
	objlist.push_back(obj);

	idNum += 1;
	obj = new Healthbar();
	obj->setId(idNum);
	obj->translate(healthPosX - 4, healthPosY + 0.4, healthPosZ - 1.8);
	obj->setColor(1, 1, 1);
	obj->scaleChange(-0.45);
	objlist.push_back(obj);

	numPops = 0;	//for drawing health bars
}

World::~World() {
	Shape *obj;
	while (!objlist.empty()) {
		obj = objlist.front();
		objlist.pop_front();
		free(obj);
	}

}

void World::draw() {

	std::list<Shape*>::iterator it; //draw what in the world
	for (it = objlist.begin(); it != objlist.end(); ++it) {
		(*it)->draw();
	}

	//calc which health bars to draw
	//depending on health - how much to draw- if health = 0 //dispaly lose text to screen in main
	GLint KnightHealth = hc.getKnightHealth(), NoskHealth = hc.getNoskHealth(),
			isCol = hc.isCollision();//calca once at begine instead of multi times

	if (isCol == 1) {	//knight hit

		numPops++;
		if (numPops <= 3) {
			objlist.pop_back();	//rid a health bar-- at end of list
		}

		if (KnightHealth == 0) {	//dispaly text in main
			displayOption = 1; //lose screen
		}

	} else if (isCol == 2) {		//nosk hit
		//depding on amoutn of health left soul bar (id 4) colour = blue(3),green,yellow,red(0)

		if (NoskHealth == 2) {
			searchById(4)->setColor(0, 1, 1);
		} else if (NoskHealth == 1) {
			searchById(4)->setColor(1, 0, 1);
		} else if (NoskHealth == 0) {
			searchById(4)->setColor(1, 0, 0); //red
			displayOption = 2; //dipaly win screen
		}
	}

}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it != objlist.end(); ++it) {
		if ((*it)->getId() == i)
			return *it;
	}
	return NULL;
}

