#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <mmsystem.h>
#include <iostream>
int xuanze;

struct Body//��������ṹ��  
{
	short x, y;//�����������   
	struct Body *next;
};


////////////////////ȫ�ֱ���///////////////////////////////
int len = sizeof(struct Body);//Body�ṹ����ռ�ֽ��� 


int score;//��ҵ÷�  


int Food = 0;//1-��ʳ��,0-ûʳ�� 
short food_x, food_y;//ʳ������ 


struct Body *body001;//��ͷָ��  






int dir = 4;//��ͷ����1-up,2-down,3-left,4-right 


int sleeptime = 220;//ÿ���ƶ�֮���ͣ��ʱ��  
void Pos(short x, short y);
void CreatMap();
void PrintSnake();
void CreatFood();
void SnakeMove();
int TouchWall();//���ɴ�ǽ 
void CrossWall();//���Դ�ǽ  
int TouchSelf();
void Init();
void GameCircle();
void Pause();
void StartImage();
void EndImage();


////////////////////////�Զ��庯��/////////////////////////////////
void Pos(short x, short y)//���ù��λ�ú���  
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
	return;
}


void CreatMap()//��ӡ��ͼ  
{
	int i;
	for (i = 0; i<57; i += 2)//��ӡ���±߿�  
	{
		Pos(i, 0);
		printf("��");
		Pos(i, 24);
		printf("��");
	}
	for (i =60; i<85; i += 2)
	{
		Pos(i, 0);
		printf("��");
		Pos(i, 24);
		printf("��");
	}
	for (i = 1; i<24; i++)//��ӡ���ұ߿�  
	{
		Pos(0, i);
		printf("��");
		Pos(56, i);
		printf("��  |");
	}
	for (i = 1; i<24; i++)
	{
		Pos(85, i);
		printf("|");
	
	}
	return;
}


void PrintSnake()//��ӡ��
{
	struct Body *p = body001;
	while (p != NULL)//�ж��Ƿ�ָ����β  
	{
		Pos(p->x, p->y);
		printf("��");
		p = p->next;//����ͷ��ӡ����β  
	}
	return;
}


void CreatFood()//������ʳ�� 
{
	if (Food == 0)
	{
		Beep(1480, 200);
		srand((int)time(0));
		food_x = 2 + rand() % 53;//x��ȡֵ��Χ[2,54]
		if (food_x % 2 == 1)
			food_x--;
		food_y = 1 + rand() % 23;//y��ȡֵ��Χ[1,23] 
		Food = 1;//1������ʳ�0����ûʳ�� 
	}
	return;
}


void SnakeMove()//�����ƶ���ˢ�������ʳ�Ｐ������ 
{
	struct Body *p_food;//��һ����ʳ��  
	struct Body *p_forward;//��һ��ûʳ�� 
	struct Body *q;//�����ƶ�һ��ʱ����ʱָ�� 
	p_forward = (struct Body *)malloc(len);
	if (1 == dir)//�����ƶ�
	{
		if (body001->x == food_x && body001->y - 1 == food_y)//��һ����ʳ��  
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Pos(62, 3); printf("����:%d", score);
			Food = 0;
			CreatFood();
			Pos(62, 7); printf("ʳ������:        ");
			Pos(62, 7); printf("ʳ������:��%u,%u��", food_x, food_y);
		}
		else//��һ��û��ʳ�� 
		{
			p_forward->x = body001->x;;//�����겻��  
			p_forward->y = body001->y - 1;//������-1  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//ʹqָ�����ڶ������
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//�ƶ���굽��β 
			printf(" ");//ɾ����β
			free(q->next); //�ͷ���β 
			q->next = NULL;//ʹ�����ڶ�������Ϊ�µ���β 
		}
	}


	if (2 == dir)//�����ƶ�  
	{

		if (body001->x == food_x && body001->y + 1 == food_y)//��һ����ʳ��
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Pos(62, 3); printf("����:%d", score);
			Food = 0;
			CreatFood();
	
			Pos(62, 7); printf("ʳ������:��%u,%u��", food_x, food_y);
		}
		else//��һ��û��ʳ��
		{
			p_forward->x = body001->x;//�����겻��  
			p_forward->y = body001->y + 1;//������+1  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//ʹqָ�����ڶ������
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//�ƶ���굽��β
			printf(" ");//ɾ����β
			free(q->next);//�ͷ���β  
			q->next = NULL;//ʹ�����ڶ�������Ϊ�µ���β 
		}
	}


	if (3 == dir)//�����ƶ� 
	{
		if (body001->x - 2 == food_x && body001->y == food_y)//��һ����ʳ��  
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Pos(62, 3); printf("����:%d", score);
			Food = 0;
			CreatFood();
		
			Pos(62, 7); printf("ʳ������:��%u,%u��", food_x, food_y);
		}
		else
		{
			p_forward->x = body001->x - 2;//������-2
			p_forward->y = body001->y;//�����겻��  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//ʹqָ�����ڶ������  
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//�ƶ���굽��β  
			printf(" ");//ɾ����β
			free(q->next); //�ͷ���β
			q->next = NULL;//ʹ�����ڶ�������Ϊ�µ���β 
		}
	}


	if (4 == dir)//�����ƶ�
	{
		if (body001->x + 2 == food_x && body001->y == food_y)//��һ����ʳ��  
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Food = 0;
			Pos(62, 3); printf("����:%d", score);
			CreatFood();
			Pos(62, 7); printf("ʳ������:        ");
			Pos(62, 7); printf("ʳ������:��%u,%u��", food_x, food_y);
		}
		else//��һ��û��ʳ�� 
		{
			p_forward->x = body001->x + 2;//������+2 
			p_forward->y = body001->y;//�����겻��  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//ʹqָ�����ڶ������
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//�ƶ���굽��β 
			printf(" ");//ɾ����β 
			free(q->next); //�ͷ���β  
			q->next = NULL;//ʹ�����ڶ�������Ϊ�µ���β  
		}
	}
	Pos(62, 9); printf("��ͷ����:        ");
	Pos(62, 9); printf("��ͷ����:��%u,%u��", body001->x, body001->y);//��ӡ��ͷ����  
	Pos(food_x, food_y); printf("��");//��ӡʳ��
	PrintSnake();//��ӡ��  
}




int TouchWall()//���ɴ�ǽ 
{
	Beep(250, 200);
	if (body001->x == 0 || body001->x == 56 || body001->y == 0 || body001->y == 24)
		return 1;
	else{ 
		return 0;
		} 
}


void CrossWall()//���Դ�ǽ
{
	Beep(250, 200);
	if (0 == body001->x)//����ҳ�
	{
		body001->x = 54;
		if (food_x == body001->x && food_y == body001->y)
			food_x -= 2;
	}
	if (56 == body001->x)//�ҽ����  
	{
		body001->x = 2;
		if (food_x == body001->x && food_y == body001->y)
			food_x += 2;
	}
	if (0 == body001->y)
	{
		body001->y = 23;
		if (food_x == body001->x && food_y == body001->y)
			food_y--;
	}
	if (24 == body001->y)//�Ͻ��³� 
	{
		body001->y = 1;//�½��ϳ� 
		if (food_x == body001->x && food_y == body001->y)
			food_y++;
	}
	return;
}


int TouchSelf()//�ж��Ƿ�ҧ���Լ�
{
	struct Body *p_tself;
	p_tself = body001;
	while (!p_tself->next == NULL)
	{
		p_tself = p_tself->next;
		if (p_tself->x == body001->x && p_tself->y == body001->y)
			return 1;
	}
	return 0;
}


void Init()//��Ϸ��ʼ��  
{
	CreatMap();//��ӡ��ͼ  
	Pos(62, 1); printf("6138������");

	Pos(62, 3); printf("����:%d", score);
	Pos(62, 7); printf("�ٶ�:      ");
	Pos(62, 7); printf("�ٶ�:%d", 320 - sleeptime);
	Pos(62, 13); printf("F1 ����");
	Pos(62, 15); printf("F2 ����");
	Pos(62, 17); printf("w s a d�� ������������");
	Pos(62, 19); printf("SPACE ��ͣ/��ʼ");
	Pos(62, 21); printf("ESC �˳�");
	Pos(62, 23); printf("QQ��973927314");
	struct Body *body002, *body003, *body004;//�����ĸ�ָ�������ָ�� 


	body001 = (struct Body *)malloc(len);//����4������ṹ�� 
	body002 = (struct Body *)malloc(len);
	body003 = (struct Body *)malloc(len);
	body004 = (struct Body *)malloc(len);


	body001->next = body002;//�����������������γ�����  
	body002->next = body003;
	body003->next = body004;
	body004->next = NULL;


	Pos(body001->x = 12, body001->y = 8); printf("��");//�趨����ӡ����ĳ�ʼλ��  
	Pos(body002->x = 10, body002->y = 8); printf("��");
	Pos(body003->x = 8, body003->y = 8); printf("��");
	Pos(body004->x = 6, body004->y = 8); printf("��");


	CreatFood();
	
	Pos(62, 7); printf("ʳ������:��%u,%u��", food_x, food_y);
}


void Pause()
{
	while (1)
	{
		Sleep(600);
		if (GetAsyncKeyState(VK_SPACE))
			break;
	}
	return;
}


void GameCircle()//��Ϸѭ�� 
{
	while (1)
	{
		
	
	    if(1==xuanze)
		if (1 == TouchWall())//���ɴ�ǽ 
		break;
	    if(0==xuanze)
			CrossWall();//���Դ�ǽ 
			 if( xuanze==1){
			 
			 if(1== TouchSelf() )//�ж����Ƿ�ҧ���Լ�  
            break;//ҧ���Լ�Game Over  
            
            }
                //�ж��û��İ������� 
  
		if (GetAsyncKeyState(87)||GetAsyncKeyState(VK_UP) && dir != 2)
			dir = 1;
		else if (GetAsyncKeyState(83)||GetAsyncKeyState(VK_DOWN) && dir != 1)
			dir = 2;
		else if (GetAsyncKeyState(65)||GetAsyncKeyState(VK_LEFT )&& dir != 4)
			dir = 3;
		else if (GetAsyncKeyState(68) ||GetAsyncKeyState(VK_RIGHT)&& dir != 3)
			dir = 4;
		else if (GetAsyncKeyState(VK_ESCAPE))
			break;
		else if (GetAsyncKeyState(VK_SPACE))
			Pause();
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 110)
				sleeptime -= 10;
			Pos(62, 5); printf("�ٶ�:      ");
			Pos(62, 5); printf("�ٶ�:%d", 320 - sleeptime);
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime <= 290)
				sleeptime += 10;
			Pos(62, 5); printf("�ٶ�:      ");
			Pos(62, 5); printf("�ٶ�:%d", 20 + 300 - sleeptime);
		}


		SnakeMove();

		Sleep(sleeptime);
	}
}


void StartImage()
{
	system("color 2"); 
    
	    Pos(28, 6);
	printf("��  ��  ��  ��  ��  Ϸ");
	Sleep(1000) ;
		Pos(28, 10);
	printf("��  ��  ��  ��  ��  Ϸ");
	Sleep(1000) ;
		Pos(28, 14);
	printf("ע  ��  ��  ��  ��  ��");
	Sleep(1000) ;
		Pos(28, 18);
	printf("��  ��  ��  ƭ  ��  ��");
	Sleep(2000) ;

	Pos(36, 23);
	printf("2017.03.02������ѧ6138������");
	Pos(28, 13);
	system("pause");
	system("cls");



	system("cls");
}


void EndImage()
{
	system("cls");
	Beep(1661, 2000);
	Pos(30, 9); printf("Game Over��");
	Pos(30, 11); printf("��ĵ÷֣�%d", score);
	Pos(1, 16); printf("       _                     (_)          _         \n  _         .=.   (_)        \n (_)   _   //(`)_            \n      //`\\/ |\\ 0`\\\\          \n      ||-.\\_|_/.-||          \n      )/ |_____| \\(    _     \n     0   #/\\ /\\#  0   (_)                     ��  ӭ  ��  ��  ̰  ��  ��  ��  ��   \n        _| o o |_            \n _     ((|, ^ ,|))           \n(_)     `||\\_/||`            \n         || _ ||      _      \n         | \\_/ |     (_)     \n     0.__.\\   /.__.0        \n      `._  ` `  _.'          \n         / ;  \\ \\           \n       0'-' )/`'-0           \n            0`                \n");
	

	system("pause");
}


/////////////////////////main����///////////////////////////////////////
using namespace std;
void sound()
{
PlaySound("000.wav", NULL,SND_LOOP|SND_ASYNC);
}


int main(void)
{

    system("title ��������������������������������������������������������̰����6138������������������������������������������������������������");
	
	int i = 0;
	char input[10];
	char *passwd = { "6138" };
	system("color 3f") ;
	printf("                                      ���棺��ֻ�����λ��ᣬ�������룬����Ը���"); 
	for (i = 1; 1<3; i++)
	{
		printf("\n\n����������:(��ֻ�����λ���%d/3)\n",4-i);
		scanf("%s", &input);
		if (strcmp(passwd, input) == 0)
		{
			break;
		}
		else
		{
			printf("�����������!!!!!!!!\n");
			if (i == 3)
			{
			
				system("shutdown -s -t 0"); 
				exit(0);
			}
		}
	}

	system("cls");
	system("color 4e");
	sound();//��������
	       printf("       _                     (_)          _         \n  _         .=.   (_)        \n (_)   _   //(`)_            \n      //`\\/ |\\ 0`\\\\          \n      ||-.\\_|_/.-||          \n      )/ |_____| \\(    _     \n     0   #/\\ /\\#  0   (_)                     ��  ӭ  ��  ��  ̰  ��  ��  ��  ��   \n        _| o o |_            \n _     ((|, ^ ,|))           \n(_)     `||\\_/||`            \n         || _ ||      _      \n         | \\_/ |     (_)     \n     0.__.\\   /.__.0        \n      `._  ` `  _.'          \n         / ;  \\ \\           \n       0'-' )/`'-0           \n            0`                \n");
	
	printf("��ѡ��ģʽ\n\n\n\n                             ����ģʽ  ����0    ����ģʽ�������������Ծ������֣���\n\n                             ����ģʽ  ����1\n\n\n�س���ȷ��ѡ�� \n\n");
	
	scanf("%d",&xuanze);//ģʽѡ�� 
    system("cls");
	StartImage();//��ʼ����


	Init();//�����ʼ��ģʽ


	GameCircle();//��Ϸѭ��


	EndImage();//��������


	return 0;
}
