//R.A.T_Core.cpp
//Tech Lead: Chen Gengru
//Coder: Tang Bolong, Yang Yifei, Xie Zhaochen
//updated on 2019-3-21
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
using namespace std;

//����Windows Multimedia API
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

//ȫ�ֱ���
#define Height 480//�����߶�
#define Width 640//�������
#define PI 3.14159//Բ����

int mouse_x;                 //�����Ͻ�Ϊ��㣬x
int mouse_y;                 //ͬ�ϣ�y
int l;   //����
int mouse_height;            //�����²�yֵ 
int mouse_width;             //�����Ҳ�xֵ
int vehicle_x, vehicle_y, vehicle_right, vehicle_bottom;   //��������
int score;//����
int safe;//�����Ƿ�ȫ`
int vehicle_ok;
int hp;//����Ѫ��
int iDirection;            //�����ͷ����
int target = 100;          //�׶���Ŀ�����������÷�����������б仯��
int gameStatus = 0;        //��ʾ��Ϸ״̬��0Ϊ��ʼ���棬1Ϊ������Ϸ��2Ϊ��Ϸ������3Ϊ��Ϸ��ͣ
int musicswitch = 1;       //��Ч����
int trap_x, trap_y;        //�������ĺ�������
int trap_r = 25;                //����뾶
int trapEnd_x, trapEnd_y;  //����ĩ�˺�������
float trapAngle = PI * 2;  //ָ���Ӧ�ĽǶ�
int cooling;               //��ȴʱ��


int road[2][6] = { {0,0,0,0,0,0}, {-200,-200,-200,480,480,480} };//�����������λ��
IMAGE start[1], background, background2, vehicle_10, vehicle_20, vehicle_30, vehicle_40,
vehicle_50, vehicle_1, vehicle_2, vehicle_3, vehicle_4, vehicle_5, mouse_tail_a, mouse_tail_d,
mouse_tail_s, mouse_tail_w, mouse_a, mouse_w, mouse_d, mouse_s, zhe_a, zhe_w,
zhe_d, zhe_s, hp_1, hp_2, hp_3, continuebg, clstart, clcontinue, clhelp, clmusic, clquit,
startbg, pmostart, pmostore, pmomusic, pmorank, pmoinfo, conbg, conpmoinfo, conpmoagain, conpmocon, conpmoback, conpmomusic,
crack_1, crack_1_mask, crack_2, crack_2_mask, crack_3, crack_3_mask, mouse1_a, mouse1_d, mouse1_w, mouse1_s,
explode, explode_mask, store_0, store_1, store_2, store_3, mute0, mute1;


struct Vehicle//��������
{
	int speed;//�����ٶ�
	int condition;//����λ��
}vehicle[6] = {
	{0, 0},
	{3, 0},//���г�
	{10, 0},//С�γ�
	{8, 0},//��ͳ�
	{6, 0},//Ħ�г�
	{15, 0}//�Ȼ���
};
void pausemenu();          //��ͣ����
void Login();              //��ʼ����
void imageLoad();          //����ͼƬ
void soundVehicle(int);    //��������
void showVehicle1(int, int, int);                  //�����ӡ����
void showVehicle2(int, int, int);                  //�����ӡ����
void startup();             //���ݳ�ʼ��
void showmouse(int);        //����ת��Ĳ�ͬ��ӡ��ͬ����
void show();                //��ʾ����
void updateWithoutInput();  //���û��޹ص�����
void updateWithInput();     //���û��йص�����
void store();

void transparentimage(int x, int y, IMAGE *srcimg, IMAGE *maskimg)
{
	putimage(x, y, maskimg, SRCAND);
	putimage(x, y, srcimg, SRCPAINT);
}


void showVehicle1(int x, int y, int num)//�����ӡ����
{
	switch (num)       //��ͬ����ֵ��Ӧ��ӡ��ͬ����ĳ���
	{
	case 1:
		putimage(x + 10, y, &vehicle_1);
		break;
	case 2:
		putimage(x, y, &vehicle_2);
		break;
	case 3:
		putimage(x, y, &vehicle_3);
		break;
	case 4:
		putimage(x, y, &vehicle_4);
		break;
	case 5:
		putimage(x, y, &vehicle_5);
		break;
	}
}

void showVehicle2(int x, int y, int num)//�����ӡ����
{
	switch (num)
	{
	case 1:
		putimage(x + 10, y, &vehicle_10);
		break;
	case 2:
		putimage(x, y, &vehicle_20);
		break;
	case 3:
		putimage(x, y, &vehicle_30);
		break;
	case 4:
		putimage(x, y, &vehicle_40);
		break;
	case 5:
		putimage(x, y, &vehicle_50);
		break;
	}
}

void startup()//��Ϸ��ʼ��
{
	initgraph(Width, Height);//���廭���ߴ�
	imageLoad();//����ͼ��
	while (1)
	{
		Login();
		if (gameStatus == 1)
		{
			break;
		}
	}

	mciSendString("close start", NULL, 0, NULL);
	mciSendString(_T("open .\\start\\start.mp3 alias start"), NULL, 0, NULL);//����Ч
	mciSendString("play start", NULL, 0, NULL);//���β���

	iDirection = 1;
	mouse_x = Width / 2;//��ʼ������λ��
	mouse_y = Height / 2;

	mouse_height = Height / 2 + 40;//��ʼ������߽�
	mouse_width = Width / 2 + 70;
	safe = 1;//��ʼ������ȫֵ
	vehicle_ok = 1;
	hp = 580;//��ʼ������Ѫ��
	cooling = 580;
	score = 0;

	trap_x = -400;
	trap_y = -400;//��ʼ�������������

	BeginBatchDraw();

	
	mciSendString(_T("close menumusic"), NULL, 0, NULL);
	mciSendString(_T("open .\\default_theme.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);//ѭ������
}

void showmouse(int Direction)
{
	switch (Direction)
	{
	case 1:
	{
		if (score < 10)
		transparentimage(mouse_x, mouse_y, &mouse_a, &zhe_a);
		else 
			transparentimage(mouse_x, mouse_y, &mouse1_a, &zhe_a);
		break;
	}
	case 2:
	{
		if (score < 10)
			transparentimage(mouse_x, mouse_y, &mouse_d, &zhe_d);
		else
			transparentimage(mouse_x, mouse_y, &mouse1_d, &zhe_d);
		break;
	}
	case 3:
	{
		if (score < 10)
			transparentimage(mouse_x, mouse_y, &mouse_w, &zhe_w);
		else
			transparentimage(mouse_x, mouse_y, &mouse1_w, &zhe_w);
		break;
	}
	case 4:
	{
		if (score < 10)
			transparentimage(mouse_x, mouse_y, &mouse_s, &zhe_s);
		else
			transparentimage(mouse_x, mouse_y, &mouse1_s, &zhe_s);
		break;
	}
	}
}

void show()                     //��ʾ����
{
	while (gameStatus == 3)
		pausemenu();

	putimage(0, 0, &background);
	putimage(580, 0, &background2);
	showmouse(iDirection);
	settextcolor(BLACK);
	char s[5];
	settextstyle(30, 20, _T("Segoe Script"));
	setbkmode(TRANSPARENT);
	sprintf_s(s, "%d", score);
	outtextxy(590, 200, s);
	char t[5];
	if (score <= 100) {
		settextstyle(30, 15, _T("Segoe Script"));
		setbkmode(TRANSPARENT);
		sprintf_s(t, "%d", target);
		outtextxy(580, 390, t);
	}
	else if (100 < score <= 500)
	{
		settextstyle(30, 15, _T("Segoe Script"));
		setbkmode(TRANSPARENT);
		sprintf_s(t, "%d", target + 400);
		outtextxy(580, 390, t);

	}
	else
	{
		settextstyle(30, 15, _T("Segoe Script"));
		setbkmode(TRANSPARENT);
		sprintf_s(t, "%d", target + 900);
		outtextxy(580, 390, t);
	}

	float clock;

	if (trapAngle <= 2 * PI)
	{
		setlinestyle(PS_SOLID, 2);
		setcolor(BLUE);
		setfillcolor(BLUE);
		fillcircle(trap_x, trap_y, trap_r);
		setcolor(YELLOW);
		for (clock = 0; clock <= trapAngle; clock += 0.05)
		{
			trapEnd_x = trap_x + (trap_r + 1) * sin(clock);
			trapEnd_y = trap_y - (trap_r + 1) * cos(clock);
			line(trap_x, trap_y, trapEnd_x, trapEnd_y);
		}
		trapAngle += PI / 100;
	}
}


void updateWithoutInput()//���û��޹ص�����
{
	if (safe == 1)
	{
		if (hp <= 580)
		{
			hp++;
		}

		if (cooling <= 580)
		{
			cooling += 2;
		}

		int i, j;
		float k;
		for (i = 0; i < 6; i++)
		{
			if ((road[0][i] == 0) && ((road[0][1] + road[0][2] + road[0][3] + road[0][4] + road[0][5] + road[0][0]) <= 12))
			{
				k = (rand() / 32767.0);
				if (k)
				{
					road[0][i] = (rand() % 6);
					soundVehicle(road[0][i]);
				}
			}
		}

		for (j = 0; j < 6; j++)//���Ƴ����˶��ʹ�ӡ
		{
			if (j < 3)//���϶���
			{
				if (road[0][j] != 0)//�ж��Ƿ��г�
				{
					if (j == 4 && (iDirection == 1 || iDirection == 2) && (abs((mouse_width - 20 - j * 100 - 20 - 40)) <= 85) && (abs((mouse_y + 20 - road[1][j] - 75)) <= 145))
					{
						hp -= 8;
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
						
					}
					else if (j == 4 && (iDirection == 3 || iDirection == 4) && (abs(mouse_x + 15 - j * 100 - 20 - 40)) <= 60 && (abs((mouse_y + 20 - road[1][j] - 75)) <= 170))
					{
						hp -= 8;
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if ((iDirection == 1 || iDirection == 2) && (abs((mouse_width - 20 - j * 100 - 20 - 40)) <= 85) && (abs((mouse_y + 20 - road[1][j] - 75)) <= 95))
					{
						hp -= 8;

						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if ((iDirection == 3 || iDirection == 4) && (abs(mouse_x + 15 - j * 100 - 20 - 40)) <= 60 && (abs((mouse_y + 20 - road[1][j] - 75)) <= 120))
					{
						hp -= 8;

						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}

					if ((iDirection == 1 || iDirection == 2) && (abs(mouse_x + 45 - trap_x - 25) <= 68) && abs(mouse_y + 20 - trap_x - 25) <= 43)
					{
						hp -= 9;
						if (hp <= 0)
						{
							trapAngle = 2 * PI;
							trap_x = -400;
							trap_y = -400;
						}
					}
					else if ((iDirection == 3 || iDirection == 4) && (abs(mouse_x + 20 - trap_x - 25) <= 43) && abs(mouse_y + 45 - trap_x - 25) <= 68)
					{
						hp -= 9;
						if(hp <= 0)
						{
							trapAngle = 2 * PI;
							trap_x = -400;
							trap_y = -400;
						}
					}

					if (hp <= 0)
					{
						safe = 0;
					}
					showVehicle1(j * 100, road[1][j], road[0][j]);
					//if(road[0][j]==4&&)

					if (road[1][j] <= Height)//�жϳ��Ƿ��ӳ�����
					{
						road[1][j] += vehicle[road[0][j]].speed;
					}
                    else//��ʼ������
					{
						score++;
						road[1][j] = -250;
						road[0][j] = 0;
					}
					if (j == 4 && (abs((trap_x - j * 100 - 40)) <= 65) && (abs((trap_y + 18 - road[1][j] - 125)) <= 148))
					{
						score += 2;
						road[1][j] = -250;
						road[0][j] = 0;
						trapAngle = 2 * PI;
						trap_x = -400;
						trap_y = -400;
						transparentimage(j * 100 + 40, road[1][j] + 125, &explode, &explode_mask);
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);

					}
					else if (j == 6 && (abs((trap_x - j * 100 - 40)) <= 65) && (abs((trap_y + 18 - road[1][j] - 75)) <= 100))
					{
						score -= 10;
						road[1][j] = -250;
						road[0][j] = 0;
						trapAngle = 2 * PI;
						trap_x = -400;
						trap_y = -400;
						transparentimage(j * 100 + 40, road[1][j] + 75, &explode, &explode_mask);
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if(j != 4 && j != 6 && (abs((trap_x - j * 100 - 40)) <= 65) && (abs((trap_y + 18 - road[1][j] - 75)) <= 100))
					{
						score += 2;
						road[1][j] = -250;
						road[0][j] = 0;
						trapAngle = 2 * PI;
						trap_x = -400;
						trap_y = -400;
						transparentimage(j * 100 + 40, road[1][j] + 75, &explode, &explode_mask);
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					

				}
			}
			else//���¶���
			{
				if (road[0][j] != 0)
				{
					if (j == 4 && (iDirection == 1 || iDirection == 2) && (abs((mouse_width - 20 - j * 100 - 20 - 40)) <= 85) && (abs((mouse_y + 20 - road[1][j] - 75)) <= 145))
					{
						hp -= 8;

						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);

					}
					else if (j == 4 && (iDirection == 3 || iDirection == 4) && (abs(mouse_x + 15 - j * 100 - 20 - 40)) <= 60 && (abs((mouse_y + 20 - road[1][j] - 75)) <= 170))
					{
						hp -= 8;

						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if ((iDirection == 1 || iDirection == 2) && (abs((mouse_width - 20 - j * 100 - 20 - 40)) <= 85) && (abs((mouse_y + 20 - road[1][j] - 75)) <= 95))
					{
						hp -= 8;

						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if ((iDirection == 3 || iDirection == 4) && (abs(mouse_x + 15 - j * 100 - 20 - 40)) <= 60 && (abs((mouse_y + 20 - road[1][j] - 75)) <= 120))
					{
						hp -= 8;
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}

					if ((iDirection == 1 || iDirection == 2) && (abs(mouse_x + 45 - trap_x - 25) <= 68) && abs(mouse_y + 20 - trap_x - 25) <= 43)
					{
						hp -= 9;
						if (hp <= 0)
						{
							trapAngle = 2 * PI;
							trap_x = -400;
							trap_y = -400;
							transparentimage(mouse_x, mouse_y, &explode, &explode_mask);
						}
					}
					else if ((iDirection == 3 || iDirection == 4) && (abs(mouse_x + 20 - trap_x - 25) <= 43) && abs(mouse_y + 45 - trap_x - 25) <= 68)
					{
						hp -= 9;
						if (hp <= 0)
						{
							trapAngle = 2 * PI;
							trap_x = -400;
							trap_y = -400;
							transparentimage(mouse_x, mouse_y, &explode, &explode_mask);
						}
					}
					if (hp <= 0)
					{
						safe = 0;
					}
					showVehicle2(j * 100, road[1][j], road[0][j]);
					if (road[1][j] >= -250)
					{
						road[1][j] -= vehicle[road[0][j]].speed;
					}
                    else
					{
						score++;
						road[1][j] = 480;
						road[0][j] = 0;
					}
					if (j == 4 && (abs((trap_x - j * 100 - 40)) <= 65) && (abs((trap_y + 18 - road[1][j] - 125)) <= 160))
					{
						score += 2;
						road[1][j] = -250;
						road[0][j] = 0;
						trapAngle = 2 * PI;
						trap_x = -400;
						trap_y = -400;
						transparentimage(j * 100 + 40, road[1][j] + 125, &explode, &explode_mask);
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if (j == 6 && (abs((trap_x - j * 100 - 40)) <= 65) && (abs((trap_y + 18 - road[1][j] - 75)) <= 110))
					{
						score -= 10;
						road[1][j] = -250;
						road[0][j] = 0;
						trapAngle = 2 * PI;
						trap_x = -400;
						trap_y = -400;
						transparentimage(j * 100 + 40, road[1][j] + 75, &explode, &explode_mask);
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					else if (j != 4 && j != 6 && (abs((trap_x - j * 100 - 40)) <= 65) && (abs((trap_y + 18 - road[1][j] - 75)) <= 110))
					{
						score += 2;
						road[1][j] = -250;
						road[0][j] = 0;
						trapAngle = 2 * PI;
						trap_x = -400;
						trap_y = -400;
						transparentimage(j * 100 + 40, road[1][j] + 75, &explode, &explode_mask);
						mciSendString(_T("open .\\peng.mp3 alias peng"), NULL, 0, NULL);
						mciSendString("play peng", NULL, 0, NULL);
					}
					
				}
			}
		}

		setfillcolor(BLUE);
		solidrectangle(0, 0, cooling, 20);
		if (hp >= 300)
		{
			setfillcolor(GREEN);
		}
		else if (hp >= 150)
		{
			setfillcolor(YELLOW);
		}
		else
		{
			setfillcolor(RED);
		}
		solidrectangle(0, Height - 20, hp, Height);
		FlushBatchDraw();
		if (score <= 50)
		{
			Sleep(70);
		}
		else
		{
			Sleep(30);
		}
	}

}

void updateWithInput()//���û��йص�����
{
	if (safe)
	{

		if (_kbhit())
		{
			if (GetAsyncKeyState('A') && mouse_x >= 0)           //wasd��������ģ���ƶ�
			{
				iDirection = 1;
				mouse_x -= 15;
				mouse_width -= 15;
			}
			if (GetAsyncKeyState('D') && mouse_width < 580)
			{
				iDirection = 2;
				mouse_x += 15;
				mouse_width += 15;
			}
			if (GetAsyncKeyState('W') && mouse_y > 0)
			{
				iDirection = 3;
				mouse_y -= 15;
				mouse_height -= 15;
			}
			if (GetAsyncKeyState('S') && mouse_height < Height)
			{
				iDirection = 4;
				mouse_y += 15;
				mouse_height += 15;
			}
			if (GetAsyncKeyState(VK_ESCAPE))
				gameStatus = 3;
		}

		MOUSEMSG m;
		while (MouseHit())
		{
			m = GetMouseMsg();
			if ((m.uMsg == WM_LBUTTONDOWN) && (trapAngle >= 2 * PI) && cooling >= 180 )//����������
			{
				trap_x = m.x;//����������������
				trap_y = m.y;
				trapAngle = 0;//���ýǶ�
				cooling -= 180;
				transparentimage(trap_x - 100, trap_y - 150, &crack_1, &crack_1_mask);
				transparentimage(trap_x - 100, trap_y - 150, &crack_2, &crack_2_mask);
				transparentimage(trap_x - 50, trap_y - 75, &crack_3, &crack_3_mask);
				Sleep(20);
			}
		}
	}

}

void delay(DWORD ms)				// ������ʱ
{
	static DWORD oldtime = GetTickCount();

	while (GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}

void gameover()//������Ϸ
{
	if (safe == 0)
	{
		settextcolor(WHITE);
		outtextxy(Width / 2 - 100, Height / 2, _T("GAME OVER"));
		mciSendString("close bkmusic", NULL, 0, NULL);
		mciSendString(_T("open \\lostround.mp3 alias gameovermusic"), NULL, 0, NULL);
		mciSendString("play gameovermusic", NULL, 0, NULL);
		EndBatchDraw();
		MOUSEMSG n;
		if (MouseHit())
		{
			n = GetMouseMsg();
			if (n.uMsg == WM_LBUTTONDOWN)
			closegraph();
		}
	}
}

int main()
{
	//system(".\\startvideo.exe");
	startup();
	srand((unsigned)time(NULL));
	while (1)
	{
		show();
			updateWithoutInput();
			if (safe != 0)
			cleardevice();
			updateWithInput();
			if (safe != 0)
			cleardevice();

			delay(5);
		gameover();

	}

	return 0;
}

void imageLoad()//����ͼƬ
{
	loadimage(&vehicle_1, _T(".\\car_1.jpg"), 60, 150);
	loadimage(&vehicle_2, _T(".\\car_2.jpg"), 80, 150);
	loadimage(&vehicle_3, _T(".\\car_3.jpg"), 80, 250);
	loadimage(&vehicle_4, _T(".\\car_4.jpg"), 80, 150);
	loadimage(&vehicle_5, _T(".\\car_5.jpg"), 80, 150);
	loadimage(&vehicle_10, _T(".\\car_10.jpg"), 60, 150);
	loadimage(&vehicle_20, _T(".\\car_20.jpg"), 80, 150);
	loadimage(&vehicle_30, _T(".\\car_30.jpg"), 80, 250);
	loadimage(&vehicle_40, _T(".\\car_40.jpg"), 80, 150);
	loadimage(&vehicle_50, _T(".\\car_50.jpg"), 80, 150);
	loadimage(&background, _T(".\\background.jpg"), 580, 480);
	loadimage(&mouse_a, _T(".\\mouse_a.png"), 90, 40);
	loadimage(&mouse_d, _T(".\\mouse_d.png"), 90, 40);
	loadimage(&mouse_w, _T(".\\mouse_w.png"), 40, 90);
	loadimage(&mouse_s, _T(".\\mouse_s.png"), 40, 90);
	loadimage(&mouse1_a, _T(".\\mouse_a.png"), 90, 40);
	loadimage(&mouse1_d, _T(".\\mouse_d.png"), 90, 40);
	loadimage(&mouse1_w, _T(".\\mouse_w.png"), 40, 90);
	loadimage(&mouse1_s, _T(".\\mouse_s.png"), 40, 90);
	loadimage(&zhe_a, _T(".\\zhe_a.png"), 90, 40);
	loadimage(&zhe_w, _T(".\\zhe_w.png"), 40, 90);
	loadimage(&zhe_s, _T(".\\zhe_s.png"), 40, 90);
	loadimage(&zhe_d, _T(".\\zhe_d.png"), 90, 40);
	loadimage(&background2, _T(".\\2.jpg"), 60, 480);
	loadimage(&startbg, _T(".\\startbg.jpg"), 640, 480);
	loadimage(&pmostart, _T(".\\pmostart.jpg"), 640, 480);   //������ʱ��ͼƬ����ͬ
	loadimage(&pmoinfo, _T(".\\pmoinfofin.jpg"), 640, 480);
	loadimage(&pmomusic, _T(".\\pmomusic.jpg"), 640, 480);
	loadimage(&pmorank, _T(".\\rank.jpg"), 640, 480);
	loadimage(&pmostore, _T(".\\pmostore.jpg"), 640, 480);
	loadimage(&conbg, _T(".\\conbg.jpg"), 640, 480);
	loadimage(&conpmoinfo, _T(".\\conpmoinfo.jpg"), 640, 480);
	loadimage(&conpmoagain, _T(".\\conpmoagain.jpg"), 640, 480);
	loadimage(&conpmocon, _T(".\\conpmocontinue.jpg"), 640, 480);
	loadimage(&conpmoback, _T(".\\conpmoback.jpg"), 640, 480);
	loadimage(&conpmomusic, _T(".\\conpmomusic.jpg"), 640, 480);
	loadimage(&mute1, _T(".\\jingyin.jpg"), 640, 480);
	loadimage(&mute0, _T(".\\mute.jpg"), 640, 480);
	loadimage(&store_0, _T(".\\store_0.jpg"), 640, 480);
	loadimage(&store_1, _T(".\\store_1.jpg"), 640, 480);
	loadimage(&store_2, _T(".\\store_2.jpg"), 640, 480);
	loadimage(&store_3, _T(".\\store_3.jpg"), 640, 480);
	loadimage(&crack_1, _T(".\\crack_1.jpg"), 200, 300);
	loadimage(&crack_1_mask, _T(".\\crack_1_mask,jpg"), 200, 300);
	loadimage(&crack_2, _T(".\\crack_2.jpg"), 200, 300);
	loadimage(&crack_2_mask, _T(".\\crack_2_mask.jpg"), 200, 300);
	loadimage(&crack_3, _T(".\\crack_3.jpg"), 100, 150);
	loadimage(&crack_3_mask, _T(".\\crack_3_mask.jpg"), 100, 150);
	loadimage(&mouse1_a, _T(".\\mouse1_a.png"), 90, 40);
	loadimage(&mouse1_d, _T(".\\mouse1_d.png"), 90, 40);
	loadimage(&mouse1_w, _T(".\\mouse1_w.png"), 40, 90);
	loadimage(&mouse1_s, _T(".\\mouse1_s.png"), 40, 90);
	loadimage(&explode, _T(".\\explode.jpg"), 70, 70);
	loadimage(&explode_mask, _T(".\\explode_mask.jpg"), 70, 70);
}
void soundVehicle(int x)
{
	switch (x)
	{
	case 1:
		mciSendString("close music1", NULL, 0, NULL);
		mciSendString(_T("open .\\1.mp3 alias music1"), NULL, 0, NULL);//����Ч
		mciSendString("play music1", NULL, 0, NULL);//���β���
		break;
	case 2:
		mciSendString("close music2", NULL, 0, NULL);
		mciSendString(_T("open .\\2.mp3 alias music2"), NULL, 0, NULL);//����Ч
		mciSendString("play music2", NULL, 0, NULL);//���β���
		break;
	case 3:
		mciSendString("close music3", NULL, 0, NULL);
		mciSendString(_T("open .\\3.mp3 alias music3"), NULL, 0, NULL);//����Ч
		mciSendString("play music3", NULL, 0, NULL);//���β���
		break;
	case 4:
		mciSendString("close music4", NULL, 0, NULL);
		mciSendString(_T("open .\\4.mp3 alias music4"), NULL, 0, NULL);//����Ч
		mciSendString("play music4", NULL, 0, NULL);//���β���
		break;
	case 5:
		mciSendString("close music5", NULL, 0, NULL);
		mciSendString(_T("open .\\5.mp3 alias music5"), NULL, 0, NULL);//����Ч
		mciSendString("play music5", NULL, 0, NULL);//���β���
		break;
	}
}

// ��¼����
void Login()
{
	MOUSEMSG m;

	while (true)
	{
		mciSendString(_T("open .\\mainmenu.mp3 alias menumusic"), NULL, 0, NULL);
		mciSendString("play menumusic", NULL, 0, NULL);
		m = GetMouseMsg();				// �ж��Ƿ������
		if (m.x >= 0 && m.y >= 0 && ((m.x - 320)*(m.x - 320) + (m.y - 367)*(m.y - 367)) <= 84 * 84)   //�������Ƿ����������
		{
			putimage(0, 0, &pmostart);

			if (m.uMsg == WM_LBUTTONDOWN)  //����Ƿ񵥻�
			{
				setbkcolor(WHITE);
				gameStatus = 1;
				break;//��Ϸ״̬��0Ϊ��ʼ���棬1Ϊ������Ϸ��2Ϊ��Ϸ������3Ϊ��Ϸ��ͣ
			 //��pausemenu�������Ƿ����ڿ��꿪ʼ����󣬵�START��ֱ�ӽ�����ͣ���濴Ч���������ϵ�ʱ������Ͱ����ﻻ�ɿ�ʼ��Ϸ�ĺ���
			}
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 51)*(m.x - 51) + (m.y - 427)*(m.y - 427)) <= 22 * 22)  //����info��
		{
			putimage(0, 0, &pmoinfo);
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 588)*(m.x - 588) + (m.y - 427)*(m.y - 427)) <= 22 * 22) //���ֿ���
		{
			putimage(0, 0, &pmomusic);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				musicswitch *= -1;
			}
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 164)*(m.x - 164) + (m.y - 405)*(m.y - 405)) <= 44 * 44)  //����
		{
			putimage(0, 0, &pmorank);
			//if (m.uMsg == WM_LBUTTONDOWN){}     ����	
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 478)*(m.x - 478) + (m.y - 403)*(m.y - 403)) <= 44 * 44)
		{
			putimage(0, 0, &pmostore);
			if (m.uMsg == WM_LBUTTONUP)
			{
				gameStatus = 4;
				store();
			}     //�̵�
		}
		else if (musicswitch == -1)
		{
			putimage(0, 0, &mute0);
		}
		else
			putimage(0, 0, &startbg);
	}
}


void store()
{
	MOUSEMSG m;
	while (gameStatus == 4)
	{
		m = GetMouseMsg();
		if (_kbhit())
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				gameStatus = 0;
				break;
			}
		}
		else if (m.x > 10 && m.x < 210 && m.y > 150 && m.y < 350)
		{
			putimage(0, 0, &store_1);
		}
		else if (m.x > 220 && m.x < 420 && m.y > 150 && m.y < 350)
		{
			putimage(0, 0, &store_2);
		}
		else if (m.x > 430 && m.x < 630 && m.y >150 && m.y < 350)
		{
			putimage(0, 0, &store_3);
		}
		else
			putimage(0, 0, &store_0);
	}
}
void pausemenu()
{
	putimage(0, 0, &conbg);
	MOUSEMSG m;

	while (gameStatus == 3)
	{
		m = GetMouseMsg();				// �ж��Ƿ������
		if (m.x >= 0 && m.y >= 0 && ((m.x - 320)*(m.x - 320) + (m.y - 240)*(m.y - 240)) <= 84 * 84)
		{
			putimage(0, 0, &conpmocon);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				gameStatus = 1;
			}
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 51)*(m.x - 51) + (m.y - 242)*(m.y - 242)) <= 22 * 22)
		{
			putimage(0, 0, &conpmoinfo);
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 588)*(m.x - 588) + (m.y - 242)*(m.y - 242)) <= 22 * 22)
		{
			putimage(0, 0, &conpmomusic);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				musicswitch *= -1;
			}
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 164)*(m.x - 164) + (m.y - 242)*(m.y - 242)) <= 44 * 44)
		{
			putimage(0, 0, &conpmoagain);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				gameStatus = 1;
				iDirection = 1;
				mouse_x = Width / 2;//��ʼ������λ��
				mouse_y = Height / 2;

				mouse_height = Height / 2 + 40;//��ʼ������߽�
				mouse_width = Width / 2 + 70;
				safe = 1;//��ʼ������ȫֵ
				vehicle_ok = 1;
				hp = 580;//��ʼ������Ѫ��
				score = 0;

				trap_x = -400;
				trap_y = -400;//��ʼ�������������

				int i;
				for (i = 0; i < 6; i++)
				{
					road[0][i] = 0;
				}
				for (i = 0; i < 3; i++)
				{
					road[1][i] = -250;
				}
				for (i = 3; i < 6; i++)
				{
					road[1][i] = 480;
				}
			}
		}
		else if (m.x >= 0 && m.y >= 0 && ((m.x - 478)*(m.x - 478) + (m.y - 240)*(m.y - 240)) <= 44 * 44)
		{
			putimage(0, 0, &conpmoback);

		}
		else if(musicswitch == -1)
		{
			putimage(0, 0, &mute1);
		}
		else
			putimage(0, 0, &conbg);
		FlushBatchDraw();
	}
	
}