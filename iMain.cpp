#include "iGraphics.h"
#include "bitmap_loader.h"
#include <iostream>
using namespace std;


#define numberofenemies 20

int x = 1000, y = 200, width, height;
bool musicon = true;
int ex = 100, ey = 145, sx = 100, sy = 200;



char enemy_picture[10][20] = { "e1.png","e1.png","e1.png","e1.png","e1.png","e1.png","e1.png","e1.png","e1.png","e1.png" };


struct e1{
	int e1_x;
	int e1_y;
	int e1_index;
	bool e1_show;
};

e1 enemy[numberofenemies];



void enemyMovement(){
	for (int i = 0; i < numberofenemies; i++){
		if (enemy[i].e1_show)
		{
			iShowImage(enemy[i].e1_x, enemy[i].e1_y, 150, 200, iLoadImage(enemy_picture[enemy[i].e1_index]));	
		}
	}
}


void setenemyVariables(){
	for (int i = 0; i < numberofenemies; i++)
	{
		enemy[i].e1_x = rand() % (width-100);
		enemy[i].e1_y = height + rand() % (height-100);
		enemy[i].e1_index = rand() % 10;
		enemy[i].e1_show = true;
	}
}



void iDraw()
{
	
	iClear();
	
	iShowImage(0,0,width, height, iLoadImage("bg1.png"));
	iShowImage(x , y , 75, 125, iLoadImage("ship_1.png"));
	enemyMovement();
	
}



void iPassiveMouse(int x, int y)
{

}

void iMouseMove(int mx, int my)
{
	
	
}

void iMouse(int button, int state, int mx, int my)
{
	
}


void iKeyboard(unsigned char key)
{
	if (key == 'w')
	{
		if (y < height-200)
		{
			y += 65;
		}
	}
	else if (key == 'a')
	{
		if (x > 0)
		{
			x -= 65;
		}
	}
	else if (key == 's')
	{
		if (y > 0)
		{
			y -= 65;
		}
	}
	else if (key == 'd')
	{
		if (x < width - 100)
		{
			x += 65;
		}
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


void change()
{
	for (int i = 0; i < numberofenemies; i++)
	{
		// Update enemy position and image index
		enemy[i].e1_index++;
		if (enemy[i].e1_index >= 10)
		{
			enemy[i].e1_index = 0;
		}
		enemy[i].e1_y -= 20;

		// Check collision with player's ship
		if (enemy[i].e1_show &&
			(enemy[i].e1_x + ex < x + sx) && (enemy[i].e1_x + ex + 100 > x) &&
			(enemy[i].e1_y + ey < y + sy) && (enemy[i].e1_y + ey + 145 > y))
		{
			// Collision occurred, handle accordingly (e.g., game over, decrease player's health, etc.)
			// For now, let's hide the enemy
			enemy[i].e1_show = false;
		}

		// Check if enemy has reached the top of the screen
		if (enemy[i].e1_y <= 0)
		{
			enemy[i].e1_x = rand() % (width - 100);
			enemy[i].e1_y = height + rand() % (height - 100);
			enemy[i].e1_show = true;
		}
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

	setenemyVariables();

	iSetTimer(10,change);

	if (musicon)
	{
		PlaySound("bgm1.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iInitialize(width, height, "Galaxy War 2069");
	
	iStart(); 
	
	return 0;
}


