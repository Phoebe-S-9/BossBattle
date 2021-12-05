/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */

#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>


using namespace std;

Matrix::Matrix() {
	loadIdentity();
}

// mat <- identity matrix
void Matrix::loadIdentity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}


// multiplication  mat <- m * mat
void Matrix::matrixPreMultiply(Matrix* m) {
	Matrix temp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLfloat sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += m->mat[i][k] * mat[k][j];
			}
			temp.mat[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = temp.mat[i][j];
		}
	}
}


// transpose  mat <- mat'
void Matrix::transpose() {
	GLint i, j;
	GLfloat temp;
	for(i=0;i<3;i++){
		for(j=i+1;j<4;j++){
			temp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = temp;
		}
	}
}

// normalize MC
void Matrix::normalize() {
	GLfloat len = sqrt(mat[0][0]*mat[0][0] + mat[1][0]*mat[1][0]+mat[2][0]*mat[2][0]);
	mat[0][0] = mat[0][0]/len;
	mat[1][0] = mat[1][0]/len;
	mat[2][0] = mat[2][0]/len;

	mat[0][2] = mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1];
	mat[1][2] = mat[2][0]*mat[0][1]-mat[0][0]*mat[2][1];
	mat[2][2] = mat[0][0]*mat[1][1]-mat[1][0]*mat[0][1];

	len = sqrt(mat[0][2]*mat[0][2] + mat[1][2]*mat[1][2]+mat[2][2]*mat[2][2]);
	mat[0][2] = mat[0][2]/len;
	mat[1][2] = mat[1][2]/len;
	mat[2][2] = mat[2][2]/len;

	mat[0][1] = mat[1][2]*mat[2][0]-mat[1][0]*mat[2][2];
	mat[1][1] = mat[2][2]*mat[0][0]-mat[2][0]*mat[0][2];
	mat[2][1] = mat[0][2]*mat[1][0]-mat[0][0]*mat[1][2];

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

// v  <- mat * v
void Matrix::multiplyVector(GLfloat* v) {
	GLfloat sum, temp[4];
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (int j = 0; j < 4; j++) {
			sum +=  mat[i][j] * v[j];
		}
		temp[i] = sum;
	}
	for (int i = 0; i < 4; i++) {
		v[i] = temp[i];
	}
}


void Matrix::printMatrix(){
	printf("Matrix:\n");
	printf("%f, %f,%f,%f\n",mat[0][0],mat[0][1],mat[0][2],mat[0][3]);
	printf("%f, %f,%f,%f\n",mat[1][0],mat[1][1],mat[1][2],mat[1][3]);
	printf("%f, %f,%f,%f\n",mat[2][0],mat[2][1],mat[2][2],mat[2][3]);
	printf("%f, %f,%f,%f\n",mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
	printf("------------------\n");
}


void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {


    GLfloat radianAngle = angle * 3.1415926/180;
    GLfloat axisVectLength = sqrt (rx * rx + ry*ry + rz*rz);
    GLfloat cosA = cos (radianAngle);
    GLfloat oneC = 1 - cosA;
    GLfloat sinA = sin (radianAngle);
    GLfloat ux = (rx) / axisVectLength;
    GLfloat uy = (ry) / axisVectLength;
    GLfloat uz = (rz) / axisVectLength;

    mat[0][0] = ux*ux*oneC + cosA;
    mat[0][1] = ux*uy*oneC - uz*sinA;
    mat[0][2] = ux*uz*oneC + uy*sinA;
    mat[0][3] = 0;

    mat[1][0] = uy*ux*oneC + uz*sinA;
    mat[1][1] = uy*uy*oneC + cosA;
    mat[1][2] = uy*uz*oneC - ux*sinA;
    mat[1][3] = 0;

    mat[2][0] = uz*ux*oneC - uy*sinA;
    mat[2][1] = uz*uy*oneC + ux*sinA;
    mat[2][2] = uz*uz*oneC + cosA;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;

}



