//2023/10/14
//使用C17语言标准编译
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

int main() {
	//设置随机种子
	srand((unsigned)time(NULL));
	//设置窗口标题
	system("title 扫雷");
	//获取标准输出句柄
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO hcursor;
	hcursor.dwSize = 1;
	hcursor.bVisible = FALSE;
	//设置控制台光标不可见
	SetConsoleCursorInfo(hOut, &hcursor);

	short flag = 0;

	//根据用户选择开始游戏或退出或提示错误信息并清空输入缓冲区
	while (1) { 
		//设置颜色并打印菜单
		color(7);
		menu();
		printf("请选择>: ");
		scanf("%hd", &flag);

		switch (flag) {
			case 1:
				clean();
				game();
				break;
			case 2:
				clean();
				CloseHandle(hOut);
				return 0;
			default:
				printf("输入错误,请重试");
				Sleep(2000);
				clean();
		}
	}
}