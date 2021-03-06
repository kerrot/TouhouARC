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
	int die();	//叫子彈自我消滅
	//判斷是否擊中敵人
	void hitenemy(Enemy enemy[MAXENEMY], int* grade, int *enemynum, Item item[MAXITEM], int *itemnum);
	//判斷是否擊中玩家
	void hitplayer(Player& player, int *ebulletnum, Item item[MAXITEM], int *itemnum, int *grade, int *graze);
	void init(int initx, int inity, int initvx, int initvy, int initskin, int initmode, int initspeed);
	~Bullet();
private:
	int x;
	int y;
	int vx;	//X方向速度
	int vy;
	int speed; //整體速度
	int skin;	//貼圖編號
	int length;
	int width;
	int drawx;	//貼圖暫存座標
	int drawy;
	int mode;	//移動模式
	bool dead;
	bool vchange;	//判斷速度是否��E�
	double angle;	//貼圖旋轉角度
	int movecount;
	PicPosition pos;	//貼圖座標
};

class Item{
public:
	Item();
	int dispaly(GLuint *texture);
	int move(int *num);
	//判斷是否被吃
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
	PicPosition pos;	//貼圖��Em
};

class Enemy{
public:
	Enemy();
	~Enemy();
	bool isdead();
	int get(int choice);	//回傳��ET
	//發射子彈
	void fire(Bullet ebullet[],Player& player, int data[][3], int *num);
	void init(int data[], int posx, int posy);
	//��E阨`
	void hurt(int *grade, int power, Item item[MAXITEM], int *itemnum, int *num);
	int dispaly(GLuint *texture);
	int move(int *num); 
private:
	bool dead;			//是否死亡
	bool damage;		//是否��E�
	int length;
	int width;
	int x;				//x軸座標
	int y;				//y軸座標
	int x_step;			//x軸移動
	int y_step;			//y軸移動
	int itemtype;			//打倒後所掉出的物品
	int skin;			//敵機外型
	int blood;			//敵機血量
	int score;			//打倒所獲得分數
	int bullet;			//子彈類型
	int type;			//發彈模式
	int period;			//發彈時間
	int mode;			//移動模式
	int firecount;
	int movecount;
	int theta;
	int staytime;		//停留時間
	PicPosition pos;	//貼圖��Em
};

class Player{
public:
	Player();
	bool init();
	void display();
	int get(int choice);
	//吃��EF��E
	void powerup(int type, int* grade);
	void move(int dire);
	int fire(Bullet pbullet[]);
	//被擊中
	void die(Item item[MAXITEM], int *itemnum);
	//畫bomb效果
	void displaybomb(GLuint *texture);
	//gameover後繼��E
	void goon();
	//使用bomb
	void bomb();
	~Player();
private:
	GLuint texture;
	bool dead;
	int x;
	int y;
	int state;		//貼圖狀況
	float range;	//貼圖大小
	int power;		//火力
	int life;		//生命
	int bombnum;	//bomb數
	bool isbomb;	//是否正在用bomb
	int slow;
	int count;		//貼圖計數
	int deadcount;
	int powercount;
	int firecount;
	int bombcount;
};

class Game{
public:
	Game();
	bool init();
	//由鍵盤輸入所��E釵瘞�
	void act(int action);
	void display();
	//遊戲進��E
	void goon();
	//產生敵人
	int generateE();	
	//畫字
	static void drawtext(char *str, int posx, int posy, int r, int g, int b);
	~Game();
private:
	bool LoadGameData();	//讀取遊戲��ET
	void drawstate();	//畫出遊戲��ET
	int time;	//現在時間
	int state;	//遊戲狀態
	int grade;	//分數
	int graze;	//擦彈數
	int enemynum;	//畫面上敵人數
	int itemnum;	//畫面上物品數
	int ebulletnum;	//畫面上敵人子彈數
	int pbulletnum;	//畫面上玩家子彈數
	int emy_time[MAXNUM][4];	//敵人產生時間
	int emy_data[MAXTYPE][12];	//敵人設定��ET
	int bul_data[MAXTYPE][3];	//子彈設定��ET
	GLuint bombpic;			//貼圖變數
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
