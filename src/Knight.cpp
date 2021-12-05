#include "Knight.hpp"
//#include "stdio.h"

Knight::Knight() {
	reset();
}

void Knight::reset() {
	GLfloat x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4; //dont need them all. could jsut be x,y,z

	//iniiaize type. partent. start psotions, color. size
	//body at origin
	body = new Cube();
	body->setParentMC(&mc);
	body->setPos(0, 0, 0);
	body->setColor(0.7, 0.8, 0.9); //body->setColor(1, 1, 1);//fake shading
	body->setScale(0.25);

	leg = new Nail();
	leg->setParentMC(&mc);
	leg->setPos(0, 0, 0);  //set then trans
	leg->translate(0.1, 0.1, 0.1);
	leg->setColor(0.9, 0.9, 0.9);
	leg->setScale(0.25);

	x1 = leg->getMC().mat[0][3];
	y1 = leg->getMC().mat[1][3];
	z1 = leg->getMC().mat[2][3];
	leg->rotate(x1, y1, z1, 170);

	leg2 = new Nail();
	leg2->setParentMC(&mc);
	leg2->setPos(0, 0, 0);
	leg2->translate(0.1, 0.1, 0.1);
	leg2->setColor(0.8, 0.8, 0.8);
	leg2->setScale(0.25);

	x2 = leg2->getMC().mat[0][3];
	y2 = leg2->getMC().mat[1][3];
	z2 = leg2->getMC().mat[2][3];
	leg2->rotate(x1, y1, z1, 190);

	horn1 = new Nail();
	horn1->setParentMC(&mc);
	horn1->setPos(0, 0, 0);
	horn1->translate(0., 0., 0.7);
	horn1->setColor(0.9, 0.9, 0.9);
	horn1->setScale(0.15);

	x3 = horn1->getMC().mat[0][3];
	y3 = horn1->getMC().mat[1][3];
	z3 = horn1->getMC().mat[2][3];
	horn1->rotate(x3, y3, z3, 200);

	head = new Light();
	head->setParentMC(&mc);
	head->setPos(0, 0, 0);
	head->translate(0., 0., 0.5);
	head->setColor(1, 1, 1);
	head->setScale(0.25);

	horn2 = new Nail(); //this horn infront of head
	horn2->setParentMC(&mc);
	horn2->setPos(0, 0, 0);
	horn2->translate(0.1, 0., 0.7);
	horn2->setColor(0.8, 0.8, 0.8);
	horn2->setScale(0.15);

	x4 = horn2->getMC().mat[0][3];
	y4 = horn2->getMC().mat[1][3];
	z4 = horn2->getMC().mat[2][3];
	horn2->rotate(x4, y4, z4, 160);

}

void Knight::draw() {

	//draw legs and body
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	leg->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	leg2->draw();
	glPopMatrix();

	glPushMatrix(); //draw body on top of legs
	this->ctmMultiply();
	glScalef(s, s, s);
	body->draw();
	glPopMatrix();

	//draw horns and head
	glPushMatrix(); //draw horn behind head
	this->ctmMultiply();
	glScalef(s, s, s);
	horn1->draw();
	glPopMatrix();

	glPushMatrix(); //draw ontop of body
	this->ctmMultiply();
	glScalef(s, s, s);
	head->draw();
	glPopMatrix();

	glPushMatrix(); //draw ontop of head
	this->ctmMultiply();
	glScalef(s, s, s);
	horn2->draw();
	glPopMatrix();

}

