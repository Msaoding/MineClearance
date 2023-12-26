//判断头文件是否被重复包含
#ifndef _MINE_CLEARANCE_
#define _MINE_CLEARANCE_

//地图长宽
#define LENGTH 16
#define WIDTH 16
//地图总大小
#define SIZE LENGTH * WIDTH
//地雷数
#define MINE 25
//用于在标记显示在地图上的图标
#define LABLE_SPACE 0
#define LABLE_HIDDEN_MINE 9
#define LABLE_MINE 10
#define LABLE_ICON 11

void color(const unsigned short textcolor);																//改变输出的字符的颜色
void menu(void);																						//用于打印菜单
void clean(void);																						//用于清空输入缓冲区
void initialize(unsigned short map[WIDTH][LENGTH]);														//初始化数组
void uncover(unsigned short map[WIDTH][LENGTH]);														//揭示所有的地雷
unsigned short mine_counter(unsigned short map[WIDTH][LENGTH]);											//地雷计数器
unsigned short mine_scan(unsigned short map[WIDTH][LENGTH], short y, short x);							//扫描地雷周围
void print_map(unsigned short map[WIDTH][LENGTH]);														//打印地图
void flash(unsigned short map[WIDTH][LENGTH]);															//刷新画面
unsigned short input(unsigned short map[WIDTH][LENGTH]);												//处理用户输入
void scan(unsigned short map[WIDTH][LENGTH], short y, short x);											//扫描用户输入的坐标周围
void game(void);																						//运行游戏

#endif