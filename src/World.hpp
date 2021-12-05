/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <iostream>
#include <list>
#include <vector>
#include "Shape.hpp"

class World {

public:
	std::list<Shape*> objlist;
	World();
	~World();
	void draw(); /* draw all objects in the world */
	void reset(); /* resets all objects */

	Shape *searchById(GLint i);

};

#endif
