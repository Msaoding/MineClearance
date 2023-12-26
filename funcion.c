#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

//��ͼ
unsigned short map[WIDTH][LENGTH] = {0};
//ͳ�Ƶ�������
unsigned short mine_quantity = 0;

enum color {
    BLACK, BLUE, GREEN, LAKE_BLUE, RED, VIOLET, YELLOW, WHITE,
    GRAY, BABY_BLUE, AQUA, LIGHT_GREEN, BLUSH,
    LAVENDER, FAINT_YELLOW, GLOSS_WHITE
};

//������ɫ
void color(const unsigned short textcolor) {
    if (textcolor <= GLOSS_WHITE) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textcolor);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    }
}

//��ӡ�˵�
void menu(void) {
	system("cls");
    color(GLOSS_WHITE);

	printf("\n\
    \n\
    \n\
    \n\
    \n\
      __  __   ___   _   _   _____      ____   _       _____      _      ____       _      _   _    ____   _____ \n\
     |  \\/  | |_ _| | \\ | | | ____|    / ___| | |     | ____|    / \\    |  _ \\     / \\    | \\ | |  / ___| | ____|\n\
     | |\\/| |  | |  |  \\| | |  _|     | |     | |     |  _|     / _ \\   | |_) |   / _ \\   |  \\| | | |     |  _|  \n\
     | |  | |  | |  | |\\  | | |___    | |___  | |___  | |___   / ___ \\  |  _ <   / ___ \\  | |\\  | | |___  | |___ \n\
     |_|  |_| |___| |_| \\_| |_____|    \\____| |_____| |_____| /_/   \\_\\ |_| \\_\\ /_/   \\_\\ |_| \\_|  \\____| |_____|\n\
                                                                                                                 \n\
    \n\
    \n\
    \n\
                      _  _   ___  _____  _    ___  _____         ___  _   ___ __  __ ___  _____ \n\
                     / |(_) / __||_   _|/_\\  | _ \\|_   _|       |_  )(_) | __|\\ \\/ /|_ _||_   _|\n\
                     | | _  \\__ \\  | | / _ \\ |   /  | |          / /  _  | _|  >  <  | |   | |  \n\
                     |_|(_) |___/  |_|/_/ \\_\\|_|_\\  |_|         /___|(_) |___|/_/\\_\\|___|  |_|  \n\
                                                                                                \n\
	\n\n\n");

    color(WHITE);
}

//������뻺����
void clean(void) {
    while (getchar() != '\n');
}

//��ʾ���е���
void uncover(unsigned short map[WIDTH][LENGTH]) {
    for (unsigned short y = 0; y < WIDTH; y++) {
        for (unsigned short x = 0; x < LENGTH; x++) {
            if (map[y][x] == LABLE_HIDDEN_MINE) {
                map[y][x] = LABLE_MINE;
            }
        }
    }
}

//��ʼ����ͼ������
void initialize(unsigned short map[WIDTH][LENGTH]) {
    unsigned short row = 0;
    unsigned short line = 0;

    for (unsigned short y = 0; y < WIDTH; y++) {
        for (unsigned short x = 0; x < LENGTH; x++) {
            map[y][x] = LABLE_ICON;
        }
    }

    for (unsigned short count = 0; count < MINE; count++) {
        do {
            row = ((unsigned short)rand() % WIDTH);
            line = ((unsigned short)rand() % LENGTH);

            if (map[row][line] == LABLE_ICON) {
                map[row][line] = LABLE_HIDDEN_MINE;
                break;
            }
        } while (1);
    }
}

//�������Ƿ��ų�
unsigned short mine_scan(unsigned short map[WIDTH][LENGTH], short y, short x) {
    for (short row = (y - 1); row <= (y + 1); row++) {
        for (short line = (x - 1); line <= (x + 1); line++) {
            if ((row < 0) || (row >= WIDTH) || (line < 0) || (line >= LENGTH)) {
                continue;
            }
            
            if (map[row][line] == LABLE_ICON) {
                return 1;
            }
        }
    }

    return 0;
}

//���׼���
unsigned short mine_counter(unsigned short map[WIDTH][LENGTH]) {
    unsigned short minecount = 0;

    for (unsigned short row = 0; row < WIDTH; row++) {
        for (unsigned short line = 0; line < LENGTH; line++) {
            if ((map[row][line] == LABLE_HIDDEN_MINE) && mine_scan(map, row, line)) {
                minecount++;
            }
        }
    }

    return minecount;
}

//��ӡ��ͼ
void print_map(unsigned short map[WIDTH][LENGTH]) {
    printf("  ");
    color(GRAY);

    //��ӡ������
    for (unsigned short x = 1; x <= WIDTH; x++) {
        printf("%3d", x);
    }
    putchar('\n');

    //��ӡ������
    for (unsigned short y = 1; y <= LENGTH; y++) {
        color(GRAY);
        printf("\n%-3d ", y);

        //��ӡ��ͼ�еĸ��ַ���
        for (unsigned short x = 0; x < WIDTH; x++) {
            color(WHITE);

            switch (map[y - 1][x]) {
                case LABLE_SPACE:
                    printf("   ");
                    break;
                case LABLE_HIDDEN_MINE:
                case LABLE_ICON:
                    printf("%-3c", 22);
                    break;
                case LABLE_MINE:
                    color(RED);
                    printf("*  ");
                    break;
                //��Բ�ͬ��С������ʹ�ò�ͬ����ɫ
                case 1:
                    color(BABY_BLUE);
                    printf("%-3hu", map[y - 1][x]);
                    break;
                case 2:
                    color(AQUA);
                    printf("%-3hu", map[y - 1][x]);
                    break;
                case 3:
                    color(LIGHT_GREEN);
                    printf("%-3hu", map[y - 1][x]);
                    break;
                case 4:
                    color(BLUSH);
                    printf("%-3hu", map[y - 1][x]);
                    break;
                case 5:
                    color(LAVENDER);
                    printf("%-3hu", map[y - 1][x]);
                    break;
                case 6:
                case 7:
                case 8:
                    color(FAINT_YELLOW);
                    printf("%-3hu", map[y - 1][x]);
                    break;
            }
        }

    }

    color(FAINT_YELLOW);
    printf("\n\n������:%hu\t\t", mine_quantity);
    color(WHITE);
}

//ˢ�»���
void flash(unsigned short map[WIDTH][LENGTH]) {
    system("cls");
    print_map(map);
}

//�����Χ�Ƿ���ڵ���
void scan(unsigned short map[WIDTH][LENGTH], short y, short x) {
    _Bool flag = 0;
    unsigned short count = 0;

    for (short row = (y - 1); row <= (y + 1); row++) {
        for (short line = (x - 1); line <= (x + 1); line++) {
            //�ж�����Ϸ���
            if ((row < 0) || (row >= WIDTH)) {
                continue;
            }
            else if ((line < 0) || (line >= LENGTH)) {
                continue;
            }
            //�����Ѿ������ĵؿ�
            else if ((map[row][line] > LABLE_SPACE) && (map[row][line] < LABLE_HIDDEN_MINE)) {
                continue;
            }

            if (map[row][line] == LABLE_HIDDEN_MINE) {
                flag = 1;
                count++;
            }
        }
    }

    //������������λ�ü�����Χ�ĵ�������
    if ((y >= 0) && (y < WIDTH) && (x >= 0) && (x < LENGTH)) {
        map[y][x] = count;
    }

    //�ݹ���ֱ����⵽����
    if (flag == 0) {
        for (short row = (y - 1); row <= (y + 1); row++) {
            for (short line = (x - 1); line <= (x + 1); line++) {
                //�ж�����Ϸ���
                if ((row < 0) || (row >= WIDTH)) {
                    continue;
                }
                else if ((line < 0) || (line >= LENGTH)) {
                    continue;
                }
                //��������λ�ú��Ѿ������ĵؿ�
                else if ((row == y) && (line == x)) {
                    continue;
                }
                else if ((map[row][line] > LABLE_SPACE) && (map[row][line] < LABLE_HIDDEN_MINE)) {
                    continue;
                }

                //����û�б���ʾ�ĵؿ�ͼ������
                if ((map[row][line] == LABLE_ICON)) {
                    scan(map, row, line);
                }
            }
        }
    }
}

//�����û�����
unsigned short input(unsigned short map[WIDTH][LENGTH]) {
    unsigned short y = 0;
    unsigned short x = 0;

    printf("����������>:");
    while (1) {
        //�ж�����Ϸ���
        if ((scanf("%hu%hu", &x, &y) == 2) && (y <= WIDTH) && (x <= LENGTH) && (y > 0) && (x > 0)) {
            break;
        }

        color(BLUSH);
        printf("\n\n�����������������");
        color(WHITE);
        clean();
        Sleep(2000);
        flash(map);
        printf("����������>:");
    }

    //�ж��Ƿ����
    if (map[y - 1][x - 1] == LABLE_HIDDEN_MINE) {
        return 1;
    }

    scan(map, (y - 1), (x - 1));
    return 0;
}

//��Ϸ��������
void game(void) {
        unsigned short flag = 0;
        unsigned short map[WIDTH][LENGTH] = { 0 };

        initialize(map);
        mine_quantity = mine_counter(map);

        while (1) {
            flash(map);

            //�ȵ��׾ͽ�����Ϸ
            if (input(map)) {
                uncover(map);
                flash(map);
                color(BLUSH);
                printf("\n\n��Ϸ����\n\n");
                system("pause");
                break;
            }
            
            //���еĵ��ױ����־�ʤ��
            mine_quantity = mine_counter(map);
            if (mine_quantity == 0) {
                flash(map);
                color(LIGHT_GREEN);
                printf("\n\n��ϲ����ʤ��\n\n");
                system("pause");
                break;
            }
        }
}