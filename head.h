//�ж�ͷ�ļ��Ƿ��ظ�����
#ifndef _MINE_CLEARANCE_
#define _MINE_CLEARANCE_

//��ͼ����
#define LENGTH 16
#define WIDTH 16
//��ͼ�ܴ�С
#define SIZE LENGTH * WIDTH
//������
#define MINE 25
//�����ڱ����ʾ�ڵ�ͼ�ϵ�ͼ��
#define LABLE_SPACE 0
#define LABLE_HIDDEN_MINE 9
#define LABLE_MINE 10
#define LABLE_ICON 11

void color(const unsigned short textcolor);																//�ı�������ַ�����ɫ
void menu(void);																						//���ڴ�ӡ�˵�
void clean(void);																						//����������뻺����
void initialize(unsigned short map[WIDTH][LENGTH]);														//��ʼ������
void uncover(unsigned short map[WIDTH][LENGTH]);														//��ʾ���еĵ���
unsigned short mine_counter(unsigned short map[WIDTH][LENGTH]);											//���׼�����
unsigned short mine_scan(unsigned short map[WIDTH][LENGTH], short y, short x);							//ɨ�������Χ
void print_map(unsigned short map[WIDTH][LENGTH]);														//��ӡ��ͼ
void flash(unsigned short map[WIDTH][LENGTH]);															//ˢ�»���
unsigned short input(unsigned short map[WIDTH][LENGTH]);												//�����û�����
void scan(unsigned short map[WIDTH][LENGTH], short y, short x);											//ɨ���û������������Χ
void game(void);																						//������Ϸ

#endif