/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#include "Cube.hpp"
#include "Camera.hpp"
#include <stdio.h>

extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;

Cube::Cube() {
	vertex[0][0] = -1;
	vertex[0][1] = -1;
	vertex[0][2] = -1;
	vertex[1][0] = -1;
	vertex[1][1] = 1;
	vertex[1][2] = -1;
	vertex[2][0] = 1;
	vertex[2][1] = 1;
	vertex[2][2] = -1;
	vertex[3][0] = 1;
	vertex[3][1] = -1;
	vertex[3][2] = -1;
	vertex[4][0] = -1;
	vertex[4][1] = -1;
	vertex[4][2] = 1;
	vertex[5][0] = -1;
	vertex[5][1] = 1;
	vertex[5][2] = 1;
	vertex[6][0] = 1;
	vertex[6][1] = 1;
	vertex[6][2] = 1;
	vertex[7][0] = 1;
	vertex[7][1] = -1;
	vertex[7][2] = 1;

	face[0][0] = 0;
	face[0][1] = 1;
	face[0][2] = 2;
	face[0][3] = 3;
	face[1][0] = 7;
	face[1][1] = 6;
	face[1][2] = 5;
	face[1][3] = 4;
	face[2][0] = 0;
	face[2][1] = 4;
	face[2][2] = 5;
	face[2][3] = 1;
	face[3][0] = 2;
	face[3][1] = 1;
	face[3][2] = 5;
	face[3][3] = 6;
	face[4][0] = 3;
	face[4][1] = 2;
	face[4][2] = 6;
	face[4][3] = 7;
	face[5][0] = 0;
	face[5][1] = 3;
	face[5][2] = 7;
	face[5][3] = 4;

	faceNormal[0][0] = 0.0, faceNormal[0][1] = 0.0, faceNormal[0][2] = -1.0, faceNormal[1][0] =
			0.0, faceNormal[1][1] = 0.0, faceNormal[1][2] = 1.0;
	faceNormal[2][0] = -1.0, faceNormal[2][1] = 0.0, faceNormal[2][2] = 0.0;
	faceNormal[3][0] = 0.0, faceNormal[3][1] = 1.0, faceNormal[3][2] = 0.0;
	faceNormal[4][0] = 1.0, faceNormal[4][1] = 0.0, faceNormal[4][2] = 0.0;
	faceNormal[5][0] = 0.0, faceNormal[5][1] = -1.0, faceNormal[5][2] = 0.0;

	r = 1.0; //defualt red cube
	g = 0.0;
	b = 0.0;

}

void Cube::drawFace(int i) {
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex3fv(vertex[face[i][0]]);
	glVertex3fv(vertex[face[i][1]]);
	glVertex3fv(vertex[face[i][2]]);
	glVertex3fv(vertex[face[i][3]]);
	glEnd();
}

void Cube::draw() {

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	glColor3f(r, g, b);
	for (int i = 0; i < 6; i++) {
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

bool Cube::isFrontface(int faceindex, Camera camera) {
	GLfloat v[4];
	v[0] = faceNormal[faceindex][0];
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
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

void Cube::setColor(GLfloat red, GLfloat green, GLfloat blue) {
	r = red;
	g = green;
	b = blue;
}
