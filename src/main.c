#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "read_bitmap.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "freeglut.lib")

#define KEY_ESC 27
#define KEY_SPC 32
#define imageWidth 8
#define imageHeight 8

int ReadBitMapData();
void polarview(void);
void resetview(void);
int xBegin = 0, yBegin = 0;
int mButton;
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 30.0, fovy = 60.0;
double rt = 0, lt = 0, ft = 0, bt = 0, tt = 0, ut = 0;
int Esurface[24] = { 11,12,13,21,23,24,31,32,35,41,44,45,56,53,52,66,64,63,76,72,75,86,84,85 };
int Msurface[24] = {21,23,31,34,41,45,11,12,52,53,63,64,74,75,82,85,103,106,114,116,125,126,92,96};

void initTexture(void);

void EdgeDisplay(int e_num) 
{
	switch (Esurface[e_num]) {
	case 11:
		glBegin(GL_QUADS);//1t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.15, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, 0.15, 0.45);
		glEnd();
		break;
	case 12:
		glBegin(GL_QUADS);//1t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.15, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, 0.15, 0.45);
		glEnd();
		break;
	case 13:
		glBegin(GL_QUADS);//1t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, 0.45, 0.15);
		glEnd();
		break;
	case 21:
		glBegin(GL_QUADS);//3t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, 0.15, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.15, 0.45);
		glEnd();
		break;
	case 23:
		glBegin(GL_QUADS);//3t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, 0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.45, 0.15);
		glEnd();
		break;
	case 24:
		glBegin(GL_QUADS);//3t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, 0.15, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, 0.45, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.15, 0.45);
		glEnd();
		break;
	case 31:
		glBegin(GL_QUADS);//1u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.15, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, -0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.45, 0.45);
		glEnd();
		break;
	case 32:
		glBegin(GL_QUADS);//1u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.15, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, -0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, -0.45, 0.45);
		glEnd();
		break;
	case 35:
		glBegin(GL_QUADS);//1u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, -0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.45, 0.15);
		glEnd();
		break;
	case 41:
		glBegin(GL_QUADS);//3u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.45, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, -0.15, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, 0.45);
		glEnd();
		break;
	case 44:
		glBegin(GL_QUADS);//3u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, -0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, -0.15, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, 0.45);
		glEnd();
		break;
	case 45:
		glBegin(GL_QUADS);//3u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, -0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, 0.15);
		glEnd();
		break;
	case 52:
		glBegin(GL_QUADS);//7t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, 0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, 0.15, -0.15);
		glEnd();
		break;
	case 53:
		glBegin(GL_QUADS);//7t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, 0.45, -0.45);
		glEnd();
		break;
	case 56:
		glBegin(GL_QUADS);//7t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.45, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, 0.15, -0.45);
		glEnd();
		break;
	case 63:
		glBegin(GL_QUADS);//9t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, 0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.45, -0.45);
		glEnd();
		break;
	case 64:
		glBegin(GL_QUADS);//9t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, 0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, 0.45, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.15, -0.15);
		glEnd();
		break;
	case 66:
		glBegin(GL_QUADS);//9t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, 0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.45, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.15, -0.45);
		glEnd();
		break;
	case 72:
		glBegin(GL_QUADS);//7u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, -0.15, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, -0.45, -0.15);
		glEnd();
		break;
	case 75:
		glBegin(GL_QUADS);//7u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, -0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.45, -0.45);
		glEnd();
		break;
	case 76:
		glBegin(GL_QUADS);//7u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, -0.15, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.45, -0.45);
		glEnd();
		break;
	case 84:
		glBegin(GL_QUADS);//9u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, -0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.15, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, -0.15);
		glEnd();
		break;
	case 85:
		glBegin(GL_QUADS);//9u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, -0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, -0.45);
		glEnd();
		break;
	case 86:
		glBegin(GL_QUADS);//9u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, -0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.15, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, -0.45);
		glEnd();
		break;
	}
}

void MidDisplay(int m_num)
{
	switch (Msurface[m_num]) {
	case 11:
		glBegin(GL_QUADS);//1m
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.15, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.15, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.15, 0.45);
		glEnd();
		break;
	case 12:
		glBegin(GL_QUADS);//1m
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.15, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.15, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, 0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, -0.15, 0.45);
		glEnd();
		break;
	case 21:
		glBegin(GL_QUADS);//2t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, 0.15, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, 0.15, 0.45);
		glEnd();
		break;
	case 23:
		glBegin(GL_QUADS);//2t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, 0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, 0.45, 0.15);
		glEnd();
		break;
	case 31:
		glBegin(GL_QUADS);//3m
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.15, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.15, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.15, 0.45);
		glEnd();
		break;
	case 34:
		glBegin(GL_QUADS);//3m
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, -0.15, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, 0.15, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.15, 0.45);
		glEnd();
		break;
	case 41:
		glBegin(GL_QUADS);//2u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.45, 0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, -0.15, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, -0.15, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.45, 0.45);
		glEnd();
		break;
	case 45:
		glBegin(GL_QUADS);//2u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.45, 0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, -0.45, 0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, -0.45, 0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.45, 0.15);
		glEnd();
		break;
	case 52:
		glBegin(GL_QUADS);//4t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.15, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, 0.45, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, 0.15, 0.15);
		glEnd();
		break;
	case 53:
		glBegin(GL_QUADS);//4t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, 0.45, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.45, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.45, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, 0.45, -0.15);
		glEnd();
		break;
	case 63:
		glBegin(GL_QUADS);//6t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, 0.45, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.45, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.45, -0.15);
		glEnd();
		break;
	case 64:
		glBegin(GL_QUADS);//6t
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, 0.15, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, 0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.45, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, 0.15, 0.15);
		glEnd();
		break;
	case 74:
		glBegin(GL_QUADS);//6u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, -0.45, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, -0.15, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.15, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, 0.15);
		glEnd();
		break;
	case 75:
		glBegin(GL_QUADS);//6u
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.45, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, -0.45, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, -0.45, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.45, -0.15);
		glEnd();
		break;
	case 82:
		glBegin(GL_QUADS);//4u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.15, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, -0.15, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, -0.45, 0.15);
		glEnd();
		break;
	case 85:
		glBegin(GL_QUADS);//4u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.45, -0.15);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, -0.45, 0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, -0.45, 0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.45, -0.15);
		glEnd();
		break;
	case 92:
		glBegin(GL_QUADS);//7m
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, 0.15, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, -0.15, -0.15);
		glEnd();
		break;
	case 96:
		glBegin(GL_QUADS);//7m
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.15, 0.15, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.15, -0.45);
		glEnd();
		break;
	case 103:
		glBegin(GL_QUADS);//8t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, 0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, 0.45, -0.45);
		glEnd();
		break;
	case 106:
		glBegin(GL_QUADS);//8t
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, 0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.45, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.45, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, 0.15, -0.45);
		glEnd();
		break;
	case 114:
		glBegin(GL_QUADS);//9m
		glTexCoord2f(0.0, 0.0); glVertex3f(0.45, -0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.45, 0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.15, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.15, -0.15);
		glEnd();
		break;
	case 116:
		glBegin(GL_QUADS);//9m
		glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.15, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.15, 0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.15, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.15, -0.45);
		glEnd();
		break;
	case 125:
		glBegin(GL_QUADS);//8u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, -0.45, -0.15);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, -0.45, -0.15);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.45, -0.45);
		glEnd();
		break;
	case 126:
		glBegin(GL_QUADS);//8u
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.45, -0.45);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, -0.15, -0.45);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.15, -0.15, -0.45);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.45, -0.45);
		glEnd();
		break;
	}
}

void EdgeRotate(e_num) {
	if (((rt != 0) && (rt >= -90)) || ((lt != 0) && (lt >= -90))) {
		switch (Esurface[e_num]) {
		case 21:
		case 23:
		case 24:
		case 41:
		case 44:
		case 45:
		case 63:
		case 64:
		case 66:
		case 84:
		case 85:
		case 86:
			glRotatef(-rt, 1., 0., 0.);
			break;
		case 11:
		case 12:
		case 13:
		case 31:
		case 32:
		case 35:
		case 52:
		case 53:
		case 56:
		case 72:
		case 75:
		case 76:
			glRotatef(lt, 1., 0., 0.);
			break;
		default:
			break;
		}
	}
	else if (((ft != 0) && (ft >= -90)) || ((bt != 0) && (bt >= -90))) {
		switch (Esurface[e_num]) {
		case 11:
		case 12:
		case 13:
		case 21:
		case 23:
		case 24:
		case 31:
		case 32:
		case 35:
		case 41:
		case 44:
		case 45:
			glRotatef(-ft, 0., 0., 1.);
			break;
		case 52:
		case 53:
		case 56:
		case 63:
		case 64:
		case 66:
		case 72:
		case 75:
		case 76:
		case 84:
		case 85:
		case 86:
			glRotatef(bt, 0., 0., 1.);
			break;
		default:
			break;
		}
	}
	else if (((tt != 0) && (tt >= -90)) || ((ut != 0) && (ut >= -90))) {
		switch (Esurface[e_num]) {
		case 11:
		case 12:
		case 13:
		case 21:
		case 23:
		case 24:
		case 52:
		case 53:
		case 56:
		case 63:
		case 64:
		case 66:
			glRotatef(-tt, 0., 1., 0.);
			break;
		case 31:
		case 32:
		case 35:
		case 41:
		case 44:
		case 45:
		case 72:
		case 75:
		case 76:
		case 84:
		case 85:
		case 86:
			glRotatef(ut, 0., 1., 0.);
			break;
		default:
			break;
		}
	}
}

void MidRotate(m_num) {
	if (((rt != 0) && (rt >= -90)) || ((lt != 0) && (lt >= -90))) {
		switch (Msurface[m_num]) {
		case 31:
		case 34:
		case 63:
		case 64:
		case 74:
		case 75:
		case 114:
		case 116:
			glRotatef(-rt, 1., 0., 0.);
			break;
		case 11:
		case 12:
		case 52:
		case 53:
		case 82:
		case 85:
		case 92:
		case 96:
			glRotatef(lt, 1., 0., 0.);
			break;
		default:
			break;
		}
	}
	else if (((ft != 0) && (ft >= -90)) || ((bt != 0) && (bt >= -90))) {
		switch (Msurface[m_num]) {
		case 11:
		case 12:
		case 21:
		case 23:
		case 31:
		case 34:
		case 41:
		case 45:
			glRotatef(-ft, 0., 0., 1.);
			break;
		case 92:
		case 96:
		case 103:
		case 106:
		case 114:
		case 116:
		case 125:
		case 126:
			glRotatef(bt, 0., 0., 1.);
			break;
		default:
			break;
		}
	}
	else if (((tt != 0) && (tt >= -90)) || ((ut != 0) && (ut >= -90))) {
		switch (Msurface[m_num]) {
		case 21:
		case 23:
		case 52:
		case 53:
		case 63:
		case 64:
		case 103:
		case 106:
			glRotatef(-tt, 0., 1., 0.);
			break;
		case 41:
		case 45:
		case 74:
		case 75:
		case 82:
		case 85:
		case 125:
		case 126:
			glRotatef(ut, 0., 1., 0.);
			break;
		default:
			break;
		}
	}
}

void display(void)
{
	float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	polarview();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	glBindTexture(GL_TEXTURE_2D, 1);//white

	glPushMatrix();
	EdgeRotate(6);
	EdgeDisplay(6);
	glPopMatrix();

	glPushMatrix();
	MidRotate(6);
	MidDisplay(6);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(0);
	EdgeDisplay(0);
	glPopMatrix();

	glPushMatrix();
	MidRotate(4);
	MidDisplay(4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-ft, 0., 0., 1.);
	glBegin(GL_QUADS);//2m
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.15, 0.45);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.15, 0.45);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.15, 0.45);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.15, 0.45);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	MidRotate(0);
	MidDisplay(0);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(9);
	EdgeDisplay(9);
	glPopMatrix();

	glPushMatrix();
	MidRotate(2);
	MidDisplay(2);
	glPopMatrix();
	
	glPushMatrix();
	EdgeRotate(3);
	EdgeDisplay(3);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 2);//yellow

	glPushMatrix();
	EdgeRotate(15);
	EdgeDisplay(15);
	glPopMatrix();

	glPushMatrix();
	MidRotate(19);
	MidDisplay(19);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(21);
	EdgeDisplay(21);
	glPopMatrix();

	glPushMatrix();
	MidRotate(17);
	MidDisplay(17);
	glPopMatrix();

	glPushMatrix();
	glRotatef(bt, 0., 0., 1.);
	glBegin(GL_QUADS);//8m
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.15, -0.45);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.15, -0.45);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.15, -0.45);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.15, -0.45);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	MidRotate(21);
	MidDisplay(21);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(12);
	EdgeDisplay(12);
	glPopMatrix();

	glPushMatrix();
	MidRotate(23);
	MidDisplay(23);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(18);
	EdgeDisplay(18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 4);//orange

	glPushMatrix();
	EdgeRotate(19);
	EdgeDisplay(19);
	glPopMatrix();

	glPushMatrix();
	MidRotate(22);
	MidDisplay(22);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(14);
	EdgeDisplay(14);
	glPopMatrix();

	glPushMatrix();
	MidRotate(14);
	MidDisplay(14);
	glPopMatrix();

	glPushMatrix();
	glRotatef(lt, 1., 0., 0.);
	glBegin(GL_QUADS);//4m
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.45, -0.15, -0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.45, 0.15, -0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.45, 0.15, 0.15);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.45, -0.15, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	MidRotate(8);
	MidDisplay(8);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(7);
	EdgeDisplay(7);
	glPopMatrix();

	glPushMatrix();
	MidRotate(7);
	MidDisplay(7);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(1);
	EdgeDisplay(1);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 3);//red

	glPushMatrix();
	EdgeRotate(22);
	EdgeDisplay(22);
	glPopMatrix();

	glPushMatrix();
	MidRotate(18);
	MidDisplay(18);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(16);
	EdgeDisplay(16);
	glPopMatrix();

	glPushMatrix();
	MidRotate(12);
	MidDisplay(12);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-rt, 1., 0., 0.);
	glBegin(GL_QUADS);//6m
	glTexCoord2f(0.0, 0.0); glVertex3f(0.45, -0.15, -0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.45, 0.15, -0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.45, 0.15, 0.15);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.45, -0.15, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	MidRotate(11);
	MidDisplay(11);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(10);
	EdgeDisplay(10);
	glPopMatrix();

	glPushMatrix();
	MidRotate(3);
	MidDisplay(3);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(5);
	EdgeDisplay(5);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 5);//blue

	glPushMatrix();
	EdgeRotate(13);
	EdgeDisplay(13);
	glPopMatrix();

	glPushMatrix();
	MidRotate(9);
	MidDisplay(9);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(2);
	EdgeDisplay(2);
	glPopMatrix();

	glPushMatrix();
	MidRotate(16);
	MidDisplay(16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-tt, 0., 1., 0.);
	glBegin(GL_QUADS);//5t
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, 0.45, -0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, 0.45, 0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.45, 0.15);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.15, 0.45, -0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	MidRotate(1);
	MidDisplay(1);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(17);
	EdgeDisplay(17);
	glPopMatrix();

	glPushMatrix();
	MidRotate(10);
	MidDisplay(10);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(4);
	EdgeDisplay(4);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 6);//green

	glPushMatrix();
	EdgeRotate(20);
	EdgeDisplay(20);
	glPopMatrix();

	glPushMatrix();
	MidRotate(15);
	MidDisplay(15);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(8);
	EdgeDisplay(8);
	glPopMatrix();

	glPushMatrix();
	MidRotate(20);
	MidDisplay(20);
	glPopMatrix();

	glPushMatrix();
	glRotatef(ut, 0., 1., 0.);
	glBegin(GL_QUADS);//5u
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.45, -0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.15, -0.45, 0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.15, -0.45, 0.15);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.45, -0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	MidRotate(5);
	MidDisplay(5);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(23);
	EdgeDisplay(23);
	glPopMatrix();

	glPushMatrix();
	MidRotate(13);
	MidDisplay(13);
	glPopMatrix();

	glPushMatrix();
	EdgeRotate(11);
	EdgeDisplay(11);
	glPopMatrix();

	

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
	glutSwapBuffers();
}

void idle(void)
{
	if ((rt < 0) && (rt >= -90)) {
		rt += 0.1;
		glutPostRedisplay();
	}
	else if ((lt < 0) && (lt >= -90)) {
		lt += 0.1;
		glutPostRedisplay();
	}
	else if ((ft < 0) && (ft >= -90)) {
		ft += 0.1;
		glutPostRedisplay();
	}
	else if ((bt < 0) && (bt >= -90)) {
		bt += 0.1;
		glutPostRedisplay();
	}
	else if ((tt < 0) && (tt >= -90)) {
		tt += 0.1;
		glutPostRedisplay();
	}
	else if ((ut < 0) && (ut >= -90)) {
		ut += 0.1;
		glutPostRedisplay();
	}
}

void myKbd(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		rt = -90;
		lt = 0;
		ft = 0;
		bt = 0;
		tt = 0;
		ut = 0;
		for (int i = 0; i <= 23; i++) {
			if (Esurface[i] == 21) {
				Esurface[i] = 63;
			}
			else if (Esurface[i] == 23) {
				Esurface[i] = 66;
			}
			else if (Esurface[i] == 24) {
				Esurface[i] = 64;
			}
			else if (Esurface[i] == 63) {
				Esurface[i] = 86;
			}
			else if (Esurface[i] == 64) {
				Esurface[i] = 84;
			}
			else if (Esurface[i] == 66) {
				Esurface[i] = 85;
			}
			else if (Esurface[i] == 84) {
				Esurface[i] = 44;
			}
			else if (Esurface[i] == 85) {
				Esurface[i] = 41;
			}
			else if (Esurface[i] == 86) {
				Esurface[i] = 45;
			}
			else if (Esurface[i] == 41) {
				Esurface[i] = 23;
			}
			else if (Esurface[i] == 44) {
				Esurface[i] = 24;
			}
			else if (Esurface[i] == 45) {
				Esurface[i] = 21;
			}

			if (Msurface[i] == 31) {
				Msurface[i] = 63;
			}
			else if (Msurface[i] == 34) {
				Msurface[i] = 64;
			}
			else if (Msurface[i] == 63) {
				Msurface[i] = 116;
			}
			else if (Msurface[i] == 64) {
				Msurface[i] = 114;
			}
			else if (Msurface[i] == 114) {
				Msurface[i] = 74;
			}
			else if (Msurface[i] == 116) {
				Msurface[i] = 75;
			}
			else if (Msurface[i] == 74) {
				Msurface[i] = 34;
			}
			else if (Msurface[i] == 75) {
				Msurface[i] = 31;
			}
		}
		glutPostRedisplay();
		break;
	case 'l':
		rt = 0;
		lt = -90;
		ft = 0;
		bt = 0;
		tt = 0;
		ut = 0;
		for (int i = 0; i <= 23; i++) {
			if (Esurface[i] == 11) {
				Esurface[i] = 35;
			}
			else if (Esurface[i] == 12) {
				Esurface[i] = 32;
			}
			else if (Esurface[i] == 13) {
				Esurface[i] = 31;
			}
			else if (Esurface[i] == 31) {
				Esurface[i] = 75;
			}
			else if (Esurface[i] == 32) {
				Esurface[i] = 72;
			}
			else if (Esurface[i] == 35) {
				Esurface[i] = 76;
			}
			else if (Esurface[i] == 72) {
				Esurface[i] = 52;
			}
			else if (Esurface[i] == 75) {
				Esurface[i] = 56;
			}
			else if (Esurface[i] == 76) {
				Esurface[i] = 53;
			}
			else if (Esurface[i] == 52) {
				Esurface[i] = 12;
			}
			else if (Esurface[i] == 53) {
				Esurface[i] = 11;
			}
			else if (Esurface[i] == 56) {
				Esurface[i] = 13;
			}

			if (Msurface[i] == 11) {
				Msurface[i] = 85;
			}
			else if (Msurface[i] == 12) {
				Msurface[i] = 82;
			}
			else if (Msurface[i] == 82) {
				Msurface[i] = 92;
			}
			else if (Msurface[i] == 85) {
				Msurface[i] = 96;
			}
			else if (Msurface[i] == 92) {
				Msurface[i] = 52;
			}
			else if (Msurface[i] == 96) {
				Msurface[i] = 53;
			}
			else if (Msurface[i] == 52) {
				Msurface[i] = 12;
			}
			else if (Msurface[i] == 53) {
				Msurface[i] = 11;
			}
		}
		glutPostRedisplay();
		break;
	case 'f':
		rt = 0;
		lt = 0;
		ft = -90;
		bt = 0;
		tt = 0;
		ut = 0;
		for (int i = 0; i <= 23; i++) {
			if (Esurface[i] == 11) {
				Esurface[i] = 21;
			}
			else if (Esurface[i] == 12) {
				Esurface[i] = 23;
			}
			else if (Esurface[i] == 13) {
				Esurface[i] = 24;
			}
			else if (Esurface[i] == 21) {
				Esurface[i] = 41;
			}
			else if (Esurface[i] == 23) {
				Esurface[i] = 44;
			}
			else if (Esurface[i] == 24) {
				Esurface[i] = 45;
			}
			else if (Esurface[i] == 41) {
				Esurface[i] = 31;
			}
			else if (Esurface[i] == 44) {
				Esurface[i] = 35;
			}
			else if (Esurface[i] == 45) {
				Esurface[i] = 32;
			}
			else if (Esurface[i] == 31) {
				Esurface[i] = 11;
			}
			else if (Esurface[i] == 32) {
				Esurface[i] = 13;
			}
			else if (Esurface[i] == 35) {
				Esurface[i] = 12;
			}

			if (Msurface[i] == 11) {
				Msurface[i] = 21;
			}
			else if (Msurface[i] == 12) {
				Msurface[i] = 23;
			}
			else if (Msurface[i] == 21) {
				Msurface[i] = 31;
			}
			else if (Msurface[i] == 23) {
				Msurface[i] = 34;
			}
			else if (Msurface[i] == 31) {
				Msurface[i] = 41;
			}
			else if (Msurface[i] == 34) {
				Msurface[i] = 45;
			}
			else if (Msurface[i] == 41) {
				Msurface[i] = 11;
			}
			else if (Msurface[i] == 45) {
				Msurface[i] = 12;
			}
		}
		glutPostRedisplay();
		break;
	case 'b':
		rt = 0;
		lt = 0;
		ft = 0;
		bt = -90;
		tt = 0;
		ut = 0;
		for (int i = 0; i <= 23; i++) {
			if (Esurface[i] == 52) {
				Esurface[i] = 75;
			}
			else if (Esurface[i] == 53) {
				Esurface[i] = 72;
			}
			else if (Esurface[i] == 56) {
				Esurface[i] = 76;
			}
			else if (Esurface[i] == 72) {
				Esurface[i] = 85;
			}
			else if (Esurface[i] == 75) {
				Esurface[i] = 84;
			}
			else if (Esurface[i] == 76) {
				Esurface[i] = 86;
			}
			else if (Esurface[i] == 84) {
				Esurface[i] = 63;
			}
			else if (Esurface[i] == 85) {
				Esurface[i] = 64;
			}
			else if (Esurface[i] == 86) {
				Esurface[i] = 66;
			}
			else if (Esurface[i] == 63) {
				Esurface[i] = 52;
			}
			else if (Esurface[i] == 64) {
				Esurface[i] = 53;
			}
			else if (Esurface[i] == 66) {
				Esurface[i] = 56;
			}

			if (Msurface[i] == 92) {
				Msurface[i] = 125;
			}
			else if (Msurface[i] == 96) {
				Msurface[i] = 126;
			}
			else if (Msurface[i] == 125) {
				Msurface[i] = 114;
			}
			else if (Msurface[i] == 126) {
				Msurface[i] = 116;
			}
			else if (Msurface[i] == 114) {
				Msurface[i] = 103;
			}
			else if (Msurface[i] == 116) {
				Msurface[i] = 106;
			}
			else if (Msurface[i] == 103) {
				Msurface[i] = 92;
			}
			else if (Msurface[i] == 106) {
				Msurface[i] = 96;
			}
		}
		glutPostRedisplay();
		break;
	case 't':
		rt = 0;
		lt = 0;
		ft = 0;
		bt = 0;
		tt = -90;
		ut = 0;
		for (int i = 0; i <= 23; i++) {
			if (Esurface[i] == 11) {
				Esurface[i] = 52;
			}
			else if (Esurface[i] == 12) {
				Esurface[i] = 56;
			}
			else if (Esurface[i] == 13) {
				Esurface[i] = 53;
			}
			else if (Esurface[i] == 52) {
				Esurface[i] = 66;
			}
			else if (Esurface[i] == 53) {
				Esurface[i] = 63;
			}
			else if (Esurface[i] == 56) {
				Esurface[i] = 64;
			}
			else if (Esurface[i] == 63) {
				Esurface[i] = 23;
			}
			else if (Esurface[i] == 64) {
				Esurface[i] = 21;
			}
			else if (Esurface[i] == 66) {
				Esurface[i] = 24;
			}
			else if (Esurface[i] == 21) {
				Esurface[i] = 12;
			}
			else if (Esurface[i] == 23) {
				Esurface[i] = 13;
			}
			else if (Esurface[i] == 24) {
				Esurface[i] = 11;
			}

			if (Msurface[i] == 21) {
				Msurface[i] = 52;
			}
			else if (Msurface[i] == 23) {
				Msurface[i] = 53;
			}
			else if (Msurface[i] == 52) {
				Msurface[i] = 106;
			}
			else if (Msurface[i] == 53) {
				Msurface[i] = 103;
			}
			else if (Msurface[i] == 103) {
				Msurface[i] = 63;
			}
			else if (Msurface[i] == 106) {
				Msurface[i] = 64;
			}
			else if (Msurface[i] == 63) {
				Msurface[i] = 23;
			}
			else if (Msurface[i] == 64) {
				Msurface[i] = 21;
			}
		}
		glutPostRedisplay();
		break;
	case 'u':
		rt = 0;
		lt = 0;
		ft = 0;
		bt = 0;
		tt = 0;
		ut = -90;
		for (int i = 0; i <= 23; i++) {
			if (Esurface[i] == 31) {
				Esurface[i] = 44;
			}
			else if (Esurface[i] == 32) {
				Esurface[i] = 41;
			}
			else if (Esurface[i] == 35) {
				Esurface[i] = 45;
			}
			else if (Esurface[i] == 41) {
				Esurface[i] = 84;
			}
			else if (Esurface[i] == 44) {
				Esurface[i] = 86;
			}
			else if (Esurface[i] == 45) {
				Esurface[i] = 85;
			}
			else if (Esurface[i] == 84) {
				Esurface[i] = 76;
			}
			else if (Esurface[i] == 85) {
				Esurface[i] = 75;
			}
			else if (Esurface[i] == 86) {
				Esurface[i] = 72;
			}
			else if (Esurface[i] == 72) {
				Esurface[i] = 31;
			}
			else if (Esurface[i] == 75) {
				Esurface[i] = 35;
			}
			else if (Esurface[i] == 76) {
				Esurface[i] = 32;
			}

			if (Msurface[i] == 41) {
				Msurface[i] = 74;
			}
			else if (Msurface[i] == 45) {
				Msurface[i] = 75;
			}
			else if (Msurface[i] == 74) {
				Msurface[i] = 126;
			}
			else if (Msurface[i] == 75) {
				Msurface[i] = 125;
			}
			else if (Msurface[i] == 125) {
				Msurface[i] = 85;
			}
			else if (Msurface[i] == 126) {
				Msurface[i] = 82;
			}
			else if (Msurface[i] == 82) {
				Msurface[i] = 41;
			}
			else if (Msurface[i] == 85) {
				Msurface[i] = 45;
			}
		}
		glutPostRedisplay();
		break;
	case KEY_SPC:
		rt = 0;
		lt = 0;
		ft = 0;
		bt = 0;
		tt = 0;
		ut = 0;
		Esurface[0] = 11;
		Esurface[1] = 12;
		Esurface[2] = 13;
		Esurface[3] = 21;
		Esurface[4] = 23;
		Esurface[5] = 24;
		Esurface[6] = 31;
		Esurface[7] = 32;
		Esurface[8] = 35;
		Esurface[9] = 41;
		Esurface[10] = 44;
		Esurface[11] = 45;
		Esurface[12] = 56;
		Esurface[13] = 53;
		Esurface[14] = 52;
		Esurface[15] = 66;
		Esurface[16] = 64;
		Esurface[17] = 63;
		Esurface[18] = 76;
		Esurface[19] = 72;
		Esurface[20] = 75;
		Esurface[21] = 86;
		Esurface[22] = 84;
		Esurface[23] = 85;

		Msurface[0] = 21;
		Msurface[1] = 23;
		Msurface[2] = 31;
		Msurface[3] = 34;
		Msurface[4] = 41;
		Msurface[5] = 45;
		Msurface[6] = 11;
		Msurface[7] = 12;
		Msurface[8] = 52;
		Msurface[9] = 53;
		Msurface[10] = 63;
		Msurface[11] = 64;
		Msurface[12] = 74;
		Msurface[13] = 75;
		Msurface[14] = 82;
		Msurface[15] = 85;
		Msurface[16] = 103;
		Msurface[17] = 106;
		Msurface[18] = 114;
		Msurface[19] = 116;
		Msurface[20] = 125;
		Msurface[21] = 126;
		Msurface[22] = 92;
		Msurface[23] = 96;
		glutPostRedisplay();
		break;
	case KEY_ESC:
		exit(0);
	default:
		break;
	}
}

void initTexture1(void)
{
	unsigned char* image1[1];
	int imageHeightw, imageWidthw;


	if (!ReadBitMapData("white.bmp", &imageWidthw, &imageHeightw, image1)) {
		printf("Error! \n");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidthw, imageHeightw, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, *image1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void initTexture2(void)
{
	unsigned char* image2[1];
	int imageHeighty, imageWidthy;


	if (!ReadBitMapData("yellow.bmp", &imageWidthy, &imageHeighty, image2)) {
		printf("Error! \n");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidthy, imageHeighty, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, *image2);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void initTexture3(void)
{
	unsigned char* image3[1];
	int imageHeightr, imageWidthr;


	if (!ReadBitMapData("red.bmp", &imageWidthr, &imageHeightr, image3)) {
		printf("Error! \n");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, 3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidthr, imageHeightr, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, *image3);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void initTexture4(void)
{
	unsigned char* image4[1];
	int imageHeighto, imageWidtho;


	if (!ReadBitMapData("orange.bmp", &imageWidtho, &imageHeighto, image4)) {
		printf("Error! \n");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidtho, imageHeighto, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, *image4);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void initTexture5(void)
{
	unsigned char* image5[1];
	int imageHeightb, imageWidthb;


	if (!ReadBitMapData("blue.bmp", &imageWidthb, &imageHeightb, image5)) {
		printf("Error! \n");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, 5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidthb, imageHeightb, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, *image5);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void initTexture6(void)
{
	unsigned char* image6[1];
	int imageHeightg, imageWidthg;


	if (!ReadBitMapData("green.bmp", &imageWidthg, &imageHeightg, image6)) {
		printf("Error! \n");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidthg, imageHeightg, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, *image6);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void myInit(char* progname)
{
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(myKbd);

	resetview();
	initTexture1();
	initTexture2();
	initTexture3();
	initTexture4();
	initTexture5();
	initTexture6();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
}


void myReshape(int width, int height)
{
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, nearw, farw);
	glMatrixMode(GL_MODELVIEW);
}


void polarview(void)
{
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(-elevation, 1.0, 0.0, 0.0);
	glRotatef(-azimuth, 0.0, 1.0, 0.0);
}


void resetview(void)
{
	distance = 3.0;
	twist = 0.0;
	elevation = -30.0;
	azimuth = 30.0;
}

void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		mButton = button;
		xBegin = x;
		yBegin = y;
	}
}


void myMotion(int x, int y)
{
	int xDisp, yDisp;

	xDisp = x - xBegin;
	yDisp = y - yBegin;
	switch (mButton) {
	case GLUT_LEFT_BUTTON:
		azimuth += (float)xDisp / 2.0;
		elevation -= (float)yDisp / 2.0;
		break;
	}
	xBegin = x;
	yBegin = y;
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutIdleFunc(idle);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutMainLoop();
}