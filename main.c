//2023/10/14
//ʹ��C17���Ա�׼����
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

int main() {
	//�����������
	srand((unsigned)time(NULL));
	//���ô��ڱ���
	system("title ɨ��");
	//��ȡ��׼������
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO hcursor;
	hcursor.dwSize = 1;
	hcursor.bVisible = FALSE;
	//���ÿ���̨��겻�ɼ�
	SetConsoleCursorInfo(hOut, &hcursor);

	short flag = 0;

	//�����û�ѡ��ʼ��Ϸ���˳�����ʾ������Ϣ��������뻺����
	while (1) { 
		//������ɫ����ӡ�˵�
		color(7);
		menu();
		printf("��ѡ��>: ");
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
				printf("�������,������");
				Sleep(2000);
				clean();
		}
	}
}