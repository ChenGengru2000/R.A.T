//R.A.T_Core.cpp
//Tech Lead: Chen Gengru
//Coder: Tang Bolong, Yang Yifei
//updated on 2019-3-10
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

//ȫ�ֱ���
#define Height 480//�����߶�
#define Width 640//�������

int mouse_x;                 //�����Ͻ�Ϊ��㣬x
int mouse_y;                 //ͬ�ϣ�y
int body_l;   //����
int mouse_height;            //�����²�yֵ 
int mouse_width;             //�����Ҳ�xֵ
int vehicle_x, vehicle_y, vehicle_right, vehicle_bottom;   //��������
int score;//����
int safe;//�����Ƿ�ȫ
int vehicle_ok;
int hp;//����Ѫ��
int iDirection;
int target = 100;



int road[2][6] = { {0,0,0,0,0,0}, {-200,-200,-200,480,480,480} };//�����������λ��
IMAGE start[1], background, background2, vehicle_10, vehicle_20, vehicle_30, vehicle_40, 
vehicle_50, vehicle_1, vehicle_2, vehicle_3, vehicle_4, vehicle_5, mouse_tail_a, mouse_tail_d, 
mouse_tail_s, mouse_tail_w, mouse_body_a, mouse_body_w, mouse_body_d, mouse_body_s, zhe_body_a, zhe_body_w, 
zhe_body_d, zhe_body_s, hp_1, hp_2, hp_3;

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

void imageLoad();//����ͼƬ

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

void showVehicle1(int x, int y, int num)//�����ӡ����
{
	switch (num)//��ͬ����ֵ��Ӧ��ӡ��ͬ����ĳ���
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
	hp = 3;//��ʼ������Ѫ��
	score = 0;
	BeginBatchDraw();


	mciSendString(_T("open .\\themusic.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);//ѭ������
}

void showmouse(int Direction)
{
	switch (Direction)
	{
	case 1:
	{
		putimage(mouse_x, mouse_y, &zhe_body_a);
		putimage(mouse_x, mouse_y, &mouse_body_a);
		putimage(mouse_x + 40, mouse_y, &mouse_tail_a);
		break;
	}
	case 2:
	{
		putimage(mouse_x + 40, mouse_y, &zhe_body_d);
		putimage(mouse_x + 40, mouse_y, &mouse_body_d);
		putimage(mouse_x, mouse_y, &mouse_tail_d);
		break;
	}
	case 3:
	{
		putimage(mouse_x + 20, mouse_y - 20, &zhe_body_w);
		putimage(mouse_x + 20, mouse_y - 20, &mouse_body_w);
		putimage(mouse_x + 20, mouse_y + 20, &mouse_tail_w);
		break;
	}
	case 4:
	{
		putimage(mouse_x + 20, mouse_y + 20, &zhe_body_s);
		putimage(mouse_x + 20, mouse_y + 20, &mouse_body_s);
		putimage(mouse_x + 20, mouse_y - 20, &mouse_tail_s);
		break;
	}
	}
}

void show()                     //��ʾ����
{
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
	else {
		settextstyle(30, 15, _T("Segoe Script"));
		setbkmode(TRANSPARENT);
		sprintf_s(t, "%d", target + 900);
		outtextxy(580, 390, t);

	}
	if (hp == 3)
	{
		putimage(580, 50, &hp_3);
	}
	else if (hp == 2)
	{
		putimage(580, 50, &hp_2);
	}
	else
		putimage(580, 50, &hp_1);
}

void clean()                         //����������������ͬ��ɫͼ�θ�����һ˲��ͼ��
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(mouse_x, mouse_y, mouse_width, mouse_height);

}

void updateWithoutInput()//���û��޹ص�����
{
	putimage(0, 0, &background);
	putimage(580, 0, &background2);

	show();

	int i, j;
	float k;
	for (i = 0; i < 6; i++)
	{
		if ((road[0][i] == 0) && ((road[0][1] + road[0][2] + road[0][3] + road[0][4] + road[0][5] + road[0][0]) <= 6))
		{
			if (k = (rand() / 32767.0))
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
				if ((iDirection==1||iDirection==2)&&(abs((mouse_width - 20 - j * 100 - 20 - 40)) <= 10) && (abs((mouse_y + 20 - road[1][j] - 75)) <= 10))
					hp--;
				if ((iDirection == 3 || iDirection == 4)&&(abs(mouse_x + 15 - j * 100 - 20 - 40)) <= 10 && (abs((mouse_y + 20 - road[1][j] - 75)) <= 10))
					hp--;
				showVehicle1(j * 100 , road[1][j], road[0][j]);
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
			}
		}
		else//���¶���
		{
			if (road[0][j] != 0)
			{
				if ((iDirection == 1 || iDirection == 2) && abs((mouse_width - 20 - j * 100 - 20 - 40)) <= 10 && abs((mouse_y + 20 - road[1][j] - 75)) <= 10)
					hp--;
				if ((iDirection == 3 || iDirection == 4) && abs((mouse_x + 15 - j * 100 - 20 - 40)) <= 10 && abs((mouse_y + 20 - road[1][j] - 75)) <= 10)
					hp--;
				showVehicle2(j * 100 + 20, road[1][j], road[0][j]);
				if (road[1][j] >= -100)
				{
					road[1][j] -= vehicle[road[0][j]].speed;
				}
				else
				{
					score++;
					road[1][j] = 480;
					road[0][j] = 0;
				}
			}
		}
	}



	FlushBatchDraw();

	Sleep(100);
}

void updateWithInput()//���û��йص�����
{
	char input;

	if (_kbhit())
	{
		if (GetAsyncKeyState('A') && mouse_x >= 0)           //wasd��������ģ���ƶ�
		{
			iDirection = 1;
			mouse_x -= 15;
			mouse_width -= 15;
		}
		if (GetAsyncKeyState('D') && mouse_width < Width)
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
	EndBatchDraw();
	_getch();
	settextcolor(WHITE);
	outtextxy(Width / 2 - 100, Height / 2, _T("GAME OVER"));
	_getch();
	closegraph();
}

int main()
{
	//system(".\\startvideo.exe");
	startup();
	srand((unsigned)time(NULL));
	while (1)
	{
		updateWithoutInput();
		updateWithInput();
		delay(5);
	}
	gameover();
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
	loadimage(&mouse_body_a, _T(".\\mouse_body_a.bmp"), 40, 40);
	loadimage(&mouse_body_d, _T(".\\mouse_body_d.bmp"), 40, 40);
	loadimage(&mouse_body_w, _T(".\\mouse_body_w.bmp"), 40, 40);
	loadimage(&mouse_body_s, _T(".\\mouse_body_s.bmp"), 40, 40);
	loadimage(&mouse_tail_a, _T(".\\mouse_tail_a.png"), 40, 40);
	loadimage(&mouse_tail_s, _T(".\\mouse_tail_s.png"), 40, 40);
	loadimage(&mouse_tail_d, _T(".\\mouse_tail_d.png"), 40, 40);
	loadimage(&mouse_tail_w, _T(".\\mouse_tail_w.png"), 40, 40);
	loadimage(&zhe_body_a, _T(".\\mouse_body_mask_a.bmp"), 40, 40);
	loadimage(&zhe_body_w, _T(".\\mouse_body_mask_w.bmp"), 40, 40);
	loadimage(&zhe_body_s, _T(".\\mouse_body_mask_s.bmp"), 40, 40);
	loadimage(&zhe_body_d, _T(".\\mouse_body_mask_d.bmp"), 40, 40);
	loadimage(&hp_1, _T(".\\hp1.png"), 60, 20);
	loadimage(&hp_2, _T(".\\hp2.png"), 60, 20);
	loadimage(&hp_3, _T(".\\hp3.png"), 60, 20);
	loadimage(&background2, _T(".\\2.jpg"), 60, 480);
}