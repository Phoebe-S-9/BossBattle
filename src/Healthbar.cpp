#include "Healthbar.hpp"

Healthbar::Healthbar() {  //set insatnce vars
	reset();
}

void Healthbar::reset() {
	GLfloat rad1 = 0.3, rad2 = 1; //radius
	GLfloat t1x = 0.3, t1y = 0.3, t1z = 0.5; //translate eye

	//create shape, set parent, set position, translate, color
	eye1 = new Sphere(rad1);
	eye1->setParentMC(&mc);
	eye1->setPos(0, 0, 0);
	eye1->translate(t1x, -t1y, t1z);
	eye1->setColor(0, 0, 0); //black

	eye2 = new Sphere(rad1);
	eye2->setParentMC(&mc);
	eye2->setPos(0, 0, 0);
	eye2->translate(-t1x, t1y, t1z);
	eye2->setColor(0, 0, 0);

	head = new Sphere(rad2);
	head->setParentMC(&mc);
	head->setPos(0, 0, 0); //head at origin
	head->setColor(1, 1, 1); //white- initially

}

void Healthbar::draw() {

	//draw head first (at back)
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	head->setColor(r, g, b);  //only head changes colour
	head->draw();
	glPopMatrix();

	//draw eyes
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	eye1->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	eye2->draw();
	glPopMatrix();
}

