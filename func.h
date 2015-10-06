#pragma once

#include <gl\glaux.h>		// Header File For The Glaux Library
#include <al\alut.h>
#include "tga.h"

#define REFRESH_TIMER 100

AUX_RGBImageRec *LoadBMP(const char *Filename);	//讀取BMP
int RGBToRGBA(AUX_RGBImageRec *image);			//BMP轉TGA
bool LoadGLTextures(GLuint *texture, char *filename, bool tga);//讀取貼圖
int LoadTGATextures(GLuint *texture, char *filename);	//讀��癿A貼圖
bool Refresh();// 判斷是否更新

ALboolean LoadWave(void);	//讀取聲音
void SoundFunc(int choice, int func);	//操作聲音
ALboolean wavelist(char *title, int num, float volume);	//產生一個可用的聲音