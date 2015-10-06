#pragma once

#include "glm.h"
#include <gl\glaux.h>

#define MAXENEMY 50
#define MAXBULLET 2000
#define MAXITEM 100
#define MAXTYPE 50
#define MAXNUM  500
#define MAXLEN 100
#define MBSPEED -40
#define SBSPEED -20
#define FASTSPEED 10
#define SLOWSPEED 3

typedef struct PicPosition{
	float up;
	float left;
	float right;
	float down;
}PicPosition;

class Player;
class Enemy;
class Item;

class BG{
public:
	BG();
	bool init();
	void display();
	~BG();
	static float range;
private:
	void drawtree();
	GLuint texture;
	GLMmodel* modelPtr;
	GLfloat fAspect;
};

class Bullet{
public:
	Bullet();
	int dispaly(GLuint *texture);
	int move(int *num, Player& player);
	bool isdead();
	int die();	//�s�l�u�ۧڮ���
	//�P�_�O�_�����ĤH
	void hitenemy(Enemy enemy[MAXENEMY], int* grade, int *enemynum, Item item[MAXITEM], int *itemnum);
	//�P�_�O�_�������a
	void hitplayer(Player& player, int *ebulletnum, Item item[MAXITEM], int *itemnum, int *grade, int *graze);
	void init(int initx, int inity, int initvx, int initvy, int initskin, int initmode, int initspeed);
	~Bullet();
private:
	int x;
	int y;
	int vx;	//X��V�t��
	int vy;
	int speed; //����t��
	int skin;	//�K�Ͻs��
	int length;
	int width;
	int drawx;	//�K�ϼȦs�y��
	int drawy;
	int mode;	//���ʼҦ�
	bool dead;
	bool vchange;	//�P�_�t�׬O�_��E�
	double angle;	//�K�ϱ��ਤ��
	int movecount;
	PicPosition pos;	//�K�Ϯy��
};

class Item{
public:
	Item();
	int dispaly(GLuint *texture);
	int move(int *num);
	//�P�_�O�_�Q�Y
	void eated(Player& player, int* num, int *grade);
	bool isdead();
	void init(int initx, int inity, int initvx, int initvy, int initskin);
	~Item();
private:
	int x;
	int y;
	int vx;
	int vy;
	int skin;
	int length;
	int width;
	bool dead;
	int counter;
	PicPosition pos;	//�K�Ϧ�Em
};

class Enemy{
public:
	Enemy();
	~Enemy();
	bool isdead();
	int get(int choice);	//�^�Ǹ�ET
	//�o�g�l�u
	void fire(Bullet ebullet[],Player& player, int data[][3], int *num);
	void init(int data[], int posx, int posy);
	//��Eˮ`
	void hurt(int *grade, int power, Item item[MAXITEM], int *itemnum, int *num);
	int dispaly(GLuint *texture);
	int move(int *num); 
private:
	bool dead;			//�O�_���`
	bool damage;		//�O�_��E�
	int length;
	int width;
	int x;				//x�b�y��
	int y;				//y�b�y��
	int x_step;			//x�b����
	int y_step;			//y�b����
	int itemtype;			//���˫�ұ��X�����~
	int skin;			//�ľ��~��
	int blood;			//�ľ���q
	int score;			//���˩���o����
	int bullet;			//�l�u����
	int type;			//�o�u�Ҧ�
	int period;			//�o�u�ɶ�
	int mode;			//���ʼҦ�
	int firecount;
	int movecount;
	int theta;
	int staytime;		//���d�ɶ�
	PicPosition pos;	//�K�Ϧ�Em
};

class Player{
public:
	Player();
	bool init();
	void display();
	int get(int choice);
	//�Y��EF��E
	void powerup(int type, int* grade);
	void move(int dire);
	int fire(Bullet pbullet[]);
	//�Q����
	void die(Item item[MAXITEM], int *itemnum);
	//�ebomb�ĪG
	void displaybomb(GLuint *texture);
	//gameover���~āE
	void goon();
	//�ϥ�bomb
	void bomb();
	~Player();
private:
	GLuint texture;
	bool dead;
	int x;
	int y;
	int state;		//�K�Ϫ��p
	float range;	//�K�Ϥj�p
	int power;		//���O
	int life;		//�ͩR
	int bombnum;	//bomb��
	bool isbomb;	//�O�_���b��bomb
	int slow;
	int count;		//�K�ϭp��
	int deadcount;
	int powercount;
	int firecount;
	int bombcount;
};

class Game{
public:
	Game();
	bool init();
	//����L��J�ҹ�E����
	void act(int action);
	void display();
	//�C���i��E
	void goon();
	//���ͼĤH
	int generateE();	
	//�e�r
	static void drawtext(char *str, int posx, int posy, int r, int g, int b);
	~Game();
private:
	bool LoadGameData();	//Ū���C����ET
	void drawstate();	//�e�X�C����ET
	int time;	//�{�b�ɶ�
	int state;	//�C�����A
	int grade;	//����
	int graze;	//���u��
	int enemynum;	//�e���W�ĤH��
	int itemnum;	//�e���W���~��
	int ebulletnum;	//�e���W�ĤH�l�u��
	int pbulletnum;	//�e���W���a�l�u��
	int emy_time[MAXNUM][4];	//�ĤH���ͮɶ�
	int emy_data[MAXTYPE][12];	//�ĤH�]�w��ET
	int bul_data[MAXTYPE][3];	//�l�u�]�w��ET
	GLuint bombpic;			//�K���ܼ�
	GLuint bulletpic;
	GLuint enemypic;
	GLuint itempic;
	GLuint facepic;
	GLuint winpic;
	Enemy enemy[MAXENEMY];
	Bullet ebullet[MAXBULLET];
	Bullet pbullet[MAXBULLET];
	Item item[MAXITEM];
	Player player;
};
