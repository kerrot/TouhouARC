#pragma once

#include <gl\glaux.h>		// Header File For The Glaux Library
#include <al\alut.h>
#include "tga.h"

#define REFRESH_TIMER 100

AUX_RGBImageRec *LoadBMP(const char *Filename);	//Ū��BMP
int RGBToRGBA(AUX_RGBImageRec *image);			//BMP��TGA
bool LoadGLTextures(GLuint *texture, char *filename, bool tga);//Ū���K��
int LoadTGATextures(GLuint *texture, char *filename);	//Ū���GA�K��
bool Refresh();// �P�_�O�_��s

ALboolean LoadWave(void);	//Ū���n��
void SoundFunc(int choice, int func);	//�ާ@�n��
ALboolean wavelist(char *title, int num, float volume);	//���ͤ@�ӥi�Ϊ��n��