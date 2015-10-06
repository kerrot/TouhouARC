#include "def.h"
#include "obj.h"
#include "func.h"
#include <gl/glut.h>
#include <fstream>
#include <math.h>
using namespace std;

float BG::range = WINDOWX * 0.65;	//πC¿∏Ωd≥Ú≥Ã•k√ÅE

BG::BG(){
	fAspect = (GLfloat)BG::range / (GLfloat)WINDOWY;	//µ¯®§§Ò®“
}

bool BG::init(){
	modelPtr = glmReadOBJ("tree1.obj");	//Glm≈™®˙obj
	glmFacetNormals(modelPtr);			//≠p∫‚™k¶V∂q
	glmVertexNormals(modelPtr, 90.0);

	SoundFunc(MUSIC, PLAY);			//ºΩ©Ò≠I¥∫≠µº÷

	GLfloat a[4] = { 0.2, 0.2, 0.2, 1 };	//•˙∑Ω≥]©w
	GLfloat d[4] = { 1, 1, 1, 1 };
	GLfloat s[4] = { 0.3, 0.3, 0.3, 1 };
	GLfloat pos[4] = { 0, 50.0, -100, 0.0 };
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	return LoadGLTextures(&texture, "./data/bg.bmp", false);//≈™®˙≠I¥∫πœ
}

void BG::display(){
	glColor3ub(255,0, 50);									//µe≠I¥∫πœ
    glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);glVertex2f( 0.0f , 0.0f );
		glTexCoord2f(1,1);glVertex2f( BG::range , 0.0f );
		glTexCoord2f(1,0);glVertex2f( BG::range , WINDOWY );
		glTexCoord2f(0,0); glVertex2f( 0.0f , WINDOWY );
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);										//≥±∑tÆƒ™G
		glColor4ub(0,0, 0, 0);
		glVertex2f( 0.0f , 250.0f );
		glVertex2f( BG::range , 250.0f );
		glColor4ub(0,0, 0, 255);
		glVertex2f( BG::range , WINDOWY );
		glVertex2f( 0.0f , WINDOWY );
	glEnd();
	
	glEnable(GL_TEXTURE_2D);
	drawtree();											//µeæÅE
	
}

void BG::drawtree(){
	glMatrixMode(GL_PROJECTION);						//ßÅE®≥zµÅEDÆyº–
	glPushMatrix();
	glViewport(0,0,BG::range,WINDOWY);
	glLoadIdentity();
	gluPerspective(60.0f, fAspect, 1.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	static int count = 0;								//≠pº∆æπ ≈˝æ¶b∑|∞ 
	count = (++count) % 50;

	glTranslatef(-165,-390,	-685);
	gluLookAt(0,0,count * -3,0,45,-100 - count * 3,0,1,0);

	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);		//µeæÅE
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);

	glTranslatef(290,0,-525);

	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(-50,0,75);
	glmDraw(modelPtr, GLM_SMOOTH | GLM_MATERIAL);

	glEnable(GL_TEXTURE_2D);						//¡Ÿ≠ÅE]©w
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);	

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glViewport(0,0,WINDOWX,WINDOWY);
	glMatrixMode(GL_MODELVIEW);
}

BG::~BG(){
	
}

Player::Player(){
	range = WINDOWX / 10;
	x = BG::range / 2 ;
	y = WINDOWY - range;
	state = 0;
	power = 1;
	life = 5;
	bombnum = 3;
	isbomb = false;
	dead = false;
	slow = 0;
	count = 0;
	deadcount = 0;
	powercount = 0;
	firecount = 0;
	bombcount = 0;
}

void Player::goon(){	//continue play
	power = 1;
	life = 5;
	bombnum = 3;
	dead = false;
	slow = 0;
	count = 0;
	deadcount = 0;
	powercount = 0;
	firecount = 0;
	bombcount = 0;
	SoundFunc(MUSIC, PLAY);	//º∑≠I¥∫≠µº÷
}

bool Player::init(){
	return LoadGLTextures(&texture, "./data/player.bmp", true);//≈™®˙∂Kπœ
}

void Player::display(){
	slow = (++slow) % 4;
	count = (count + slow / 3) % 4;

	(dead)? glColor4ub(255,255,255, 150): glColor4ub(255,255,255, 255);	//¶∫™∫∏‹≥z©ÅE
    glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glTranslatef(x - (range / 2), y - (range / 2), 0.0f);	//µe™±Æa
	glBegin(GL_QUADS);
		glTexCoord2f(0.25 * count,1 - 0.25 * state);
		glVertex2f( 0.0f , 0.0f );
		glTexCoord2f(0.25 * count + 0.25,1 - 0.25 * state);
		glVertex2f( range , 0.0f );
		glTexCoord2f(0.25 * count + 0.25,0.75 - 0.25 * state);
		glVertex2f( range , range );
		glTexCoord2f(0.25 * count,0.75 - 0.25 * state); 
		glVertex2f( 0.0f , range );
	glEnd();
	

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0, (GLfloat)WINDOWX, (GLfloat)WINDOWY, 0, 10, -10);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);

	glTranslatef(x, y, 0.0f);							//µeßP©w¬I
	glutSolidSphere(5, 20, 20);
	
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	state = 0;											//¡Ÿ≠ÅE®≠I¶V
	if(dead){											//µLºƒ≠pº∆
		deadcount = (++deadcount) % DEADTIME;
		(deadcount)? 1: dead = false;
	}		
}

void Player::powerup(int type, int* grade){
	switch(type){
	case 0:	(power < 9)? powercount = (++powercount) % 10 : powercount = 1;	//power≤÷øn
			if(power < 9 && powercount == 0){	//¶Y10≠”§W§…1
				++power;
				SoundFunc(POWERUP, PLAY);		//powerup≠µº÷
			}else{
				(*grade) += 100;
				SoundFunc(GET_ITEM, PLAY);		//¶Y®ÅEF¶Ë≠µº÷
			}	
			break;
	case 1:	++bombnum;SoundFunc(GET_ITEM, PLAY);break;//•[bombº∆
	case 2:	++life;SoundFunc(GET_ITEM, PLAY);break;	//•[©R
	case 3:	if(power < 9){						//§@§fÆ§…®ÅEÃ∞™
				power = 9;
				SoundFunc(POWERUP, PLAY);
			}else{
				(*grade) += 1000;
				SoundFunc(GET_ITEM, PLAY);
			}
			break;
	case  4: power = 9; break;
	}
}

int Player::fire(Bullet pbullet[]){
	firecount = (++firecount) % 10;	//µoÆg∂°πj
	if(firecount != 1) return 0;

	int i = 0, j = 0;
	int way;		//≠p∫‚¶b≠˛§@¥˙™∫§lºu
	for(j = 0; j < power; j++){
		switch(j / 3){
		case 0:way = 0;break;
		case 1:way = 50;break;
		case 2:way = -50;break;
		}
		while(pbullet[i].isdead() == false) i = (++i) % MAXBULLET;	//ß‰•i•Œ≈‹º∆
		//•D≠n§lºu
		pbullet[i].init(x + way, y - range / 2 - (j % 3) * 80,0 , MBSPEED, -2, -1, MBSPEED);
	}
	for(j = 0; j < power; j++){//∞∆ºu •™•k≥£¶≥
		while(pbullet[i].isdead() == false) i = (++i) % MAXBULLET;
		pbullet[i].init(x - range / 2 - (j % 3) * 15, y - (j / 3) * 50,0 , SBSPEED, -1, -1, SBSPEED);
		while(pbullet[i].isdead() == false) i = (++i) % MAXBULLET;
		pbullet[i].init(x + range / 2 + (j % 3) * 15, y - (j / 3) * 50,0 , SBSPEED, -1, -1, SBSPEED);
	}

	SoundFunc(PLAYER_SHOT, PLAY);	//µoÆg¡n≠µ

	return 3 * power;	//¶^∂«≤£•Õ¶h§÷§lºu
}

void Player::move(int dire){	//≤æ∞ 	®√≈‹¥´∂Kπœ ¶V•™©Œ•k®´™∫∂Kπœ
	switch(dire){
	case MOVE_RIGHT:x += FASTSPEED;state = 1;break;
	case MOVE_LEFT:	x -= FASTSPEED;state = 2;break;
	case MOVE_UP:	y -= FASTSPEED;break;
	case MOVE_DOWN:	y += FASTSPEED;break;
	case SLOW_RIGHT:x += SLOWSPEED;state = 1;break;
	case SLOW_LEFT:	x -= SLOWSPEED;state = 2;break;
	case SLOW_UP:	y -= SLOWSPEED;break;
	case SLOW_DOWN:	y += SLOWSPEED;break;
	}//∂W•XΩd≥Ú´h∞±§ÅE
	(x > BG::range - range / 4)? x = BG::range - range / 4 : 1;
	(x < range / 4)? x = range / 4 : 1;
	(y > WINDOWY - range / 2)? y = WINDOWY - range / 2 : 1;
	(y < range / 2)? y = range / 2 : 1;
}

int Player::get(int choice){	//¶^∂«∏ÅET
	switch(choice){
	case POSX: return x;
	case POSY: return y;
	case LENGTH: return range / 2;
	case WIDTH: return range;
	case BOMBNUM: return bombnum;
	case ISBOMB: return isbomb;
	case LIFE: return life;
	case POWER: return power;
	}
	return -1;
}

void Player::bomb(){		//®œ•Œ¨µºu
	if(bombnum == 0 || isbomb) return;//•ø¶b®œ•Œ´h™Ω±µ¶^∂«
	--bombnum;
	isbomb = true;
	SoundFunc(BOMB_SOUND, PLAY);//¨µºu≠µÆƒ
}

void Player::displaybomb(GLuint *texture){	//µe¨µºu
	if(!isbomb) return;

	float alpha = bombcount;
	alpha = alpha / BOMBTIME * 256;

	glColor4ub(255,255,255, (GLbyte)alpha);
    glBindTexture(GL_TEXTURE_2D, *texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);glVertex2f( 0.0f , 0.0f );
		glTexCoord2f(1,1);glVertex2f( BG::range , 0.0f );
		glTexCoord2f(1,0);glVertex2f( BG::range , WINDOWY );
		glTexCoord2f(0,0);glVertex2f( 0.0f , WINDOWY );
	glEnd();

	bombcount = (++bombcount) % BOMBTIME;//¨µºuÆ…∂°
	if(bombcount == 0)
		isbomb = false;
}

void Player::die(Item item[MAXITEM], int *itemnum){//™±Æa¶∫§`
	if(dead) return;
	--life;								//¶∫§`∑l•¢
	(power > 1)? --power : power = 1;	
	bombnum = 3;
	dead = true;
	if(life == 0){
		SoundFunc(MUSIC, PAUSE);		//∞±§˚…I¥∫≠µº÷
		SoundFunc(GAMEOVER, PLAY);		//GAMEOVER≠µº÷
	}else
		SoundFunc(DEATH, PLAY);			//¶∫§`≠µÆƒ

	int i = 0;	//≤£•Õ™´´~
	while(item[i].isdead() == false) i = (++i) % MAXITEM;
	item[i].init(x - range, y, -5, -5, 0);
	++(*itemnum);
	while(item[i].isdead() == false) i = (++i) % MAXITEM;
	item[i].init(x + range, y, 5, -5, 0);
	++(*itemnum);
	while(item[i].isdead() == false) i = (++i) % MAXITEM;
	item[i].init(x, y - range, 0, -10, 1);
	++(*itemnum);


	x = BG::range / 2 ;//¶^¬k™ÅEl¶ÅEm
	y = WINDOWY - range;
}

Player::~Player(){

}

Game::Game(){
	time = 0;
	grade = 0;
	graze = 0;
	ebulletnum = 0;
	pbulletnum = 0;
	enemynum = 0;
	itemnum = 0;
	state = 0;
	for(int i = 0; i < MAXNUM; i++)//™ÅEl§∆ºƒ§H≤£•ÕÆ…∂° ≠Y≈™®˙∏ÅE∆•¢±—´h§£∑|¶≥ºƒ§H
		emy_time[i][0] = -1;
}

bool Game::init(){
	bool succeed = true;		//≈™®˙∂Kπœ
	succeed &= (bool)LoadGLTextures(&bombpic, "./data/bomb.bmp", false);
	succeed &= (bool)LoadGLTextures(&bulletpic, "./data/bullet.bmp", true);
	succeed &= (bool)LoadGLTextures(&enemypic, "./data/enemy.bmp", true);
	succeed &= (bool)LoadGLTextures(&itempic, "./data/item.bmp", true);
	succeed &= (bool)LoadGLTextures(&facepic, "./data/face.bmp", false);
	succeed &= (bool)LoadGLTextures(&winpic, "./data/win.bmp", false);
	succeed &= player.init();
	succeed &= (bool)LoadGameData();

	return succeed;
}

void Game::display(){
	int i;
	int count;
	player.displaybomb(&bombpic);//µe¨µºu
	
	i = 0;
	count = enemynum;	//µeºƒ§H
	while(count)
		count -= enemy[i++].dispaly(&enemypic);//®Cµe§@≠”¥˚¿@ §£ª›®C¶∏µeßπ≥Ã§jº∆
	
	i = 0;
	count = pbulletnum;	//µe™±Æa§lºu
	while(count)
		count -= pbullet[i++].dispaly(&bulletpic);

	i = 0;
	count = itemnum;	//µe™´´~
	while(count)
		count -= item[i++].dispaly(&itempic);
	
	player.display();	//µeßπÆa
	
	i = 0;
	count = ebulletnum;	//µeºƒ§H§lºu
	while(count)
		count -= ebullet[i++].dispaly(&bulletpic);

	drawstate();	//µeπC¿∏∏ÅET
}

void Game::goon(){
	if(player.get(LIFE) == 0){	//GAMEOVER
		state = 1;
		return;
	}
	if(state == 2)	//πL√ÅE
		return;
	if(time == 6000){	//Æ…∂°®ÅEL√ÅE
		state = 2;
		SoundFunc(MUSIC, STOP);	//∞±§˚…I¥∫≠µº÷
		SoundFunc(WIN, PLAY);	//πL√ˆ≠µÆƒ
		return;
	}

	int i = 0;
	int count;

	enemynum += generateE();	//≤£•Õºƒ§H

	i = 0;
	count = enemynum;
	while(count){
		count -= enemy[i].move(&enemynum);	//ºƒ§H≤æ∞ 
		//≥Q¨µºu¨µ
		(player.get(ISBOMB))? enemy[i].hurt(&grade, 10, item, &itemnum, &enemynum): 1;
		//µoÆg§lºu
		enemy[i].fire(ebullet, player, bul_data, &ebulletnum);			
		i++;
	}
	i = 0;
	count = pbulletnum;
	while(count){
		count -= pbullet[i].move(&pbulletnum, player);
		//ßP¬_¿ª§§ºƒ§H
		pbullet[i].hitenemy(enemy, &grade, &enemynum, item, &itemnum);
		i++;
	}

	i = 0;
	count = itemnum;
	while(count){
		count -= item[i].move(&itemnum);
		//ßP¬_≥Q¶Y
		item[i].eated(player, &itemnum, &grade);
		i++;
	}

	i = 0;
	count = ebulletnum;
	while(count){
		count -= ebullet[i].move(&ebulletnum, player);
		//ßP¬_¿ª§§™±Æa
		ebullet[i].hitplayer(player, &ebulletnum, item, &itemnum, &grade, &graze);
		i++;
	}

	time++;
}

int Game::generateE(){
	static int now = 0;
	int i = 0, num = 0;
	while(emy_time[now][0] < time  && now < MAXNUM)
		++now;
	while(emy_time[now][0] == time){//∑˙ …∂°≤≈¶XÆ…≤£•Õ
		while(enemy[i].isdead() == false) i = (++i) % MAXENEMY;
		enemy[i].init(emy_data[ emy_time[now][1] ], emy_time[now][2], emy_time[now][3]);
		++num;
		++now;
	}
	
	return num;
}

bool Game::LoadGameData(){
	ifstream enemy, enemy_type, bullet;
	char temp[MAXLEN] = "";
	char *ptr = NULL;
	int i, j, len;
	enemy.open("enemy.txt");			//∂}¿…
	enemy_type.open("enemy_type.txt");
	bullet.open("bullet.txt");

	enemy.getline(temp, MAXLEN);		//•h±º≤ƒ§@¶ÅE
	enemy_type.getline(temp, MAXLEN);
	bullet.getline(temp, MAXLEN);

	i = 0;
	do{
		enemy.getline(temp, MAXLEN);
		ptr = strtok(temp, " \t");	//¶r¶ÅEB≤z®√¶s§J≈‹º∆
		if(ptr == NULL)
			break;
		emy_time[i][0] = atoi(ptr);
		ptr = strtok(NULL, " \t");
		emy_time[i][1] = atoi(ptr);
		ptr = strtok(NULL, " \t");
		emy_time[i][2] = atoi(ptr);
		ptr = strtok(NULL, " \t");
		emy_time[i][3] = atoi(ptr);
		++i;
	}while(1);

	i = 0; j = 0;
	do{
		j = 0;
		enemy_type.getline(temp, MAXLEN);
		len = strlen(temp);
		ptr = strtok(temp, " \t");
		while(ptr != NULL){
			emy_data[i][j++] = atoi(ptr);
			ptr = strtok(NULL, " \t");
		}
		++i;
	}while(len);
	
	i = 0; j = 0;
	do{
		j = 0;
		bullet.getline(temp, MAXLEN);
		len = strlen(temp);
		ptr = strtok(temp, " \t");
		while(ptr != NULL){
			bul_data[i][j++] = atoi(ptr);
			ptr = strtok(NULL, " \t");
		}
		++i;
	}while(len);

	enemy.close();			//√ˆ¿…
	enemy_type.close();
	bullet.close();

	return 1;
}

void Game::drawstate(){
	char temp[MAXLEN] = "";
	static int stateleft = BG::range + 30;
	int i = 0;

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(30,0,30);						//πC¿∏∏ÅETπœ©≥
	glRectf(BG::range, 0, WINDOWX, WINDOWY);

	
	/*sprintf(temp, "Time: %d", time);			//DEBUG•Œ
	drawtext(temp, 600,20, 255, 255, 255);

	sprintf(temp, "Score: %d", grade);
	drawtext(temp, 600, 50, 255, 255, 255);

	sprintf(temp, "Enemy: %d", enemynum);
	drawtext(temp, 600, 100, 255, 255, 255);

	sprintf(temp, "Pbullet: %d", pbulletnum);
	drawtext(temp, 600, 150, 255, 255, 255);

	sprintf(temp, "Item: %d", itemnum);
	drawtext(temp, 600,200, 255, 255, 255);

	sprintf(temp, "Bomb: %d", player.get(BOMBNUM));
	drawtext(temp, 600,300, 255, 255, 255);

	sprintf(temp, "Life: %d", player.get(LIFE));
	drawtext(temp, 600,350, 255, 255, 255);

	sprintf(temp, "Power: %d", player.get(POWER));
	drawtext(temp, 600,400, 255, 255, 255);

	sprintf(temp, "Ebullet: %d", ebulletnum);
	drawtext(temp, 600, 450, 255, 255, 255);

	sprintf(temp, "Graze: %d", graze);
	drawtext(temp, 600, 500, 255, 255, 255);*/

	sprintf(temp, "Score: %d", grade);			//§¿º∆
	drawtext(temp, stateleft, 50, 255, 255, 255);
	drawtext("Life: ", stateleft,100, 255, 255, 255);//•Õ©Rº∆¶rºÀ
	drawtext("Bomb: ", stateleft,150, 255, 255, 255);//¨µºuº∆¶rºÀ
	sprintf(temp, "Power: %d", player.get(POWER));	//§ı§O
	drawtext(temp, stateleft, 200, 255, 255, 255);
	sprintf(temp, "Graze: %d", graze);				//¿øºuº∆
	drawtext(temp, stateleft, 250, 255, 255, 255);

	if(state == 1){			//GAMEOVERµe≠±
		glColor3ub(0,0,0);
		glRectf(0, WINDOWY / 2 - 20, BG::range, WINDOWY / 2 + 30);
		drawtext("Game over!!!", BG::range / 3, WINDOWY / 2, 255, 255, 255);
		drawtext("Continue: Press enter.", BG::range / 3, WINDOWY / 2 + 20, 255, 255, 255);
	}
	glEnable(GL_TEXTURE_2D);

	int templife = player.get(LIFE);	//•Õ©Rº∆∂Kπœ
	glColor3ub(255,255, 255);
	glBindTexture(GL_TEXTURE_2D, bulletpic);
	glPushMatrix();
	glTranslatef(stateleft + 70, 80, 0.0f);
	for(i = 0; i < templife; ++i){
	glBegin(GL_QUADS);
		glTexCoord2f(0.75,0.25);	glVertex2f( 0.0f , 0.0f );
		glTexCoord2f(1,0.25);		glVertex2f( 20 , 0.0f );
		glTexCoord2f(1,0);			glVertex2f( 20 , 20 );
		glTexCoord2f(0.75,0);		glVertex2f( 0.0f , 20 );
	glEnd();
	(((i + 1) / 6 > 0) && ((i + 1) % 6 == 0))? glTranslatef(-125, 25, 0.0f)
											 : glTranslatef(25, 0, 0.0f);
	}
	glPopMatrix();

	int tempbomb = player.get(BOMBNUM);	//¨µºuº∆∂Kπœ
	glColor3ub(255,0, 0);
	glPushMatrix();
	glTranslatef(stateleft + 70, 130, 0.0f);
	for(i = 0; i < tempbomb; ++i){
	glBegin(GL_QUADS);
		glTexCoord2f(0.75,0.25);	glVertex2f( 0.0f , 0.0f );
		glTexCoord2f(1,0.25);		glVertex2f( 20 , 0.0f );
		glTexCoord2f(1,0);			glVertex2f( 20 , 20 );
		glTexCoord2f(0.75,0);		glVertex2f( 0.0f , 20 );
	glEnd();
	(((i + 1) / 6 > 0) && ((i + 1) % 6 == 0))? glTranslatef(-125, 25, 0.0f)
											 : glTranslatef(25, 0, 0.0f);
	}
	glPopMatrix();
	
	glColor3ub(255,	255, 255);				//©€µPøﬂ  øﬂARC
	glBindTexture(GL_TEXTURE_2D, facepic);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);	glVertex2f( BG::range , WINDOWY / 2);
		glTexCoord2f(1,1);	glVertex2f( WINDOWX , WINDOWY / 2);
		glTexCoord2f(1,0);	glVertex2f( WINDOWX , WINDOWY );
		glTexCoord2f(0,0);	glVertex2f( BG::range , WINDOWY );
	glEnd();

	if(state == 2){						//πL√ˆµe≠±
		glBindTexture(GL_TEXTURE_2D, winpic);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);	glVertex2f( 0 , 0);
			glTexCoord2f(1,1);	glVertex2f( BG::range , 0);
			glTexCoord2f(1,0);	glVertex2f( BG::range , WINDOWY );
			glTexCoord2f(0,0);	glVertex2f( 0 , WINDOWY );
		glEnd();
	}

	glEnable(GL_DEPTH_TEST);
}

void Game::act(int action){
	if(state == 0)
	switch(action){
	case FIRE:		pbulletnum += player.fire(pbullet);break;//¡‰ΩLπÅE≥∞ ß@
	case BOMB:		player.bomb();break;
	case POWERUP:   player.powerup(4, &grade);
	case MOVE_RIGHT:
	case MOVE_LEFT:	
	case MOVE_UP:	
	case MOVE_DOWN:	
	case SLOW_RIGHT:
	case SLOW_LEFT:	
	case SLOW_UP:	
	case SLOW_DOWN:	player.move(action);break;
	}
	if(state == 1  && action == ENTER){//±µ√ÅE
		grade = 0;
		graze = 0;
		state = 0;
		int i = 0;
		int count = ebulletnum;		//Æ¯•hµe≠±§lºu
		while(count){
		count -= ebullet[i].die();
		i++;
		}
		ebulletnum = 0;

		i = 0;						//≤£•Õ™´´~
		while(item[i].isdead() == false) i = (++i) % MAXITEM;
		item[i].init(BG::range / 4, 0, 0, 0, 3);
		++itemnum;
		while(item[i].isdead() == false) i = (++i) % MAXITEM;
		item[i].init(BG::range / 2, 0, 0, 0, 3);
		++itemnum;
		while(item[i].isdead() == false) i = (++i) % MAXITEM;
		item[i].init( 3 * BG::range / 4, 0, 0, 0, 3);
		++itemnum;
		player.goon();//±µ√ˆ™ÅEl≥]©w
	}

}

void Game::drawtext(char *str, int posx, int posy, int r, int g, int b){
	int len = strlen(str);
	glColor3ub(r,g,b);
	glRasterPos2i(posx,posy);	//µe¶r¶ÅEm
	for(int i = 0; i < len ; i++)//µe¶r
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

Game::~Game(){
	
}


Bullet::Bullet(){
	dead = true;
}

bool Bullet::isdead(){
	return dead;
}

int Bullet::dispaly(GLuint *texture){
	if(dead) return 0;

	glColor3ub(255,255,255);
    glBindTexture(GL_TEXTURE_2D, *texture);
	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	if(skin == 0 || skin == 1)		//±€¬‡∂Kπœ  •u¶≥¨Y®«≠n
		glRotated(angle, 0 ,0 ,1);

	glBegin(GL_QUADS);
		glTexCoord2f(pos.left,pos.up);		glVertex2f( -1 * drawx , -1 * drawy );
		glTexCoord2f(pos.right,pos.up);		glVertex2f( drawx , -1 * drawy );
		glTexCoord2f(pos.right,pos.down);	glVertex2f( drawx , drawy );
		glTexCoord2f(pos.left,pos.down);	glVertex2f( -1 * drawx , drawy );
	glEnd();
	glPopMatrix();

	return 1;
}

int Bullet::move(int *num, Player& player){
	if(dead) return 0;
	x += vx;
	y += vy;
	if(y < -1 * width / 2 || y > WINDOWY + width / 2 ||	//∂W•XΩd≥Ú¶€∑¿
		x < -1 * length / 2 || x > BG::range + length / 2){
		dead = true;
		(*num)--;
	}
	switch(mode){
	case 0: break;	//£∏ØÅElºu
	case 1:			//∞l¬‹ºu
		if(movecount == 0){
			if( x > player.get(POSX) )
				vx--;
			else
				vx++;
			if( y > player.get(POSY) )
				vy--;
			else
				vy++;
			movecount = 10;
			vchange = true;
		}
		movecount--;
		break;
	case 2:			//§lºuº≤¿´·§œºu
		if( x + vx >= BG::range  || x + vx <= 0){
			vx = -vx;
			if(vy == 0)
				vy = 1;
			vy = 2*vy;
			(x > BG::range / 2)? x = BG::range - length / 2 : x = width / 2;
			vchange = true;
		}
		break;
	case 3:			//¡Õ¶V§U©Œ§W
		if(movecount == 0){	
			(vx > 0)? --vx: (vx != 0)? ++vx: 1;
			movecount = 10;
			vchange = true;
		}
		(vy == 0)? vy = 1: 1;
		movecount--;
		break;
	case 4:	if(movecount == 0){	//≤æ∞ §@¨qÆ…∂°´·∫À∑«™±Æa
				vx = 0;
				vy = 0;
				vchange = true;
			}
			if(movecount == -5){
				int dx = player.get(POSX) - x;
				int dy = player.get(POSY) - y;
				if(dx != 0 && dy != 0){
					double a =  atan2(dx , dy);
					vx = (int)(speed * sin(a));
					vy = (int)(speed * cos(a));
				}else{
					if(dx == 0)
						(dy > 0)? vy = speed: vy = -1 * speed;
					else
						(dx > 0)? vx = speed: vx = -1 * speed;
				}
				vchange = true;
			}
			movecount--;
			break;
	}

	if(vchange && (skin == 0 || skin == 1))	//≥t´◊ßÅE‹™∫∏‹∫‚∂Kπœ®§´◊  •u¶≥¨Y®«≠n
		(vx !=0 && vy != 0)? angle = -1 * atan2(vx , vy) / M_PI * 180
					   : (vx == 0)? angle = 0: angle = -90;
	vchange = false;
	return 1;
}

void Bullet::init(int initx, int inity, int initvx, int initvy, int initskin, int initmode, int initspeed){
	x = initx;
	y = inity;
	vx = initvx;
	vy = initvy;
	speed = initspeed;
	skin = initskin;
	mode = initmode;
	movecount = 10;
	vchange = false;

	if(skin == 0 || skin == 1)
		(vx !=0 && vy != 0)? angle = -1 * atan2(vx , vy) / M_PI * 180
					   : (vx == 0)? angle = 0: angle = 90;

	dead = false;

	int row = (skin + 2) / 4;
	int col = (skin + 2) % 4;

	pos.down = 0.75 - row * 0.25;	//∂Kπœ¶ÅEm≥]©w
	pos.up = 1 - row * 0.25;
	pos.left = col * 0.25;
	pos.right = 0.25 + col * 0.25;

	switch(skin){	//∂KπœπÅEM§j§p
	case -2:length = WINDOWX / 16; width = WINDOWY / 10;break;
	case -1:length = WINDOWX / 35; width = WINDOWY / 15;break;
	case 0:length = WINDOWX / 50; width = WINDOWY / 25;break;
	case 1:length = WINDOWX / 50; width = WINDOWY / 25;break;
	case 2:length = WINDOWX / 10; width = length;break;
	case 3:length = WINDOWX / 30; width = length;break;
	case 4:length = WINDOWX / 15; width = length;break;
	case 5:length = WINDOWX / 20; width = length;break;
	case 6:length = WINDOWX / 12; width = length;break;
	default: length = WINDOWX / 20; width = length;break;
	}
	drawx = length / 2;
	drawy = width / 2;
}

void Bullet::hitenemy(Enemy enemy[MAXENEMY], int* grade, int *enemynum, Item item[MAXITEM], int *itemnum){
	if(dead) return;
	
	int up, down, left, right;
	up = y - width / 2;
	down = y + width / 2;
	left = x - length / 2;
	right = x + length / 2;

	bool hit[2] = {0};
	int eup, edown, eleft, eright;

	int i = 0;
	for(int j = 0; j < (*enemynum); j++){	//¶≥¶h§÷ºƒ§HßP¬_¶h§÷¶∏
		while(enemy[i].isdead() == true) i = (++i) % MAXBULLET;	//ß‰¨°µ€™∫
		eup = enemy[i].get(POSY) - enemy[i].get(WIDTH) / 2;
		edown = enemy[i].get(POSY) + enemy[i].get(WIDTH) / 2;
		eleft = enemy[i].get(POSX) - enemy[i].get(LENGTH) / 2;
		eright = enemy[i].get(POSX) + enemy[i].get(LENGTH) / 2;	
		
		if(x > enemy[i].get(POSX))		//XΩd≥ÅE
			(eright > left)? hit[0] = true: hit[0] = false;
		else
			(eleft < right)? hit[0] = true: hit[0] = false;
		
		if(y > enemy[i].get(POSY))		//YΩd≥ÅE
			(edown > up)? hit[1] = true: hit[1] = false;
		else
			(eup < down)? hit[1] = true: hit[1] = false;

		if(hit[0] && hit[1]){			//XY≥£§§ ßYØu™∫§§
			enemy[i].hurt(grade, skin + 3, item, itemnum, enemynum);
			++(*grade);
		}
		i = (++i) % MAXBULLET;
	}

}

void Bullet::hitplayer(Player& player, int *ebulletnum, Item item[MAXITEM], int *itemnum, int *grade, int *graze){
	if(dead) return;
	
	if(player.get(ISBOMB)){	//®œ•Œ¨µºu´h¶€∑¿
		dead = true;
		--(*ebulletnum);
		return;
	}

	int r = (length + width) / 4;

	int d = (x - player.get(POSX))*(x - player.get(POSX)) + 
		(y - player.get(POSY))*(y - player.get(POSY));

	if(d < (r + 10) * (r + 10)){	//¿øºußP¬_
		(*grade) += 10;
		++(*graze);
		SoundFunc(GRAZE, PLAY);
	}

	if(d < r * r){			//©R§§
		player.die(item, itemnum);
		dead = true;
		--(*ebulletnum);
	}
}

int Bullet::die(){
	dead = true;
	return 1;
}

Bullet::~Bullet(){

}

Enemy::Enemy(){
	length = WINDOWX / 16;
	width = WINDOWY / 10;
	dead = true;
	damage = false;
	firecount = 0;
}

bool Enemy::isdead(){
	return dead;
}

void Enemy::init(int data[], int posx, int posy){
	skin = data[0];
	itemtype = data[1];
	x = posx;
	y = posy;
	x_step = data[2];
	y_step = data[3];
	score = data[4];
	blood = data[5];
	bullet = data[6];
	type = data[7];
	mode = data[8];
	period = data[9];

	int row = skin / 4;
	int col = skin % 4;

	pos.down = 0.75 - row * 0.25;
	pos.up = 1 - row * 0.25;
	pos.left = col * 0.25;
	pos.right = 0.25 + col * 0.25;

	switch(skin){	//∂KπœπÅEM§j§p
	case 0:length = WINDOWX / 16; width = WINDOWY / 10;break;
	case 1:length = WINDOWX / 16; width = WINDOWY / 10;break;
	case 2:length = WINDOWX / 14; width = WINDOWY / 9;break;
	case 3:length = WINDOWX / 17; width = WINDOWY / 8;break;
	case 4:length = WINDOWX / 18; width = WINDOWY / 10;break;
	case 5:length = WINDOWX / 14; width = WINDOWY / 9;break;
	case 6:length = WINDOWX / 10; width = WINDOWY / 12;break;
	case 7:length = WINDOWX / 15; width = WINDOWY / 13;break;
	case 8:length = WINDOWX / 17; width = WINDOWY / 10;break;
	}

	dead = false;
	firecount = 0;
	theta = 0;
	switch(mode){	//≤æ∞ º“¶°πÅE≥∞±ØdÆ…∂°
	case 1:	staytime = 150; movecount = 50;break;
	default: staytime = 0; movecount = -1;break;
	}
}

int Enemy::dispaly(GLuint *texture){
	if(dead) return 0;

	float left, right;	//¶V•™©Œ¶V•k ßP¬_∂Kπœ§Ë¶V
	if(x_step >= 0){
		left = pos.left;
		right = pos.right;
	}else{
		left = pos.right;
		right = pos.left;
	}

	(damage)? glColor3ub(255,0,0): glColor3ub(255,255,255);
    glBindTexture(GL_TEXTURE_2D, *texture);
	glPushMatrix();
	glTranslatef(x - (length / 2), y - (width / 2), 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(left,pos.up);	glVertex2f( 0 , 0 );
		glTexCoord2f(right,pos.up);	glVertex2f( length , 0 );
		glTexCoord2f(right,pos.down);	glVertex2f( length , width );
		glTexCoord2f(left,pos.down);	glVertex2f( 0 , width );
	glEnd();
	glPopMatrix();

	damage = false;
	return 1;
}

int Enemy::move(int *num){
	if(dead) return 0;
	x += x_step;
	y += y_step;
	if(x < -1 * length / 2 || x > BG::range + length / 2 ||	//∂W•XΩd≥Ú¶€∑¿
	   y < -1 * width / 2 || y > WINDOWY + width / 2){
		dead = true;
		(*num)--;
	}
	switch(mode){
	case 0: break;	//™Ω™Ω®´
	case 1:	if(movecount == 0){	//≤æ∞ §@¨qÆ…∂°´ÅE ∞±§˚¿@¨qÆ…∂°  ¶A©π§W
				x_step = 0;
				y_step = 0;
				(staytime > 0)? --staytime: y_step = -5;
			}else		
				(staytime != 0)? --movecount: 1;
			break;
	case 2:	(y_step > 0)? --y_step: (y_step != 0)? ++y_step: 0;//¡Õ¶V•™©Œ•k
			break;
	}
	return 1;
}

int Enemy::get(int choice){
	switch(choice){
	case POSX: return x;
	case POSY: return y;
	case LENGTH: return length;
	case WIDTH: return width;
	}
	return -1;
}

void Enemy::hurt(int *grade, int power, Item item[MAXITEM], int *itemnum, int *num){
	if(dead) return;
	damage = true;
	blood -= power;		//®ÅEÀ
	int i = 0;
	if(blood <= 0){		//¶∫§`
		dead = true;
		SoundFunc(ENEMY_DEATH, PLAY);	//¶∫§`≠µÆƒ
		--(*num);
		(*grade) += score;	//•[§¿º∆
		while(item[i].isdead() == false) i = (++i) % MAXITEM;	//≤£•Õ™´´~
		item[i].init(x, y, 0, -5, itemtype);
		++(*itemnum);
	}
}

void Enemy::fire(Bullet ebullet[],Player& player, int data[][3], int *num){
	if(dead) return;
	firecount = (++firecount) % period;		//µoÆg∂°πj
	if(firecount!=0) return;
	
	if(mode == 1 && (x_step != 0 || y_step != 0))	//mode 1•≤∂∑∞±§˚¿~µoÆg§lºu
		return;
	int i = 0, j = 0;
	int px = 0, py = 0, pxy = 0;
	int randx = 0, randy = 0; 
	float sin45 = pow(0.5,0.5) * data[bullet][1];

	
	switch(type){
	case 0:	while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;			//™ΩΩu¶V§U´¨
			ebullet[i].init(x ,y , 0, data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);
			++(*num);
			SoundFunc(ENEMY_SHOT1, PLAY);
			break;
	case 1:																		//∫À∑«´¨
			px = player.get(POSX)-x;		//¶V∂qx = enemy_x - player_x
			py = player.get(POSY)-y;		//¶V∂qy = enemy_y - player_y
			pxy = pow( pow(px,2)+pow(py,2) , 0.5);
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, (px*data[bullet][1])/pxy, (py*data[bullet][1])/pxy, data[bullet][0], data[bullet][2], data[bullet][1]);	
			++(*num);
			SoundFunc(ENEMY_SHOT1, PLAY);
			break;
	case 2:																		//¥≤Æg´¨
			randx = rand()%21 - 10;			//randx range : 10 ~ -10
			randy = pow( 100-pow(randx,2), 0.5);		//randy = ( 1-randx^2 )^0.5
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			j = rand()%2;
			if(j == 1)
				ebullet[i].init( x, y, randx*data[bullet][1]/10,  randy*data[bullet][1]/10, data[bullet][0], data[bullet][2], data[bullet][1]);
			else
				ebullet[i].init( x, y, randx*data[bullet][1]/10, -randy*data[bullet][1]/10, data[bullet][0], data[bullet][2], data[bullet][1]);
			++(*num);
			SoundFunc(ENEMY_SHOT1, PLAY);
			break;
	case 3:																		//§K§ËÆg¿ª	
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, data[bullet][1], 0, data[bullet][0], data[bullet][2], data[bullet][1]);		//•k
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, sin45, sin45, data[bullet][0], data[bullet][2], data[bullet][1]);				//•k§U
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, 0, data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);		//§U
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, -1*sin45, sin45, data[bullet][0], data[bullet][2], data[bullet][1]);			//•™§U
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, -1*data[bullet][1], 0, data[bullet][0], data[bullet][2], data[bullet][1]);		//•™
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, -1*sin45, -1*sin45, data[bullet][0], data[bullet][2], data[bullet][1]);		//•™§W
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, 0, -1*data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);		//§W
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, sin45, -1*sin45, data[bullet][0], data[bullet][2], data[bullet][1]);			//•k§W
			(*num)+=8;
			SoundFunc(ENEMY_SHOT2, PLAY);
			break;
	case 4: for(j = 0;j<5;j++){
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;			//5-Way∂∂Æ…ƒ¡±€¬‡ºuπÅE
			ebullet[i].init( x, y, sin(theta)*data[bullet][1], cos(theta)*data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);
			theta += 5;
			(*num)+=1;
			}
			SoundFunc(ENEMY_SHOT2, PLAY);
			break;
	case 5: while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;			//∞fÆ…ƒ¡±€¬‡ºuπÅE
			ebullet[i].init( x, y, sin(theta)*data[bullet][1], cos(theta)*data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);
			theta -= 10;
			(*num)+=1;
			SoundFunc(ENEMY_SHOT3, PLAY);
			break;
	case 6: while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;			//§ª§ËÆg¿ª
			ebullet[i].init( x, y, sin(theta)*data[bullet][1], cos(theta)*data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;
			ebullet[i].init( x, y, -1*sin(theta)*data[bullet][1], cos(theta)*data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);
			if(theta >= 3)
				theta = -theta;
			theta += 1;
			(*num)+=2;
			SoundFunc(ENEMY_SHOT3, PLAY);
			break;
	case 7: for(j = 0;j<6;j++){
			while(ebullet[i].isdead() == false) i = (++i) % MAXBULLET;			//4-WAY ∂∂Æ…ƒ¡±€¬‡ºuπÅE
			ebullet[i].init( x, y, cos(theta)*data[bullet][1], data[bullet][1], data[bullet][0], data[bullet][2], data[bullet][1]);
			theta += 1;
			(*num)+=1;
			}
			SoundFunc(ENEMY_SHOT2, PLAY);
			break;
	}
}

Enemy::~Enemy(){

}

Item::Item(){
	dead = true;
	length = WINDOWX / 30;
	width = length;
	counter = 0;
}

bool Item::isdead(){
	return dead;
}

int Item::dispaly(GLuint *texture){
	if(dead) return 0;

	glColor3ub(255,255,255);
    glBindTexture(GL_TEXTURE_2D, *texture);
	glPushMatrix();
	glTranslatef(x - (length / 2), y - (width / 2), 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(pos.left,pos.up);		glVertex2f( 0 , 0 );
		glTexCoord2f(pos.right,pos.up);		glVertex2f( length , 0 );
		glTexCoord2f(pos.right,pos.down);	glVertex2f( length , width );
		glTexCoord2f(pos.left,pos.down);	glVertex2f( 0 , width );
	glEnd();
	glPopMatrix();

	return 1;
}

int Item::move(int *num){
	if(dead) return 0;

	x += vx;
	y += vy;
	
	if(counter == 0){
	(vx > 0)? --vx: (vx != 0)? ++vx: 1;
	(vy > 5)? --vy: (vy != 5)? ++vy: 1;
	}

	counter = (++counter) % 5;

	if(x > BG::range)	//∂W•XXΩd≥ÅEØd¶bµe≠±§§
		x = BG::range;
	if(x < 0)
		x = 0;

	if(y > WINDOWY + width / 2 ){	//∂W•XΩd≥Ú¶€∑¿
		dead = true;
		(*num)--;
	}
	return 1;
}

void Item::init(int initx, int inity, int initvx, int initvy, int initskin){
	x = initx;
	y = inity;
	vx = initvx;
	vy = initvy;
	skin = initskin;
	dead = false;
	counter = 0;

	pos.down = 0.5 - 0.5 * (skin / 2);
	pos.up = 1 - 0.5 * (skin / 2);
	pos.left = 0.5 * (skin % 2);
	pos.right = 0.5 + 0.5 * (skin % 2);
}

void Item::eated(Player& player, int* num, int *grade){
	if(dead) return;
	
	bool hit[2] = {0};
	int up, down, left, right;
	int pup, pdown, pleft, pright;

	up = y - width / 2;
	down = y + width / 2;
	left = x - length / 2;
	right = x + length / 2;

	pup = player.get(POSY) - player.get(WIDTH) / 2;
	pdown = player.get(POSY) + player.get(WIDTH) / 2;
	pleft = player.get(POSX) - player.get(LENGTH) / 2;
	pright = player.get(POSX) + player.get(LENGTH) / 2;	
		
	if(x > player.get(POSX))
		(pright > left)? hit[0] = true: hit[0] = false;
	else
		(pleft < right)? hit[0] = true: hit[0] = false;
		
	if(y > player.get(POSY))
		(pdown > up)? hit[1] = true: hit[1] = false;
	else
		(pup < down)? hit[1] = true: hit[1] = false;

	if(hit[0] && hit[1]){
		player.powerup(skin, grade);
		dead = true;
		--(*num);
	}
}

Item::~Item(){
	
}
