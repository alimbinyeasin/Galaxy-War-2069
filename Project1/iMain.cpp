#define _CRT_NONSTDC_NO_DEPRECATE
#include "iGraphics.h"
#include "bitmap_loader.h"
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

#define upperBGspeed 10
#define lowerBGspeed 10
#define numberofenemies 10
#define explosionEnemy_01 7
#define fire 50
#define missile01 50
#define MAX_HEALTH 100
#define bossexplosion 9


int instruction = 0;
int lifeCount = 1;
int shockcount = 0;
int lasercount = 0;
int x = 1000, y = 200, width, height; // x = mothership x-current coordinate , y = mothership y-current coordinate
bool musicon = true;
int enemy_01_x = 100, enemy_01_y = 145, ship_01_x = 100, ship_01_y = 200;
//bool life = true;
int index_user = 0;
int index_boss = 0;
int b = 0; // boss level changing index
int gx = 50, gy = 75; // machine gun of coordinate mothership 
int mx = 75, my = 100; //missile coordinate of mothership
int missile_x1 = 75, missile_y1 = 100;
int laser_x1 = 75, laser_y1 = 100;
int bossg_x = 50, bossg_y = 75; //boss gun
int boss_m = 75, bossm_y = 100; // boss missile
int enemies = 0;
int boss_level = 0; //states whether it will generate boss-1 or normal hoard enemies-0
int bossSpeed = 25;
int bossDirection = 1;
int mothershipHealth = MAX_HEALTH;
int boss01health = MAX_HEALTH + 50;

int bossState = 0; // states whether the boss will be of phase 1 or 2
int gameLevel = 1; //indicates the level of the game



//char bosspicture[1][20] = { "b1-1.png" };
char shockwave[10][30] = { "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", "Shockwave\\sw.png", };
char missile[10][30] = { "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png", "Missile\\Missile.png" };
char firing[10][30] = { "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png", "MachineGunFire\\shot2.png" };
char laserbeam[10][30] = { "Laserbeam\\tile000.png", "Laserbeam\\tile001.png", "Laserbeam\\tile002.png", "Laserbeam\\tile003.png", "Laserbeam\\tile004.png", "Laserbeam\\tile005.png", "Laserbeam\\tile006.png", "Laserbeam\\tile007.png", "Laserbeam\\tile007.png","Laserbeam\\tile007.png" };


char enemy_picture[10][20] = { "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png", "Enemy_ship\\e1.png" };
char enemy_picture02[10][20] = { "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png", "Enemy_ship\\e2.png" };
char enemy_picture03[10][20] = { "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png", "Enemy_ship\\e3.png" };
char enemy_picture04[10][20] = { "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png", "Enemy_ship\\e4.png" };
char enemy_picture05[10][20] = { "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png", "Enemy_ship\\e5.png" };

char enemy_01_explosion[7][25] = { "Explosion\\explosion1.png", "Explosion\\explosion2.png", "Explosion\\explosion3.png", "Explosion\\explosion4.png", "Explosion\\explosion5.png", "Explosion\\explosion6.png", "Explosion\\explosion7.png" };

char mainmenu[23] = { "Mainmenu\\MAINMENU.png" };
char buttons[10][40] = { "BUTTONS\\Play.png", "BUTTONS\\Story.png", "BUTTONS\\Credits.png","BUTTONS\\Highscore.png" "BUTTONS\\Exit.png" };

char enemyFire[10][30] = { "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png", "EnemyMachineGun\\shot1.png" };

char boss_firing[10][30] = { "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png", "MachineGunFire\\b.png" };
char boss_missile[10][30] = { "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png", "Missile\\m.png" };
char boss_laser[10][30] = { "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png", "Boss_lb\\new.png" };




//---------------------- mainmenu -----------------------
struct buttonCordinate{
	int butt_x;
	int butt_y;
}bCordinate[5];
int gameState = -1;


//--------------------- highscore --------------------------
int hs = 0;
int len = 0;
char str1[100], str2[100];
bool newscore = true;

struct hscore{
	char name[30];
	int score = 0;
}high_score[5];



void highscore(int n){
	hs=hs + n;
}
//in order to take input after a player finishes the game or dies
void drawTextBox()
{
	iSetColor(255, 255, 255);
	iText(width / 2 - 100, height / 2 + 225, "Enter name:",GLUT_BITMAP_HELVETICA_18);
	iSetColor(150, 150, 150);
	iRectangle(width/2-100, height/2+190, 250, 30);
	iSetColor(255, 255, 255);
	iText(width / 2 - 100, height / 2 + 190, str2, GLUT_BITMAP_HELVETICA_18);
	iSetColor(255, 255, 255);
	iText(width / 2 - 100, height / 2 + 170, "Your Score is:", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255, 255, 255);
	iText(width / 2 - 100, height / 2 + 150, "Your Score is:", GLUT_BITMAP_HELVETICA_18);
}
//will be added after a player dies or finishes the game
void newHighscore(){
	FILE *fp;
	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++){
		fscanf(fp, "%s %d\n", high_score[i].name, &high_score[i].score);
	}
	int t; // temp score for s
	char n[30];//temp name for s
	//might need to add a bool
	if (newscore){
		for (int i = 0; i < 4; i++)
		{
			if (high_score[i].score < hs)
			{
				high_score[5].score = hs;
				strcpy(high_score[5].name, str1);
				for (int j = 0; i < 5; i++)
				{
					for (int k = 5; k>j; k--)
					{
						if (high_score[k].score>high_score[k - 1].score)
						{ //sortin
							t = high_score[k - 1].score;
							high_score[k - 1].score = high_score[k].score;
							high_score[k].score = t;
							strcpy(n, high_score[k - 1].name);
							strcpy(high_score[k - 1].name, high_score[k].name);
							strcpy(high_score[k].name, n);
						}
					}
				}
				fp = fopen("Highscore\\Score.txt", "w");
				for (int i = 0; i < 4; i++)
				{
					fprintf(fp, "%s %d", high_score[i].name, &high_score[i].score);
					fclose(fp);
					newscore = false;
					break;
				}
			}
		}
		fclose(fp);
	}
}


// -----------  machine gun of mothership  -----------------------
struct machine_gun_s1{
	int gun_x;
	int gun_y;
	int gun_index;
	int gun_show;
};
machine_gun_s1 f01[fire];


void machinegun()
{
	// Check if any machine gun object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!f01[i].gun_show)
		{
			f01[i].gun_x = x + 12.5;
			f01[i].gun_y = y + 60;
			f01[i].gun_index = index_user % 10; // Repeatedly show the firing images
			f01[i].gun_show = true;
			f01[i].gun_index++; // Increment the firing image index for the next object
			break;
		}
	}
}


// ------------ missile of mothership -----------------
struct missile_mothership{
	int missile_x;
	int missile_y;
	int missile_index;
	bool missile_show;
};
missile_mothership m01[missile01];
void missileFire()
{
	// Check if any machine gun object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!m01[i].missile_show)
		{
			m01[i].missile_x = x + 9.5;
			m01[i].missile_y = y + 70;
			m01[i].missile_index = index_user % 10; // Repeatedly show the firing images
			m01[i].missile_show = true;
			m01[i].missile_index++; // Increment the firing image index for the next object
			break;
		}
	}
}


//----------------------Shock wave for mothership(level-2)------------------------
struct shockwave_mothership{
	int sw_x;
	int sw_y;
	int sw_index;
	bool sw_show;
};
shockwave_mothership sw01[missile01];
void shock_wave()
{
	// Check if any shockwave object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!sw01[i].sw_show)
		{
			sw01[i].sw_x = x + 9.5;
			sw01[i].sw_y = y + 70;
			sw01[i].sw_index = index_user % 10; // Repeatedly show the shockwave images
			sw01[i].sw_show = true;
			sw01[i].sw_index++; // Increment the shockwave image index for the next object
			break;
		}
	}
}


//-------------------new weapon for mothership(level-3)-----------------
struct laser_beam{
	int lb_x;
	int lb_y;
	int lb_index;
	bool lb_show;
};
laser_beam laser[missile01];
void laser_throw()
{
	// Check if any laserbeam object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!laser[i].lb_show)
		{
			laser[i].lb_x = x + 9.5;
			laser[i].lb_y = y + 70;
			laser[i].lb_index = index_user % 10; // Repeatedly show the laserbeam images
			laser[i].lb_show = true;
			laser[i].lb_index++; // Increment the laserbeam image index for the next object
			break;
		}
	}
}


//  --------------------  Hoard Enemy category -1   ----------------------------
struct e1{
	int e1_x;
	int e1_y;
	int e1_index;
	bool e1_show;
	int explosion_index;
};
e1 enemy[numberofenemies];
void setenemyVariables(){
	for (int i = 0; i < numberofenemies; i++)
	{
		enemy[i].e1_x = rand() % (width - 100);
		enemy[i].e1_y = height + rand() % (height - 100);
		enemy[i].e1_index = rand() % 10;
		enemy[i].e1_show = true;
	}
}
//---------------- enemy machinegun -------------------
struct enemyFireBullet {
	int bullet_x;
	int bullet_y;
	int bullet_index;
	bool bullet_show;
};
enemyFireBullet enemyBullet[fire];
int index_enemy = 0;
void enemyMFire() {
	for (int i = 0; i < fire; i++) {
		if (!enemyBullet[i].bullet_show) {
			//int randomEnemy = rand() % numberofenemies;
			enemyBullet[i].bullet_x = enemy[i].e1_x + enemy_01_x / 2;
			enemyBullet[i].bullet_y = enemy[i].e1_y;
			enemyBullet[i].bullet_index = index_enemy % 10;
			enemyBullet[i].bullet_show = true;
			enemyBullet[i].bullet_index++;
			break;
		}
	}
}



//--------------Boss struct---------------------
struct boss
{
	int boss_x;
	int boss_y;
	int boss_state = 0;
	int boss_index = 0;
	bool boss_show;
	int explosion_index;
};
boss b01[3];

void setBoss()
{

	b01[b].boss_x = width / 2;
	b01[b].boss_y = height - 300;
	b01[b].boss_show = true;
}



// ------------------Boss machine gun---------------
struct bossMachineGun {
	int gun_x;
	int gun_y;
	int gun_index;
	int gun_show;
};
bossMachineGun bossGun[fire];
void boss_machinegun()
{
	// Check if any machine gun object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!bossGun[i].gun_show)
		{
			bossGun[i].gun_x = b01[b].boss_x + 50;
			bossGun[i].gun_y = b01[b].boss_y - 5;
			bossGun[i].gun_index = index_boss % 10; // Repeatedly show the firing images
			bossGun[i].gun_show = true;
			bossGun[i].gun_index++; // Increment the firing image index for the next object
			break;
		}
	}
}


// -------------------Boss missiles-----------------
struct bossMissile {
	int missile_x;
	int missile_y;
	int missile_index;
	bool missile_show;
};
bossMissile bossMissiles[missile01];

void bossMissileFire()
{
	// Check if any missile object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!bossMissiles[i].missile_show)
		{
			bossMissiles[i].missile_x = b01[b].boss_x + 40;
			bossMissiles[i].missile_y = b01[b].boss_y - 20;
			bossMissiles[i].missile_index = index_boss % 10; // Repeatedly show the missile images
			bossMissiles[i].missile_show = true;
			bossMissiles[i].missile_index++; // Increment the missile image index for the next object
			break;
		}
	}
}

//------------Boos laserbeam-------------
struct bosslaserbeam {
	int laser_x;
	int laser_y;
	int laser_index;
	bool laser_show;
};
bosslaserbeam bosslaser[missile01];

void bosslaser_throw()
{
	// Check if any laserbeam object is not showing and create a new one
	for (int i = 0; i < fire; i++)
	{
		if (!bosslaser[i].laser_show)
		{
			bosslaser[i].laser_x = b01[b].boss_x + 40;
			bosslaser[i].laser_y = b01[b].boss_y - 20;
			bosslaser[i].laser_index = index_boss % 10; // Repeatedly show the laser images
			bosslaser[i].laser_show = true;
			bosslaser[i].laser_index++; // Increment the laser image index for the next object
			break;
		}
	}
}

void setBossVariables()
{
	for (int i = 0; i < fire; i++) {
		bossGun[i].gun_show = false;
		bossMissiles[i].missile_show = false;
		//bosslaser[i].laser_show = false;
	}
}

// --------------------   iDraw is called again and again   ------------------------
void iDraw()
{

	iClear();

	if (gameState == -1)
	{
		instruction = 0;
		iShowImage(0, 0, width, height, iLoadImage(mainmenu));
		for (int i = 0; i < 5; i++){
			iShowImage(bCordinate[i].butt_x, bCordinate[i].butt_y, 200, 100, iLoadImage(buttons[i]));
		}
	}
	else if (gameState == 0)
	{

		if (gameLevel == 1){
			iShowImage(0, 0, width, height, iLoadImage("Background//lvl1bg.png"));
			iShowImage(x, y, 75, 125, iLoadImage("Mothership\\ship_1.png")); // Mothership for level -1
		}
		else if (gameLevel == 2){
			iShowImage(0, 0, width, height, iLoadImage("Background//lvl2bg.png"));
			iShowImage(x, y, 75, 125, iLoadImage("Mothership\\ship_2.png"));
		}
		else if (gameLevel == 3){
			iShowImage(0, 0, width, height, iLoadImage("Background//lvl3bg.png"));
			iShowImage(x, y, 75, 125, iLoadImage("Mothership\\ship_3.png"));
		}

		//Enemy generation for e1
		if (boss_level == 0)
		{

			for (int i = 0; i < numberofenemies; i++)
			{
				if (enemy[i].e1_show)
				{
					if (enemy[i].e1_show && enemies <= 10)
					{
						iShowImage(enemy[i].e1_x, enemy[i].e1_y, 150, 150, iLoadImage(enemy_picture[enemy[i].e1_index]));

					}
					else if (enemy[i].e1_show && enemies >10 && enemies <= 20)
					{
						iShowImage(enemy[i].e1_x, enemy[i].e1_y, 150, 150, iLoadImage(enemy_picture02[enemy[i].e1_index]));

					}
					else if (enemy[i].e1_show && enemies > 20 && enemies <= 30)
					{
						iShowImage(enemy[i].e1_x, enemy[i].e1_y, 150, 150, iLoadImage(enemy_picture03[enemy[i].e1_index]));

					}
					else if (enemy[i].e1_show && enemies > 30 && enemies <= 40)
					{
						iShowImage(enemy[i].e1_x, enemy[i].e1_y, 150, 150, iLoadImage(enemy_picture04[enemy[i].e1_index]));

					}
					else if (enemy[i].e1_show && enemies > 40 && enemies <= 50)
					{
						iShowImage(enemy[i].e1_x, enemy[i].e1_y, 150, 150, iLoadImage(enemy_picture05[enemy[i].e1_index]));

					}
				}
				else
				{
					// Display explosion frames if the enemy is hidden
					if (enemy[i].explosion_index < explosionEnemy_01)
					{
						iShowImage(enemy[i].e1_x, enemy[i].e1_y, 100, 125, iLoadImage(enemy_01_explosion[enemy[i].explosion_index]));
						enemy[i].explosion_index++;
					}
				}
			}
			// Display enemy bullets
			for (int i = 0; i <= 10; i++)
			{
				if (enemyBullet[i].bullet_show)
				{
					iShowImage(enemyBullet[i].bullet_x, enemyBullet[i].bullet_y, 75, 100, iLoadImage(enemyFire[enemyBullet[i].bullet_index]));
				}
			}
			enemyMFire();
		}



		//--------------------Entry of boss image--------------------

		else if (boss_level == 1 && b01[b].boss_show)
		{
			if (boss01health <= MAX_HEALTH)
			{
				bossState = 1;
			}

			if (bossState == 0)
			{
				if (gameLevel == 1 && b01[b].boss_show){
					iShowImage(b01[b].boss_x, b01[b].boss_y, 175, 200, iLoadImage("Boss\\b1-1.png"));
				}
				if (gameLevel == 2 && b01[b].boss_show){
					iShowImage(b01[b].boss_x, b01[b].boss_y, 175, 200, iLoadImage("Boss\\b2-1.png"));
				}
				if (gameLevel == 3 && b01[b].boss_show){
					iShowImage(b01[b].boss_x, b01[b].boss_y, 175, 200, iLoadImage("Boss\\b3-1.png"));
				}

				// health bar for boss
				int healthBarWidthB = (boss01health * 2);
				int healthBarHeightB = 10;
				int healthBarXB = b01[b].boss_x - 50;
				int healthBarYB = b01[b].boss_y + 200;

				iSetColor(255, 0, 0);
				iFilledRectangle(healthBarXB, healthBarYB, MAX_HEALTH * 2, healthBarHeightB);

				iSetColor(0, 0, 255);
				iFilledRectangle(healthBarXB, healthBarYB, healthBarWidthB, healthBarHeightB);
				// Render boss machine gun images
				for (int i = 0; i < fire; i++) {
					if (i % 3 == 0)
					{

						if (bossGun[i].gun_show) {
							iShowImage(bossGun[i].gun_x, bossGun[i].gun_y, 50, 75, iLoadImage(boss_firing[bossGun[i].gun_index]));
						}
					}
				}
			}

			else if (bossState == 1)
			{
				if (gameLevel == 1 && b01[b].boss_show){
					iShowImage(b01[b].boss_x, b01[b].boss_y, 175, 200, iLoadImage("Boss\\b1-2.png"));
				}
				if (gameLevel == 2 && b01[b].boss_show){
					iShowImage(b01[b].boss_x, b01[b].boss_y, 175, 200, iLoadImage("Boss\\b2-2.png"));
				}
				if (gameLevel == 3 && b01[b].boss_show){
					iShowImage(b01[b].boss_x, b01[b].boss_y, 175, 200, iLoadImage("Boss\\b3-2.png"));
				}

				// health bar for boss
				int healthBarWidthB = (boss01health * 2);
				int healthBarHeightB = 10;
				int healthBarXB = b01[b].boss_x - 50;
				int healthBarYB = b01[b].boss_y + 200;

				iSetColor(255, 0, 0);
				iFilledRectangle(healthBarXB, healthBarYB, MAX_HEALTH * 2, healthBarHeightB);

				iSetColor(0, 0, 255);
				iFilledRectangle(healthBarXB, healthBarYB, healthBarWidthB, healthBarHeightB);
				// Render boss missiles

				for (int i = 0; i < missile01; i++) {
					if (i % 2 == 0)
					{
						if (bossMissiles[i].missile_show) {
							iShowImage(bossMissiles[i].missile_x, bossMissiles[i].missile_y, 75, 100, iLoadImage(boss_missile[bossMissiles[i].missile_index]));
						}
					}
					// Render boss laserbeams

					if (i % 5 == 0 && gameLevel==3)
					{
						if (bosslaser[i].laser_show) {
							iShowImage(bosslaser[i].laser_x, bosslaser[i].laser_y, 75, 100, iLoadImage(boss_laser[bosslaser[i].laser_index]));
							cout << "Laserbeam" << endl;
						}
					}
				}
			}
		}

		//laserbeam for mothership
		for (int i = 0; i < missile01; i++)
		{
			if (laser[i].lb_show)
			{
				iShowImage(laser[i].lb_x, laser[i].lb_y, 50, 75, iLoadImage(laserbeam[laser[i].lb_index]));
			}
		}

		// shockwave for mothership
		for (int i = 0; i < missile01; i++)
		{
			if (sw01[i].sw_show)
			{
				iShowImage(sw01[i].sw_x, sw01[i].sw_y, 75, 100, iLoadImage(shockwave[sw01[i].sw_index]));
			}
		}

		//missile for mothership
		for (int i = 0; i < missile01; i++)
		{
			if (m01[i].missile_show)
			{
				iShowImage(m01[i].missile_x, m01[i].missile_y, 75, 100, iLoadImage(missile[m01[i].missile_index]));
			}
		}

		//machine gun image for mothership
		for (int i = 0; i < fire; i++)
		{
			if (f01[i].gun_show)
			{
				iShowImage(f01[i].gun_x, f01[i].gun_y, 50, 75, iLoadImage(firing[f01[i].gun_index]));
			}
		}
	
		// health bar for mothership
		int healthBarWidth = (mothershipHealth * 2);
		int healthBarHeight = 10;
		int healthBarX = x - 60;
		int healthBarY = y - 20;

		iSetColor(255, 0, 0);
		iFilledRectangle(healthBarX, healthBarY, MAX_HEALTH * 2, healthBarHeight);

		iSetColor(0, 0, 255);
		iFilledRectangle(healthBarX, healthBarY, healthBarWidth, healthBarHeight);
	}

	else if (gameState == 1){
		iShowImage(0, 0, width, height, iLoadImage("Mainmenu\\Story.png"));
		if (instruction == 1){
			iShowImage(0, 0, width, height, iLoadImage("Mainmenu\\Instruction.png"));
		}
		
	}
	else if (gameState == 2){
		//credits needs to be added
		iShowImage(0, 0, width, height, iLoadImage("Mainmenu\\Credits.png"));
	}
	else if (gameState == 3){
		//highscore
		iShowImage(0, 0, width, height, iLoadImage("Mainmenu\\Highscore.png"));
		FILE *fp;
		fp = fopen("Highscore\\Score.txt", "r");
		if (fp == '\0'){
			cout << "FILE NOT FOUND" << endl;
		}
		char showName[5][30], showScore[5][5];
		for (int i = 0; i < 5; i++){
			fscanf(fp, "%s %d\n", high_score[i].name, &high_score[i].score);
		}
		for (int i = 0; i < 5; i++){
			sprintf(showName[i], "%s", high_score[i].name);
			sprintf(showScore[i],"%d", high_score[i].score);
			iText(100, 200, showName[i], GLUT_BITMAP_HELVETICA_18);
			iText(100, 210, showScore[i], GLUT_BITMAP_HELVETICA_18);
		}
		fclose(fp);
	}
	else if (gameState == 4){
		exit(1);
	}
	else if (gameState == 5){
		iShowImage(0, 0, width, height, iLoadImage("Mainmenu\\Gameover.png"));
		//after dying or game over input score
		drawTextBox();
		newHighscore();
	}
	
}
void iPassiveMouse(int x, int y)
{

}

void iMouseMove(int mx, int my)
{


}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON){
		for (int i = 0; i < 6; i++){
			if (mx >= bCordinate[i].butt_x && mx <= bCordinate[i].butt_x + 260 && my >= bCordinate[i].butt_y && my <= bCordinate[i].butt_y + 95){
				gameState = i;
			}
		}
	}
}

void iKeyboard(unsigned char key)
{
	if (gameState == 5){
		if (key == '\r'){
			gameState = -1;
		}
		else if (key >= 'a' && key < 'z' || key >= 'A' && key <= 'Z'){
			str2[len] = key;
			len++;
		}
	}
	if (key == 'w')
	{
		if (y < height - 200)
		{
			y += 65;
		}
	}
	else if (key == 'a')
	{
		if (x > 50)
		{
			x -= 65;
		}
	}
	else if (key == 's')
	{
		if (y > 150)
		{
			y -= 65;
		}
	}
	else if (key == 'd')
	{
		if (x < width - 125)
		{
			x += 65;
		}
	}
	else if (key == 'e')
	{
		gameState = -1;
	}
	else if (key == ' ')
	{
		if (enemies > 12)
		{
			missileFire();
		}
	}
	else if (key == 'z')
	{
		machinegun();
	}
	else if (key == 'q')
	{
		if ((gameLevel == 2 || gameLevel == 3) && enemies >15){
			shock_wave();
		}
	}
	else if (key == 'f')
	{
		if (gameLevel == 3 && enemies >15){
			laser_throw();
		}
	}
	else if (key == 'n'){
		instruction = 1;
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_DOWN)
	{
		if (musicon)
		{
			musicon = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			musicon = true;
			PlaySound("bgm1.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}

}
// ----------------------   Change is called from main function after every 10 milisecond ---------------------------------
void change()
{
	if (gameState == 0)
	{
		if (boss_level == 0)
		{
			for (int i = 0; i < numberofenemies; i++)
			{
				// Update enemy position and image index
				enemy[i].e1_index++;
				if (enemy[i].e1_index >= 10)
				{
					enemy[i].e1_index = 0;
				}
				enemy[i].e1_y -= 30;


				// Check collision with player's ship
				if (enemy[i].e1_show && (enemy[i].e1_x + enemy_01_x < x + ship_01_x) && (enemy[i].e1_x + enemy_01_x > x) && (enemy[i].e1_y + enemy_01_y < y + ship_01_y) && (enemy[i].e1_y + enemy_01_y  > y))
				{
					// Collision occurred, handle accordingly (e.g., game over, decrease player's health, etc.)
					enemy[i].e1_show = false;
					enemies++;
					mothershipHealth -= 5;
					enemy[i].explosion_index = 0; // to start the explosion animation from the begining
				}

				if (enemies == 30 && gameLevel == 1)//entry of boss-1 now
				{
					boss_level = 1;
					setBoss();
					setBossVariables();
					break;
				}

				if (enemies == 40 && gameLevel == 2)//entry of boss -2 now
				{
					boss_level = 1;
					setBoss();
					setBossVariables();
					break;
				}

				if (enemies == 50 && gameLevel == 3)//entry of boss-3 now
				{
					boss_level = 1;
					setBoss();
					setBossVariables();
					break;
				}
				// Check collision with bullets
				for (int j = 0; j < fire; j++)
				{
					if (enemy[i].e1_show)
					{
						if ((f01[j].gun_show && (f01[j].gun_x  < enemy[i].e1_x + enemy_01_x) && (f01[j].gun_x + gx > enemy[i].e1_x) && (f01[j].gun_y  < enemy[i].e1_y + enemy_01_y) && (f01[j].gun_y + gy > enemy[i].e1_y)) || (m01[j].missile_show && (m01[j].missile_x  < enemy[i].e1_x + enemy_01_x) && (m01[j].missile_x + missile_x1 > enemy[i].e1_x) && (m01[j].missile_y  < enemy[i].e1_y + enemy_01_y) && (m01[j].missile_y + missile_y1 > enemy[i].e1_y)) || (sw01[j].sw_show && (sw01[j].sw_x  < enemy[i].e1_x + 175) && (sw01[j].sw_x + mx>enemy[i].e1_x) && (sw01[j].sw_y < enemy[i].e1_y + 200) && (sw01[j].sw_y + my > enemy[i].e1_y)) || (laser[j].lb_show && (laser[j].lb_x  < enemy[i].e1_x + enemy_01_x) && (laser[j].lb_x + laser_x1 > enemy[i].e1_x) && (laser[j].lb_y  < enemy[i].e1_y + enemy_01_y) && (laser[j].lb_y + laser_y1 > enemy[i].e1_y)))
						{
							// Collision occurred with an enemy ship
							// Handle the collision (e.g., reduce enemy's health, destroy the enemy, etc.)
							enemy[i].e1_show = false; // Hide the enemy ship after it is hit
							f01[j].gun_show = false; // Hide the bullet after it hits an enemy
							m01[j].missile_show = false;
							sw01[j].sw_show = false;
							laser[j].lb_show = false;
							enemies++;
							enemy[i].explosion_index = 0;
							highscore(5);
						}
					}
				}

				// Check if enemy has reached the top of the screen
				if (enemy[i].e1_y <= 0)
				{
					enemy[i].e1_x = rand() % (width - 100);
					enemy[i].e1_y = height + rand() % (height - 100);
					enemy[i].e1_show = true;
				}
			}
			//enemy bullet
			for (int i = 0; i < fire; i++)
			{
				if (enemyBullet[i].bullet_show)
				{
					enemyBullet[i].bullet_index = index_enemy % 10;
					enemyBullet[i].bullet_y -= 50; // Move the bullet towards the mother ship

					// Check if the bullet collides with the mother ship
					if ((enemyBullet[i].bullet_x + gx < x + ship_01_x) && (enemyBullet[i].bullet_x + gx > x) && (enemyBullet[i].bullet_y + gy < y + ship_01_y) && (enemyBullet[i].bullet_y + gy > y))
					{
						enemyBullet[i].bullet_show = false; // Hide the bullet after collision
						mothershipHealth -= 2; //bullet hits ship decrease of health

					}
					// Check if the bullet has reached the bottom of the screen
					if (enemyBullet[i].bullet_y <= 0)
					{
						enemyBullet[i].bullet_show = false;
					}
				}
			}
			index_enemy++;
			if (index_enemy >= 10)
			{
				index_enemy = 0; // Reset the firing image index if it exceeds the number of images
			}
		}
		//-----------------Boss level 1 moving-------------------
		else if (boss_level == 1)
		{
			// Move the boss horizontally
			if (b01[b].boss_x <= 100 || b01[b].boss_x + 175 >= width - 100)
			{
				// Reverse direction when reaching screen boundaries
				bossDirection *= -1;
			}
			b01[b].boss_x += bossSpeed * bossDirection;
			boss_machinegun();
			bossMissileFire();
			if (gameLevel == 3){
				bosslaser_throw();
			}
			
			// Update machine gun positions
			for (int i = 0; i < fire; i++)
			{
				if (bossGun[i].gun_show)
				{
					bossGun[i].gun_index = index_boss % 10; // Cycle through firing images repeatedly
					bossGun[i].gun_y -= 50;
					if ((bossGun[i].gun_x + gx < x + ship_01_x) && (bossGun[i].gun_x + gx > x) && (bossGun[i].gun_y + gy < y + ship_01_y) && (bossGun[i].gun_y + gy > y))
					{
						bossGun[i].gun_show = false; // Hide the bullet after collision
						mothershipHealth -= 2; //bullet hits ship decrease of health

					}

					// Check if the machine gun has reached the bottom of the screen
					if (bossGun[i].gun_y <= 50)
					{
						bossGun[i].gun_show = false;
					}
				}
			}

			// update missile positions
			for (int i = 0; i < fire; i++)
			{
				if (bossMissiles[i].missile_show)
				{
					bossMissiles[i].missile_index = index_boss % 10; // Cycle through firing images repeatedly
					bossMissiles[i].missile_y -= 30;

					//Missile for boss, decrease the health of mothership
					if ((bossMissiles[i].missile_x + missile_x1 < x + ship_01_x) && (bossMissiles[i].missile_x + missile_x1 > x) && (bossMissiles[i].missile_y + missile_y1 < y + ship_01_y) && (bossMissiles[i].missile_y + missile_y1 > y))
					{
						bossMissiles[i].missile_show = false; // Hide the missile after collision
						mothershipHealth -= 5; //bullet hits ship decrease of health

					}
					// Check if the missile has reached the bottom of the screen
					if (bossMissiles[i].missile_y <= 50)
					{
						bossMissiles[i].missile_show = false;
					}
				}
			}

			//update laserbeam positions
			for (int i = 0; i < fire; i++)
			{
				if (bosslaser[i].laser_show)
				{
					bosslaser[i].laser_index = index_boss % 10; // Cycle through firing images repeatedly
					bosslaser[i].laser_y -= 30;

					//Missile for boss, decrease the health of mothership
					if ((bosslaser[i].laser_x + missile_x1 < x + ship_01_x) && (bosslaser[i].laser_x + missile_x1 > x) && (bosslaser[i].laser_y + missile_y1 < y + ship_01_y) && (bosslaser[i].laser_y + missile_y1 > y))
					{
						bosslaser[i].laser_show = false; // Hide the missile after collision
						mothershipHealth -= 5; //bullet hits ship decrease of health

					}
					// Check if the missile has reached the bottom of the screen
					if (bosslaser[i].laser_y <= 50)
					{
						bosslaser[i].laser_show = false;
					}
				}
			}


			// Check collision with bullets from mothership
			for (int j = 0; j < fire; j++)
			{
				if (b01[b].boss_show)
				{
					if ((f01[j].gun_show && (f01[j].gun_x + gx < b01[b].boss_x + 175) && (f01[j].gun_x + gx > b01[b].boss_x) && (f01[j].gun_y + gy < b01[b].boss_y + 200) && (f01[j].gun_y + gy > b01[b].boss_y)) || (m01[j].missile_show && (m01[j].missile_x + missile_x1 < b01[b].boss_x + 175) && (m01[j].missile_x + missile_x1 > b01[b].boss_x) && (m01[j].missile_y + missile_y1 < b01[b].boss_y + 200) && (m01[j].missile_y + missile_y1 > b01[b].boss_y)))
					{
						f01[j].gun_show = false; // Hide the bullet after it hits an enemy
						m01[j].missile_show = false;
						boss01health -= 5;
					}
				}
				if ((sw01[j].sw_show && (sw01[j].sw_x + mx < b01[b].boss_x + 175) && sw01[j].sw_x + mx>b01[b].boss_x) && (sw01[j].sw_y + my < b01[b].boss_y + 200) && (sw01[j].sw_y + my > b01[b].boss_y)){
					sw01[j].sw_index = false;
					boss01health -= 10;
				}
				if (laser[j].lb_show && (laser[j].lb_x  < b01[b].boss_x + 175) && (laser[j].lb_x + laser_x1 > b01[b].boss_x) && (laser[j].lb_y  < b01[b].boss_y + 200) && (laser[j].lb_y + laser_y1 > b01[b].boss_y))
				{
					laser[j].lb_show = false;
					boss01health -= 10;
				}
			}
			// Increment the firing image index for the next iteration
			index_boss++;
			if (index_boss >= 10)
			{
				index_boss = 0; // Reset the firing image index if it exceeds the number of images
			}
			if (boss01health <= 0)
			{
				if (gameLevel == 1)
				{
					b01[b].boss_show = false; //boss 1 is dead
					gameLevel = 2; //level updated
					boss_level = 0; // again enemies are generated
					gameState = 0; //hudai mayb
					enemies = 0; // enemies count set to 0
					b = 1;
					boss01health = MAX_HEALTH + 70;
					bossState = 0;
					mothershipHealth = MAX_HEALTH;
					highscore(20);
				}
				else if (gameLevel == 2)
				{
					b01[b].boss_show = false; //boss 2 is dead
					gameLevel = 3; //level updated
					boss_level = 0; // again enemies are generated
					gameState = 0; //hudai mayb
					enemies = 0; // enemies count set to 0
					b = 2;
					boss01health = MAX_HEALTH + 100;
					bossState = 0;
					mothershipHealth = MAX_HEALTH;
					highscore(40);
				}
				else if (gameLevel == 3)
				{
					highscore(60);
					gameState =2;
				}
			}
		}




		// Update machine gun positions
		for (int i = 0; i < fire; i++)
		{
			if (f01[i].gun_show)
			{
				f01[i].gun_index = index_user % 10; // Cycle through firing images repeatedly
				f01[i].gun_y += 50;

				// Check if the machine gun has reached the top of the screen
				if (f01[i].gun_y >= height - 100)
				{
					f01[i].gun_show = false;
				}
			}
		}

		// update missile positions
		for (int i = 0; i < fire; i++)
		{
			if (m01[i].missile_show)
			{
				m01[i].missile_index = index_user % 10; // Cycle through firing images repeatedly
				m01[i].missile_y += 30;

				// Check if the missile has reached the top of the screen
				if (m01[i].missile_y >= height - 100)
				{
					m01[i].missile_show = false;
				}
			}
		}

		// update shockwave positions
		for (int i = 0; i < missile01; i++)
		{
			if (sw01[i].sw_show)
			{
				sw01[i].sw_index = index_user % 10; // Cycle through firing images repeatedly
				sw01[i].sw_y += 30;

				// Check if the missile has reached the top of the screen
				if (sw01[i].sw_y >= height - 100)
				{
					sw01[i].sw_show = false;
				}
			}
		}

		// update laserbeam positions
		for (int i = 0; i < missile01; i++)
		{
			if (laser[i].lb_show)
			{
				laser[i].lb_index = index_user % 10; // Cycle through firing images repeatedly
				laser[i].lb_y += 30;

				// Check if the missile has reached the top of the screen
				if (laser[i].lb_y >= height - 100)
				{
					laser[i].lb_show = false;
				}
			}
		}

		// Increment the firing image index for the next iteration
		index_user++;
		if (index_user >= 10)
		{
			index_user = 0; // Reset the firing image index if it exceeds the number of images
		}
	}


	if (mothershipHealth <= 0)
	{
		lifeCount=lifeCount-1;
		if (lifeCount<=0)
		{
			gameState = 5;
		}
		mothershipHealth = MAX_HEALTH;
	}
}


int main()
{
	HWND desktopHandle = GetDesktopWindow();
	// Get the screen dimensions

	RECT desktopRect;
	GetClientRect(desktopHandle, &desktopRect);

	// Calculate the width and height
	width = desktopRect.right;
	height = desktopRect.bottom;
	int flag = 100;
	for (int i = 4; i >= 0; i--)
	{
		bCordinate[i].butt_x = width / 2 - 100;
		bCordinate[i].butt_y = flag;
		flag += 150;
	}

	setenemyVariables();
	iSetTimer(10, change);

	//iSetTimer(1000, enemyMFire);
	if (musicon)
	{
		PlaySound("bgm1.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iInitialize(width, height, "Galaxy War 2069");

	iStart();

	return 0;
}