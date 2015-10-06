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
	int die();	//¥s¤l¼u¦Û§Ú®ø·À
	//§PÂ_¬O§_À»¤¤¼Ä¤H
	void hitenemy(Enemy enemy[MAXENEMY], int* grade, int *enemynum, Item item[MAXITEM], int *itemnum);
	//§PÂ_¬O§_À»¤¤ª±®a
	void hitplayer(Player& player, int *ebulletnum, Item item[MAXITEM], int *itemnum, int *grade, int *graze);
	void init(int initx, int inity, int initvx, int initvy, int initskin, int initmode, int initspeed);
	~Bullet();
private:
	int x;
	int y;
	int vx;	//X¤è¦V³t«×
	int vy;
	int speed; //¾ãÅé³t«×
	int skin;	//¶K¹Ï½s¸¹
	int length;
	int width;
	int drawx;	//¶K¹Ï¼È¦s®y¼Ğ
	int drawy;
	int mode;	//²¾°Ê¼Ò¦¡
	bool dead;
	bool vchange;	//§PÂ_³t«×¬O§_§EÜ
	double angle;	//¶K¹Ï±ÛÂà¨¤«×
	int movecount;
	PicPosition pos;	//¶K¹Ï®y¼Ğ
};

class Item{
public:
	Item();
	int dispaly(GLuint *texture);
	int move(int *num);
	//§PÂ_¬O§_³Q¦Y
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
	PicPosition pos;	//¶K¹Ï¦Em
};

class Enemy{
public:
	Enemy();
	~Enemy();
	bool isdead();
	int get(int choice);	//¦^¶Ç¸ET
	//µo®g¤l¼u
	void fire(Bullet ebullet[],Player& player, int data[][3], int *num);
	void init(int data[], int posx, int posy);
	//¨EË®`
	void hurt(int *grade, int power, Item item[MAXITEM], int *itemnum, int *num);
	int dispaly(GLuint *texture);
	int move(int *num); 
private:
	bool dead;			//¬O§_¦º¤`
	bool damage;		//¬O§_¨EË
	int length;
	int width;
	int x;				//x¶b®y¼Ğ
	int y;				//y¶b®y¼Ğ
	int x_step;			//x¶b²¾°Ê
	int y_step;			//y¶b²¾°Ê
	int itemtype;			//¥´­Ë«á©Ò±¼¥Xªºª««~
	int skin;			//¼Ä¾÷¥~«¬
	int blood;			//¼Ä¾÷¦å¶q
	int score;			//¥´­Ë©ÒÀò±o¤À¼Æ
	int bullet;			//¤l¼uÃş«¬
	int type;			//µo¼u¼Ò¦¡
	int period;			//µo¼u®É¶¡
	int mode;			//²¾°Ê¼Ò¦¡
	int firecount;
	int movecount;
	int theta;
	int staytime;		//°±¯d®É¶¡
	PicPosition pos;	//¶K¹Ï¦Em
};

class Player{
public:
	Player();
	bool init();
	void display();
	int get(int choice);
	//¦Y¨EF¦E
	void powerup(int type, int* grade);
	void move(int dire);
	int fire(Bullet pbullet[]);
	//³QÀ»¤¤
	void die(Item item[MAXITEM], int *itemnum);
	//µebomb®ÄªG
	void displaybomb(GLuint *texture);
	//gameover«áÄ~ÄE
	void goon();
	//¨Ï¥Îbomb
	void bomb();
	~Player();
private:
	GLuint texture;
	bool dead;
	int x;
	int y;
	int state;		//¶K¹Ïª¬ªp
	float range;	//¶K¹Ï¤j¤p
	int power;		//¤õ¤O
	int life;		//¥Í©R
	int bombnum;	//bomb¼Æ
	bool isbomb;	//¬O§_¥¿¦b¥Îbomb
	int slow;
	int count;		//¶K¹Ï­p¼Æ
	int deadcount;
	int powercount;
	int firecount;
	int bombcount;
};

class Game{
public:
	Game();
	bool init();
	//¥ÑÁä½L¿é¤J©Ò¹E³¦æ°Ê
	void act(int action);
	void display();
	//¹CÀ¸¶i¦E
	void goon();
	//²£¥Í¼Ä¤H
	int generateE();	
	//µe¦r
	static void drawtext(char *str, int posx, int posy, int r, int g, int b);
	~Game();
private:
	bool LoadGameData();	//Åª¨ú¹CÀ¸¸ET
	void drawstate();	//µe¥X¹CÀ¸¸ET
	int time;	//²{¦b®É¶¡
	int state;	//¹CÀ¸ª¬ºA
	int grade;	//¤À¼Æ
	int graze;	//À¿¼u¼Æ
	int enemynum;	//µe­±¤W¼Ä¤H¼Æ
	int itemnum;	//µe­±¤Wª««~¼Æ
	int ebulletnum;	//µe­±¤W¼Ä¤H¤l¼u¼Æ
	int pbulletnum;	//µe­±¤Wª±®a¤l¼u¼Æ
	int emy_time[MAXNUM][4];	//¼Ä¤H²£¥Í®É¶¡
	int emy_data[MAXTYPE][12];	//¼Ä¤H³]©w¸ET
	int bul_data[MAXTYPE][3];	//¤l¼u³]©w¸ET
	GLuint bombpic;			//¶K¹ÏÅÜ¼Æ
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
