/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */

#include "Nail.hpp"

extern Camera myCamera;
extern Light myLight;

extern CullMode cullMode;
extern RenderMode renderMode;

Nail::Nail() {

	vertex[0][0] = -0.5;
	vertex[0][1] = -0.5;
	vertex[0][2] = 0;
	vertex[1][0] = 0.5;
	vertex[1][1] = -0.5;
	vertex[1][2] = 0;
	vertex[2][0] = 0.5;
	vertex[2][1] = 0.5;
	vertex[2][2] = 0;
	vertex[3][0] = -0.5;
	vertex[3][1] = 0.5;
	vertex[3][2] = 0;
	vertex[4][0] = 0;
	vertex[4][1] = 0.0;
	vertex[4][2] = 3;

	face[0][0] = 0;
	face[0][1] = 1;
	face[0][2] = 4;
	face[1][0] = 1;
	face[1][1] = 2;
	face[1][2] = 4;
	face[2][0] = 2;
	face[2][1] = 3;
	face[2][2] = 4;
	face[3][0] = 3;
	face[3][1] = 0;
	face[3][2] = 4;

	for (int i = 0; i < 4; i++) {
		Vector V1 = Vector(vertex[face[i][1]][0] - vertex[face[i][0]][0],
				vertex[face[i][1]][1] - vertex[face[i][0]][1],
				vertex[face[i][1]][2] - vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0] - vertex[face[i][1]][0],
				vertex[face[i][2]][1] - vertex[face[i][1]][1],
				vertex[face[i][2]][2] - vertex[face[i][1]][2]);
		faceNormal[i] = V1.cross(V2);
		faceNormal[i].normalize();
	}

	r = .0;
	g = .1;
	b = 0.1;

}

void Nail::drawFace(GLint i) {

	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex3fv(vertex[face[i][0]]);
	glVertex3fv(vertex[face[i][1]]);
	glVertex3fv(vertex[face[i][2]]);
	glEnd();

}

void Nail::draw() {

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	for (int i = 0; i < 4; i++) {
		if (cullMode == BACKFACE) {
			if (isFrontface(i, myCamera)) {
				drawFace(i);
			}
		} else {
			drawFace(i);
		}
	}
	glPopMatrix();
}

bool Nail::isFrontface(int faceindex, Camera camera) {
	GLfloat v[4];
	v[0] = faceNormal[faceindex].x;
	v[1] = faceNormal[faceindex].y;
	v[2] = faceNormal[faceindex].z;
	v[3] = 0.0;
	mc.multiplyVector(v);
	if (pmc != NULL) {
		pmc->multiplyVector(v);
		return (pmc->mat[0][3] - camera.eye.x) * v[0]
				+ (pmc->mat[1][3] - camera.eye.y) * v[1]
				+ (pmc->mat[2][3] - camera.eye.z) * v[2] < 0;
	} else {
		return (mc.mat[0][3] - camera.eye.x) * v[0]
				+ (mc.mat[1][3] - camera.eye.y) * v[1]
				+ (mc.mat[2][3] - camera.eye.z) * v[2] < 0;
	}
}

void Nail::setColor(GLfloat red, GLfloat green, GLfloat blue) {
	r = red;
	g = green;
	b = blue;
}
