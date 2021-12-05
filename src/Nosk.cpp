#include "Nosk.hpp"

Nosk::Nosk() {
	reset();
}

void Nosk::reset() {

	GLfloat x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

	//head at origin

	horn1 = new Nail();
	horn1->setParentMC(&mc);
	horn1->setPos(0, 0, 0);
	horn1->translate(0., 0., 0.7);
	horn1->setColor(0.9, 0.9, 0.9);
	horn1->setScale(0.15);

	x1 = horn1->getMC().mat[0][3];
	y1 = horn1->getMC().mat[1][3];
	z1 = horn1->getMC().mat[2][3];
	horn1->rotate(x1, y1, z1, 170);

	head = new Light();
	head->setParentMC(&mc);
	head->setPos(0, 0, 0);
	head->translate(0., 0., 0.5);
	head->setColor(1, 1, 1);
	head->setScale(0.25);

	x2 = head->getMC().mat[0][3];
	y2 = head->getMC().mat[1][3];
	z2 = head->getMC().mat[2][3];

	horn2 = new Nail(); //this horn infront of head
	horn2->setParentMC(&mc);
	horn2->setPos(0, 0, 0);
	horn2->translate(0.1, 0., 0.7);
	horn2->setColor(0.8, 0.8, 0.8);
	horn2->setScale(0.15);

	x3 = horn2->getMC().mat[0][3];
	y3 = horn2->getMC().mat[1][3];
	z3 = horn2->getMC().mat[2][3];
	horn2->rotate(x3, y3, z3, 190);

	body = new Light();
	body->setParentMC(&mc);
	body->setPos(0, 0, 0);
	body->translate(-.4, 0.1, -0.6);
	body->setColor(1, 0.65, 0); //orange
	body->setScale(0.6);

	leg1 = new Nail();
	leg1->setParentMC(&mc);
	leg1->setColor(0.1, 0.1, 0.1);
	leg1->setScale(0.4);
	leg1->setPos(0, 0, 0);
	leg1->translate(0.1, 0.1, 0.1);

	x1 = leg1->getMC().mat[0][3];
	y1 = leg1->getMC().mat[1][3];
	z1 = leg1->getMC().mat[2][3];
	leg1->rotate(x1, y1, z1, 50);

	leg2 = new Nail();
	leg2->setParentMC(&mc);
	leg2->setColor(0.15, 0.15, 0.15);
	leg2->setScale(0.4);
	leg2->setPos(0, 0, 0);
	leg2->translate(0.1, 0.1, 0.1);

	x2 = leg2->getMC().mat[0][3];
	y2 = leg2->getMC().mat[1][3];
	z2 = leg2->getMC().mat[2][3];
	leg2->rotate(x2, y2, z2, 190);

	leg = new Nail(); //actual leg 3
	leg->setParentMC(&mc);
	leg->setPos(0, 0, 0);
	leg->translate(-0.2, 0.7, -0.1);
	leg->setColor(0.1, 0.1, 0.1);
	leg->setScale(0.4);

	for (int i = 0; i < 10; i++) {
		x1 = leg->getMC().mat[0][3];
		y1 = leg->getMC().mat[1][3];
		z1 = leg->getMC().mat[2][3];
		leg->rotate(x1, y1, z1, 10);
	}
	//	leg->rotate(-x1, y1, z1, 350);

	leg4 = new Nail();
	leg4->setParentMC(&mc);
	leg4->setPos(0, 0, 0);
	leg4->translate(-0.2, 0.5, -0.3);
	leg4->setColor(0.18, 0.18, 0.18);
	leg4->setScale(0.4);

	x2 = leg4->getMC().mat[0][3];
	y2 = leg4->getMC().mat[1][3];
	z2 = leg4->getMC().mat[2][3];
	leg4->rotate(x2, y2, z2, -270);
}

void Nosk::draw() {

	//body and legs
	glPushMatrix(); //legs behind body
	this->ctmMultiply();
	glScalef(s, s, s);
	leg1->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	leg->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	body->draw();
	glPopMatrix();

	glPushMatrix();	//legs front of body
	this->ctmMultiply();
	glScalef(s, s, s);
	leg2->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	leg4->draw();
	glPopMatrix();

	//head
	horn1->setPos(0, 0, 0);	//reset where they are
	head->setPos(0, 0, 0);
	horn2->setPos(0, 0, 0);

	if (flipNosk == 1) {	//flipped
		horn1->setPos(-0.10, 0, 0.20);
		horn1->translate(0.1, 0.9, 0.4);
		head->translate(0.1, 0.9, 0.4);
		horn2->translate(0.1, 0.8, 0.5);
	} else if (flipNosk == 0) { //reset
		horn1->translate(0., 0., 0.7);
		head->translate(0., 0., 0.5);
		horn2->translate(0.1, 0., 0.7);
	}

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
