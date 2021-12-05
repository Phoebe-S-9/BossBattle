#include "Sphere.hpp"

extern RenderMode renderMode;

Sphere::Sphere(GLdouble size) {
	radius = size;
	splices = 50;
	stacks = 50;
	textureID = 0;

	quad = gluNewQuadric();
}

void Sphere::draw() {
	glPushMatrix();
	ctmMultiply();

	quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricNormals(quad, GLU_SMOOTH);
	glShadeModel(GL_FLAT);

	glColor3f(r, g, b);

	gluSphere(quad, radius, splices, stacks);

	glPopMatrix();
}

void Sphere::setColor(GLfloat red, GLfloat green, GLfloat blue) {
	r = red;
	g = green;
	b = blue;
}

