#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

//地图
unsigned short map[WIDTH][LENGTH] = {0};
//统计地雷数量
unsigned short mine_quantity = 0;

enum color {
    BLACK, BLUE, GREEN, LAKE_BLUE, RED, VIOLET, YELLOW, WHITE,
    GRAY, BABY_BLUE, AQUA, LIGHT_GREEN, BLUSH,
    LAVENDER, FAINT_YELLOW, GLOSS_WHITE
};

//设置颜色
void color(const unsigned short textcolor) {
    if (textcolor <= GLOSS_WHITE) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textcolor);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    }
}

//打印菜单
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

//清空输入缓冲区
void clean(void) {
    while (getchar() != '\n');
}

//揭示所有地雷
void uncover(unsigned short map[WIDTH][LENGTH]) {
    for (unsigned short y = 0; y < WIDTH; y++) {
        for (unsigned short x = 0; x < LENGTH; x++) {
            if (map[y][x] == LABLE_HIDDEN_MINE) {
                map[y][x] = LABLE_MINE;
            }
        }
    }
}

//初始化地图并埋雷
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

//检测地雷是否被排除
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

//地雷计数
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

//打印地图
void print_map(unsigned short map[WIDTH][LENGTH]) {
    printf("  ");
    color(GRAY);

    //打印横坐标
    for (unsigned short x = 1; x <= WIDTH; x++) {
        printf("%3d", x);
    }
    putchar('\n');

    //打印纵坐标
    for (unsigned short y = 1; y <= LENGTH; y++) {
        color(GRAY);
        printf("\n%-3d ", y);

        //打印地图中的各种符号
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
                //针对不同大小的数字使用不同的颜色
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
    printf("\n\n地雷数:%hu\t\t", mine_quantity);
    color(WHITE);
}

//刷新画面
void flash(unsigned short map[WIDTH][LENGTH]) {
    system("cls");
    print_map(map);
}

//检测周围是否存在地雷
void scan(unsigned short map[WIDTH][LENGTH], short y, short x) {
    _Bool flag = 0;
    unsigned short count = 0;

    for (short row = (y - 1); row <= (y + 1); row++) {
        for (short line = (x - 1); line <= (x + 1); line++) {
            //判断坐标合法性
            if ((row < 0) || (row >= WIDTH)) {
                continue;
            }
            else if ((line < 0) || (line >= LENGTH)) {
                continue;
            }
            //跳过已经检测过的地块
            else if ((map[row][line] > LABLE_SPACE) && (map[row][line] < LABLE_HIDDEN_MINE)) {
                continue;
            }

            if (map[row][line] == LABLE_HIDDEN_MINE) {
                flag = 1;
                count++;
            }
        }
    }

    //检测完后在自身位置记下周围的地雷数量
    if ((y >= 0) && (y < WIDTH) && (x >= 0) && (x < LENGTH)) {
        map[y][x] = count;
    }

    //递归检测直到检测到地雷
    if (flag == 0) {
        for (short row = (y - 1); row <= (y + 1); row++) {
            for (short line = (x - 1); line <= (x + 1); line++) {
                //判断坐标合法性
                if ((row < 0) || (row >= WIDTH)) {
                    continue;
                }
                else if ((line < 0) || (line >= LENGTH)) {
                    continue;
                }
                //跳过自身位置和已经检测过的地块
                else if ((row == y) && (line == x)) {
                    continue;
                }
                else if ((map[row][line] > LABLE_SPACE) && (map[row][line] < LABLE_HIDDEN_MINE)) {
                    continue;
                }

                //遇到没有被揭示的地块就继续检测
                if ((map[row][line] == LABLE_ICON)) {
                    scan(map, row, line);
                }
            }
        }
    }
}

//处理用户输入
unsigned short input(unsigned short map[WIDTH][LENGTH]) {
    unsigned short y = 0;
    unsigned short x = 0;

    printf("请输入坐标>:");
    while (1) {
        //判断坐标合法性
        if ((scanf("%hu%hu", &x, &y) == 2) && (y <= WIDTH) && (x <= LENGTH) && (y > 0) && (x > 0)) {
            break;
        }

        color(BLUSH);
        printf("\n\n输入错误，请重新输入");
        color(WHITE);
        clean();
        Sleep(2000);
        flash(map);
        printf("请输入坐标>:");
    }

    //判断是否踩雷
    if (map[y - 1][x - 1] == LABLE_HIDDEN_MINE) {
        return 1;
    }

    scan(map, (y - 1), (x - 1));
    return 0;
}

//游戏的主函数
void game(void) {
        unsigned short flag = 0;
        unsigned short map[WIDTH][LENGTH] = { 0 };

        initialize(map);
        mine_quantity = mine_counter(map);

        while (1) {
            flash(map);

            //踩到雷就结束游戏
            if (input(map)) {
                uncover(map);
                flash(map);
                color(BLUSH);
                printf("\n\n游戏结束\n\n");
                system("pause");
                break;
            }
            
            //所有的地雷被发现就胜利
            mine_quantity = mine_counter(map);
            if (mine_quantity == 0) {
                flash(map);
                color(LIGHT_GREEN);
                printf("\n\n恭喜你获得胜利\n\n");
                system("pause");
                break;
            }
        }
}