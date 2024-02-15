#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
using namespace std;
int score = 0, scorecolor = GREEN;

class balloon{
	public:
		int x, y, color, speed;
		char character;
		balloon(int X, int Y, int c, char C)
		{
			x = X;
			y = Y;
			color = c;
			character = C;
			speed = (rand() % 3) + 2;
		}
		void Reset()
		{
			y = (rand() % 200) + 920;
			character = (rand() % 26) + 97;
			color = (rand() % 14) + 1;
			speed = (rand() % 3) + 2;
		}
		void Draww()
		{
			setcolor(color);
			circle(x, y, 50);
			setfillstyle(SOLID_FILL, color);
			floodfill(x, y + 48, color);
			char C[1];
			sprintf(C, "%c", character);
			setcolor(WHITE);
			outtextxy(x - 10, y - 10, C);
			y -= speed;
			if(y <= -50)
			{
				Reset();
				score--;
				scorecolor = RED;
			}
		}
};
vector<balloon> B;

class destroy{
	public:
	int x, y, color, clock = 0;
	destroy(int X, int Y, int C)
	{
		x = X;
		y = Y;
		color = C;
	}
	void Draww()
	{
		setcolor(color);
		setfillstyle(SOLID_FILL, color);
		circle(x + 25 + clock, y - 25 - clock, 12 - clock);
		floodfill(x + 25 + clock, y - 25 - clock, color);
		circle(x + 25 + clock, y + 25 + clock, 12 - clock);
		floodfill(x + 25 + clock, y + 25 + clock, color);
		circle(x - 25 - clock, y - 25 - clock, 12 - clock);
		floodfill(x - 25 - clock, y - 25 - clock, color);
		circle(x - 25 - clock, y + 25 + clock, 12 - clock);
		floodfill(x - 25 - clock, y + 25 + clock, color);
		clock++;
	}
};
list<destroy*> des;
list<destroy*> :: iterator iter;

int main(int argc, char** argv)
{
	initwindow(1920, 1080, "Button Press", -3, -3, true, true);
	srand(time(NULL));
	for(int i = 0; i < 5; i++)
	{
		int y = (rand() % 370) + 500;
		int C = (rand() % 26) + 97;
		int c = (rand() % 14) + 1;
		balloon temp(100 + i*300, y, c, C);
		B.push_back(temp);
	}
	int page = 0;
	setactivepage(0);
	setvisualpage(0);
	settextstyle(0, 0, 5);
	outtextxy(500, 200, "Button Press");
	settextstyle(0, 0, 0);
	outtextxy(650, 400, "Press Any Key");
	outtextxy(1200, 600, "Created by - Atul Raj");
	outtextxy(1200, 650, "21JE0195");
	outtextxy(1200, 700, "IIT(ISM)");
	outtextxy(1200, 750, "(c) Copyright");
	settextstyle(0, 0, 4);
	getch();
	cleardevice();
	outtextxy(750, 400, "3");
	delay(1000);
	outtextxy(750, 400, "2");
	delay(1000);
	outtextxy(750, 400, "1");
	delay(1000);
	while(1)
	{
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		
		setcolor(scorecolor);
		char S[20];
		sprintf(S, "%d", score);
		outtextxy(1200, 50, "Score : ");
		outtextxy(1450, 50, S);
		
		setfillstyle(SOLID_FILL, WHITE);
		floodfill(1, 1, scorecolor);
		for(int i = 0; i < 5; i++)
			B[i].Draww();
		if(kbhit())
		{
			int test = 0;
			char c = getch();
			for(int i = 0; i < 5; i++)
			{
				if(B[i].character == c)
				{
					destroy* temp = new destroy(B[i].x, B[i].y, B[i].color);
					des.push_back(temp);
					test = 1;
					score++;
					scorecolor = GREEN;
					B[i].Reset();
					break;
				}
			}
			if(!test)
			{
				scorecolor = RED;
				score--;
			}
		}
		for(iter = des.begin(); iter != des.end(); iter++)
		{
			(*iter)->Draww();
			if((*iter)->clock == 11)
			{
				delete (*iter);
				des.pop_front();
			}
		}
		if(score < 0)
			score = 0;
		
		page = 1 - page;
		delay(1);
	}
	return 0;
}
