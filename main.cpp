#include "def.h"
#include "obj.h"
#include "func.h"
#include<time.h>
#include<gl/glut.h>
#include<iostream>
#define TIME 33
using namespace std;

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

BG bg;
Game game;

bool moveUp = false;
bool moveDown = false;
bool moveLeft = false;
bool moveRight = false;
bool moveFire = false;
bool moveSlow = false;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//µe¹Ï
	// 
	bg.display();
	game.display();

	glutSwapBuffers();
}

bool isShift = false;

void timer(int value){
	if (moveUp)
	{
		game.act(moveSlow ? SLOW_UP : MOVE_UP);
	}
	if (moveDown)
	{
		game.act(moveSlow ? SLOW_DOWN : MOVE_DOWN);
	}
	if (moveLeft)
	{
		game.act(moveSlow ? SLOW_LEFT : MOVE_LEFT);
	}
	if (moveRight)
	{
		game.act(moveSlow ? SLOW_RIGHT : MOVE_RIGHT);
	}
	if (moveFire)
	{
		game.act(FIRE);
	}

	game.goon();

	glutTimerFunc(TIME, timer, 1);
}

void spinDisplay(void)
{
	
	glutPostRedisplay();
}

void init(void)
{
	srand(time(NULL));
	alutInit(0, NULL);

	LoadWave();
	bg.init();
	game.init();

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background

	glEnable(GL_BLEND);									//Enable ³z©E
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void myReshape(int width, int height)
{
	 	if (height==0)										// Prevent A Divide By Zero By
	 	{
	 		height=1;										// Making Height Equal One
	 	}
	 
	 	glViewport(0,0,width,height);						// Reset The Current Viewport
	 
	 	
	 	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	 	glLoadIdentity();									// Reset The Projection Matrix
	 	
	 	//³]©w2D§Ev¯x°}
	 	gluOrtho2D(0, (GLfloat)WINDOWX, (GLfloat)WINDOWY, 0);
	 	
	 	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	 	glLoadIdentity();									// Reset The Modelview Matrix
}

void keyborad1(int key, int x, int y){

	switch (key){
	case GLUT_KEY_UP:moveUp = true; break;
	case GLUT_KEY_DOWN:moveDown = true; break;
	case GLUT_KEY_LEFT:moveLeft = true; break;
	case GLUT_KEY_RIGHT:moveRight = true; break;
	case GLUT_KEY_F2:game.act(POWERUP); break;
	}
}

void keyboard1up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:moveUp = false; break;
	case GLUT_KEY_DOWN:moveDown = false; break;
	case GLUT_KEY_LEFT:moveLeft = false; break;
	case GLUT_KEY_RIGHT:moveRight = false; break;
	}
}

void keyboard2(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 13:game.act(ENTER); break;
	case 'z':moveFire = true; break;
	case 'x':moveSlow = true; break;
	case 'c':game.act(BOMB); break;
	}
}

void keyboard2up(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'z':moveFire = false; break;
	case 'x':moveSlow = false; break;
	}
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOWX, WINDOWY);
	glutCreateWindow("TouhouARC");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(spinDisplay);
	glutTimerFunc(TIME, timer, 1);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutSpecialFunc(keyborad1);
	glutSpecialUpFunc(keyboard1up);
	glutKeyboardFunc(keyboard2);
	glutKeyboardUpFunc(keyboard2up);
	glutSetCursor(GLUT_CURSOR_NONE);
	init();
	glutMainLoop();

}

