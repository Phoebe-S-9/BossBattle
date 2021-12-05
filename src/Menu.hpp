/*
 *  BossBattle
 *  Author: Phoebe Schulman
 *  Version: 2021-11-27
 */
#ifndef MENU_HPP_
#define MENU_HPP_

#include <GL/glut.h>

void menu();
void mainMenu(GLint option);

//void VCSTransMenu(GLint transOption);
void reset();

//void VCSTransform(GLint);

//void cullMenu(GLint option);
//void lightMenu(GLint option);
//void lightTransform(GLint);
void shadeMenu(GLint option);
void animateMenu(GLint option);

void noskMove(void);/* nosk move back and forth */
void knightJumpDown(void); //knight jumping animation
void knightJumpUp(void); //knight jumping animation
void infection(); //infection attack

#endif
