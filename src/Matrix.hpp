/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef CMATRIX_H
#define CMATRIX_H

#include <GL/gl.h>
#include <iostream>

using namespace std;

class Matrix {
public:
	GLfloat mat[4][4];   	// this matrix is for MC
	Matrix();  				// constructor
	~Matrix(){};
	void loadIdentity();  // make identity matrix


	void matrixPreMultiply(Matrix* m);  	// mat <- m*mat
	void transpose();  						// mat <- mat'
	void multiplyVector(GLfloat* v); // mat*v
	void normalize();  // this function is to normalize MC
	void rotateMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat angle); //mat <- Rotation(rx, ry, rz, angle)
	void printMatrix(); // a function to print matrixes
};

#endif
