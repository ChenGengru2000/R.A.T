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
IMAGE start[112];

//引用Windows Multimedia API
#pragma comment(lib, "Winmm.lib")

//全局变量
#define Height 480//画布高度
#define Width 640//画布宽度

int main()
{
	loadimage(&start[0], _T(".\\start\\0.gif"), 640, 480);
	loadimage(&start[1], _T(".\\start\\1.gif"), 640, 480);
	loadimage(&start[2], _T(".\\start\\2.gif"), 640, 480);
	loadimage(&start[3], _T(".\\start\\3.gif"), 640, 480);
	loadimage(&start[4], _T(".\\start\\4.gif"), 640, 480);
	loadimage(&start[5], _T(".\\start\\5.gif"), 640, 480);
	loadimage(&start[6], _T(".\\start\\6.gif"), 640, 480);
	loadimage(&start[7], _T(".\\start\\7.gif"), 640, 480);
	loadimage(&start[8], _T(".\\start\\8.gif"), 640, 480);
	loadimage(&start[9], _T(".\\start\\9.gif"), 640, 480);
	loadimage(&start[10], _T(".\\start\\10.gif"), 640, 480);
	loadimage(&start[11], _T(".\\start\\11.gif"), 640, 480);
	loadimage(&start[12], _T(".\\start\\12.gif"), 640, 480);
	loadimage(&start[13], _T(".\\start\\13.gif"), 640, 480);
	loadimage(&start[14], _T(".\\start\\14.gif"), 640, 480);
	loadimage(&start[15], _T(".\\start\\15.gif"), 640, 480);
	loadimage(&start[16], _T(".\\start\\16.gif"), 640, 480);
	loadimage(&start[17], _T(".\\start\\17.gif"), 640, 480);
	loadimage(&start[18], _T(".\\start\\18.gif"), 640, 480);
	loadimage(&start[19], _T(".\\start\\19.gif"), 640, 480);
	loadimage(&start[20], _T(".\\start\\20.gif"), 640, 480);
	loadimage(&start[21], _T(".\\start\\21.gif"), 640, 480);
	loadimage(&start[22], _T(".\\start\\22.gif"), 640, 480);
	loadimage(&start[23], _T(".\\start\\23.gif"), 640, 480);
	loadimage(&start[24], _T(".\\start\\24.gif"), 640, 480);
	loadimage(&start[25], _T(".\\start\\25.gif"), 640, 480);
	loadimage(&start[26], _T(".\\start\\26.gif"), 640, 480);
	loadimage(&start[27], _T(".\\start\\27.gif"), 640, 480);
	loadimage(&start[28], _T(".\\start\\28.gif"), 640, 480);
	loadimage(&start[29], _T(".\\start\\29.gif"), 640, 480);
	loadimage(&start[30], _T(".\\start\\30.gif"), 640, 480);
	loadimage(&start[31], _T(".\\start\\31.gif"), 640, 480);
	loadimage(&start[32], _T(".\\start\\32.gif"), 640, 480);
	loadimage(&start[33], _T(".\\start\\33.gif"), 640, 480);
	loadimage(&start[34], _T(".\\start\\34.gif"), 640, 480);
	loadimage(&start[35], _T(".\\start\\35.gif"), 640, 480);
	loadimage(&start[36], _T(".\\start\\36.gif"), 640, 480);
	loadimage(&start[37], _T(".\\start\\37.gif"), 640, 480);
	loadimage(&start[38], _T(".\\start\\38.gif"), 640, 480);
	loadimage(&start[39], _T(".\\start\\39.gif"), 640, 480);
	loadimage(&start[40], _T(".\\start\\40.gif"), 640, 480);
	loadimage(&start[41], _T(".\\start\\41.gif"), 640, 480);
	loadimage(&start[42], _T(".\\start\\42.gif"), 640, 480);
	loadimage(&start[43], _T(".\\start\\43.gif"), 640, 480);
	loadimage(&start[44], _T(".\\start\\44.gif"), 640, 480);
	loadimage(&start[45], _T(".\\start\\45.gif"), 640, 480);
	loadimage(&start[46], _T(".\\start\\46.gif"), 640, 480);
	loadimage(&start[47], _T(".\\start\\47.gif"), 640, 480);
	loadimage(&start[48], _T(".\\start\\48.gif"), 640, 480);
	loadimage(&start[49], _T(".\\start\\49.gif"), 640, 480);
	loadimage(&start[50], _T(".\\start\\50.gif"), 640, 480);
	loadimage(&start[51], _T(".\\start\\51.gif"), 640, 480);
	loadimage(&start[52], _T(".\\start\\52.gif"), 640, 480);
	loadimage(&start[53], _T(".\\start\\53.gif"), 640, 480);
	loadimage(&start[54], _T(".\\start\\54.gif"), 640, 480);
	loadimage(&start[55], _T(".\\start\\55.gif"), 640, 480);
	loadimage(&start[56], _T(".\\start\\56.gif"), 640, 480);
	loadimage(&start[57], _T(".\\start\\57.gif"), 640, 480);
	loadimage(&start[58], _T(".\\start\\58.gif"), 640, 480);
	loadimage(&start[59], _T(".\\start\\59.gif"), 640, 480);
	loadimage(&start[60], _T(".\\start\\60.gif"), 640, 480);
	loadimage(&start[61], _T(".\\start\\61.gif"), 640, 480);
	loadimage(&start[62], _T(".\\start\\62.gif"), 640, 480);
	loadimage(&start[63], _T(".\\start\\63.gif"), 640, 480);
	loadimage(&start[64], _T(".\\start\\64.gif"), 640, 480);
	loadimage(&start[65], _T(".\\start\\65.gif"), 640, 480);
	loadimage(&start[66], _T(".\\start\\66.gif"), 640, 480);
	loadimage(&start[67], _T(".\\start\\67.gif"), 640, 480);
	loadimage(&start[68], _T(".\\start\\68.gif"), 640, 480);
	loadimage(&start[69], _T(".\\start\\69.gif"), 640, 480);
	loadimage(&start[70], _T(".\\start\\70.gif"), 640, 480);
	loadimage(&start[71], _T(".\\start\\71.gif"), 640, 480);
	loadimage(&start[72], _T(".\\start\\72.gif"), 640, 480);
	loadimage(&start[73], _T(".\\start\\73.gif"), 640, 480);
	loadimage(&start[74], _T(".\\start\\74.gif"), 640, 480);
	loadimage(&start[75], _T(".\\start\\75.gif"), 640, 480);
	loadimage(&start[76], _T(".\\start\\76.gif"), 640, 480);
	loadimage(&start[77], _T(".\\start\\77.gif"), 640, 480);
	loadimage(&start[78], _T(".\\start\\78.gif"), 640, 480);
	loadimage(&start[79], _T(".\\start\\79.gif"), 640, 480);
	loadimage(&start[80], _T(".\\start\\80.gif"), 640, 480);
	loadimage(&start[81], _T(".\\start\\81.gif"), 640, 480);
	loadimage(&start[82], _T(".\\start\\82.gif"), 640, 480);
	loadimage(&start[83], _T(".\\start\\83.gif"), 640, 480);
	loadimage(&start[84], _T(".\\start\\84.gif"), 640, 480);
	loadimage(&start[85], _T(".\\start\\85.gif"), 640, 480);
	loadimage(&start[86], _T(".\\start\\86.gif"), 640, 480);
	loadimage(&start[87], _T(".\\start\\87.gif"), 640, 480);
	loadimage(&start[88], _T(".\\start\\88.gif"), 640, 480);
	loadimage(&start[89], _T(".\\start\\89.gif"), 640, 480);
	loadimage(&start[90], _T(".\\start\\90.gif"), 640, 480);
	loadimage(&start[91], _T(".\\start\\91.gif"), 640, 480);
	loadimage(&start[92], _T(".\\start\\92.gif"), 640, 480);
	loadimage(&start[93], _T(".\\start\\93.gif"), 640, 480);
	loadimage(&start[94], _T(".\\start\\94.gif"), 640, 480);
	loadimage(&start[95], _T(".\\start\\95.gif"), 640, 480);
	loadimage(&start[96], _T(".\\start\\96.gif"), 640, 480);
	loadimage(&start[97], _T(".\\start\\97.gif"), 640, 480);
	loadimage(&start[98], _T(".\\start\\98.gif"), 640, 480);
	loadimage(&start[99], _T(".\\start\\99.gif"), 640, 480);
	loadimage(&start[100], _T(".\\start\\100.gif"), 640, 480);
	loadimage(&start[101], _T(".\\start\\101.gif"), 640, 480);
	loadimage(&start[102], _T(".\\start\\102.gif"), 640, 480);
	loadimage(&start[103], _T(".\\start\\103.gif"), 640, 480);
	loadimage(&start[104], _T(".\\start\\104.gif"), 640, 480);
	loadimage(&start[105], _T(".\\start\\105.gif"), 640, 480);
	loadimage(&start[106], _T(".\\start\\106.gif"), 640, 480);
	loadimage(&start[107], _T(".\\start\\107.gif"), 640, 480);
	loadimage(&start[108], _T(".\\start\\108.gif"), 640, 480);
	loadimage(&start[109], _T(".\\start\\109.gif"), 640, 480);
	loadimage(&start[110], _T(".\\start\\110.gif"), 640, 480);
	loadimage(&start[111], _T(".\\start\\111.gif"), 640, 480);
	initgraph(640, 480);
	int i;
	for (i = 0; i < 112; i++)
	{
		putimage(0, 0, &start[i]);
		if (_kbhit())
		{
			return 0;
		}
		Sleep(100);
	}

	return 0;
}