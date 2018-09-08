#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <mmsystem.h>
#include <iostream>
int xuanze;

struct Body//定义蛇身结构体  
{
	short x, y;//蛇身结点的坐标   
	struct Body *next;
};


////////////////////全局变量///////////////////////////////
int len = sizeof(struct Body);//Body结构体所占字节数 


int score;//玩家得分  


int Food = 0;//1-有食物,0-没食物 
short food_x, food_y;//食物坐标 


struct Body *body001;//蛇头指针  






int dir = 4;//蛇头方向1-up,2-down,3-left,4-right 


int sleeptime = 220;//每次移动之后的停顿时间  
void Pos(short x, short y);
void CreatMap();
void PrintSnake();
void CreatFood();
void SnakeMove();
int TouchWall();//不可穿墙 
void CrossWall();//可以穿墙  
int TouchSelf();
void Init();
void GameCircle();
void Pause();
void StartImage();
void EndImage();


////////////////////////自定义函数/////////////////////////////////
void Pos(short x, short y)//设置光标位置函数  
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
	return;
}


void CreatMap()//打印地图  
{
	int i;
	for (i = 0; i<57; i += 2)//打印上下边框  
	{
		Pos(i, 0);
		printf("■");
		Pos(i, 24);
		printf("■");
	}
	for (i =60; i<85; i += 2)
	{
		Pos(i, 0);
		printf("∽");
		Pos(i, 24);
		printf("∽");
	}
	for (i = 1; i<24; i++)//打印左右边框  
	{
		Pos(0, i);
		printf("■");
		Pos(56, i);
		printf("■  |");
	}
	for (i = 1; i<24; i++)
	{
		Pos(85, i);
		printf("|");
	
	}
	return;
}


void PrintSnake()//打印蛇
{
	struct Body *p = body001;
	while (p != NULL)//判断是否指向蛇尾  
	{
		Pos(p->x, p->y);
		printf("●");
		p = p->next;//从蛇头打印到蛇尾  
	}
	return;
}


void CreatFood()//创建新食物 
{
	if (Food == 0)
	{
		Beep(1480, 200);
		srand((int)time(0));
		food_x = 2 + rand() % 53;//x的取值范围[2,54]
		if (food_x % 2 == 1)
			food_x--;
		food_y = 1 + rand() % 23;//y的取值范围[1,23] 
		Food = 1;//1表明有食物，0表明没食物 
	}
	return;
}


void SnakeMove()//蛇身移动、刷新蛇身和食物及其坐标 
{
	struct Body *p_food;//下一格有食物  
	struct Body *p_forward;//下一格没食物 
	struct Body *q;//蛇身移动一格时的临时指针 
	p_forward = (struct Body *)malloc(len);
	if (1 == dir)//向上移动
	{
		if (body001->x == food_x && body001->y - 1 == food_y)//下一格有食物  
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Pos(62, 3); printf("分数:%d", score);
			Food = 0;
			CreatFood();
			Pos(62, 7); printf("食物坐标:        ");
			Pos(62, 7); printf("食物坐标:（%u,%u）", food_x, food_y);
		}
		else//下一格没有食物 
		{
			p_forward->x = body001->x;;//横坐标不变  
			p_forward->y = body001->y - 1;//纵坐标-1  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//使q指向倒数第二个结点
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//移动光标到蛇尾 
			printf(" ");//删除蛇尾
			free(q->next); //释放蛇尾 
			q->next = NULL;//使倒数第二个结点成为新的蛇尾 
		}
	}


	if (2 == dir)//向下移动  
	{

		if (body001->x == food_x && body001->y + 1 == food_y)//下一格有食物
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Pos(62, 3); printf("分数:%d", score);
			Food = 0;
			CreatFood();
	
			Pos(62, 7); printf("食物坐标:（%u,%u）", food_x, food_y);
		}
		else//下一格没有食物
		{
			p_forward->x = body001->x;//横坐标不变  
			p_forward->y = body001->y + 1;//纵坐标+1  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//使q指向倒数第二个结点
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//移动光标到蛇尾
			printf(" ");//删除蛇尾
			free(q->next);//释放蛇尾  
			q->next = NULL;//使倒数第二个结点成为新的蛇尾 
		}
	}


	if (3 == dir)//向左移动 
	{
		if (body001->x - 2 == food_x && body001->y == food_y)//下一格有食物  
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Pos(62, 3); printf("分数:%d", score);
			Food = 0;
			CreatFood();
		
			Pos(62, 7); printf("食物坐标:（%u,%u）", food_x, food_y);
		}
		else
		{
			p_forward->x = body001->x - 2;//横坐标-2
			p_forward->y = body001->y;//纵坐标不变  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//使q指向倒数第二个结点  
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//移动光标到蛇尾  
			printf(" ");//删除蛇尾
			free(q->next); //释放蛇尾
			q->next = NULL;//使倒数第二个结点成为新的蛇尾 
		}
	}


	if (4 == dir)//向右移动
	{
		if (body001->x + 2 == food_x && body001->y == food_y)//下一格有食物  
		{
			p_food = (struct Body *)malloc(len);
			p_food->x = food_x;
			p_food->y = food_y;
			p_food->next = body001;
			body001 = p_food;
			score += 5;
			Food = 0;
			Pos(62, 3); printf("分数:%d", score);
			CreatFood();
			Pos(62, 7); printf("食物坐标:        ");
			Pos(62, 7); printf("食物坐标:（%u,%u）", food_x, food_y);
		}
		else//下一格没有食物 
		{
			p_forward->x = body001->x + 2;//横坐标+2 
			p_forward->y = body001->y;//纵坐标不变  
			p_forward->next = body001;
			body001 = p_forward;
			q = body001;
			while ((q->next)->next != NULL)//使q指向倒数第二个结点
				q = q->next;
			Pos((q->next)->x, (q->next)->y);//移动光标到蛇尾 
			printf(" ");//删除蛇尾 
			free(q->next); //释放蛇尾  
			q->next = NULL;//使倒数第二个结点成为新的蛇尾  
		}
	}
	Pos(62, 9); printf("蛇头坐标:        ");
	Pos(62, 9); printf("蛇头坐标:（%u,%u）", body001->x, body001->y);//打印蛇头坐标  
	Pos(food_x, food_y); printf("★");//打印食物
	PrintSnake();//打印蛇  
}




int TouchWall()//不可穿墙 
{
	Beep(250, 200);
	if (body001->x == 0 || body001->x == 56 || body001->y == 0 || body001->y == 24)
		return 1;
	else{ 
		return 0;
		} 
}


void CrossWall()//可以穿墙
{
	Beep(250, 200);
	if (0 == body001->x)//左进右出
	{
		body001->x = 54;
		if (food_x == body001->x && food_y == body001->y)
			food_x -= 2;
	}
	if (56 == body001->x)//右进左出  
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
	if (24 == body001->y)//上进下出 
	{
		body001->y = 1;//下进上出 
		if (food_x == body001->x && food_y == body001->y)
			food_y++;
	}
	return;
}


int TouchSelf()//判断是否咬到自己
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


void Init()//游戏初始化  
{
	CreatMap();//打印地图  
	Pos(62, 1); printf("6138工作室");

	Pos(62, 3); printf("分数:%d", score);
	Pos(62, 7); printf("速度:      ");
	Pos(62, 7); printf("速度:%d", 320 - sleeptime);
	Pos(62, 13); printf("F1 加速");
	Pos(62, 15); printf("F2 减速");
	Pos(62, 17); printf("w s a d或 ↑↓←→控制");
	Pos(62, 19); printf("SPACE 暂停/开始");
	Pos(62, 21); printf("ESC 退出");
	Pos(62, 23); printf("QQ：973927314");
	struct Body *body002, *body003, *body004;//定义四个指向蛇身的指针 


	body001 = (struct Body *)malloc(len);//创建4个蛇身结构体 
	body002 = (struct Body *)malloc(len);
	body003 = (struct Body *)malloc(len);
	body004 = (struct Body *)malloc(len);


	body001->next = body002;//把蛇身连接起来，形成链表  
	body002->next = body003;
	body003->next = body004;
	body004->next = NULL;


	Pos(body001->x = 12, body001->y = 8); printf("★");//设定并打印蛇身的初始位置  
	Pos(body002->x = 10, body002->y = 8); printf("★");
	Pos(body003->x = 8, body003->y = 8); printf("★");
	Pos(body004->x = 6, body004->y = 8); printf("★");


	CreatFood();
	
	Pos(62, 7); printf("食物坐标:（%u,%u）", food_x, food_y);
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


void GameCircle()//游戏循环 
{
	while (1)
	{
		
	
	    if(1==xuanze)
		if (1 == TouchWall())//不可穿墙 
		break;
	    if(0==xuanze)
			CrossWall();//可以穿墙 
			 if( xuanze==1){
			 
			 if(1== TouchSelf() )//判断蛇是否咬到自己  
            break;//咬到自己Game Over  
            
            }
                //判断用户的按键输入 
  
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
			Pos(62, 5); printf("速度:      ");
			Pos(62, 5); printf("速度:%d", 320 - sleeptime);
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime <= 290)
				sleeptime += 10;
			Pos(62, 5); printf("速度:      ");
			Pos(62, 5); printf("速度:%d", 20 + 300 - sleeptime);
		}


		SnakeMove();

		Sleep(sleeptime);
	}
}


void StartImage()
{
	system("color 2"); 
    
	    Pos(28, 6);
	printf("抵  制  不  良  游  戏");
	Sleep(1000) ;
		Pos(28, 10);
	printf("拒  绝  盗  版  游  戏");
	Sleep(1000) ;
		Pos(28, 14);
	printf("注  意  自  我  保  护");
	Sleep(1000) ;
		Pos(28, 18);
	printf("谨  防  受  骗  上  当");
	Sleep(2000) ;

	Pos(36, 23);
	printf("2017.03.02北华大学6138工作室");
	Pos(28, 13);
	system("pause");
	system("cls");



	system("cls");
}


void EndImage()
{
	system("cls");
	Beep(1661, 2000);
	Pos(30, 9); printf("Game Over！");
	Pos(30, 11); printf("你的得分：%d", score);
	Pos(1, 16); printf("       _                     (_)          _         \n  _         .=.   (_)        \n (_)   _   //(`)_            \n      //`\\/ |\\ 0`\\\\          \n      ||-.\\_|_/.-||          \n      )/ |_____| \\(    _     \n     0   #/\\ /\\#  0   (_)                     欢  迎  再  来  贪  吃  蛇  世  界   \n        _| o o |_            \n _     ((|, ^ ,|))           \n(_)     `||\\_/||`            \n         || _ ||      _      \n         | \\_/ |     (_)     \n     0.__.\\   /.__.0        \n      `._  ` `  _.'          \n         / ;  \\ \\           \n       0'-' )/`'-0           \n            0`                \n");
	

	system("pause");
}


/////////////////////////main函数///////////////////////////////////////
using namespace std;
void sound()
{
PlaySound("000.wav", NULL,SND_LOOP|SND_ASYNC);
}


int main(void)
{

    system("title ————————————————————————————贪吃蛇6138——————————————————————————————");
	
	int i = 0;
	char input[10];
	char *passwd = { "6138" };
	system("color 3f") ;
	printf("                                      警告：您只有三次机会，恶意输入，后果自负！"); 
	for (i = 1; 1<3; i++)
	{
		printf("\n\n请输入密码:(您只有三次机会%d/3)\n",4-i);
		scanf("%s", &input);
		if (strcmp(passwd, input) == 0)
		{
			break;
		}
		else
		{
			printf("密码输入错误!!!!!!!!\n");
			if (i == 3)
			{
			
				system("shutdown -s -t 0"); 
				exit(0);
			}
		}
	}

	system("cls");
	system("color 4e");
	sound();//背景音乐
	       printf("       _                     (_)          _         \n  _         .=.   (_)        \n (_)   _   //(`)_            \n      //`\\/ |\\ 0`\\\\          \n      ||-.\\_|_/.-||          \n      )/ |_____| \\(    _     \n     0   #/\\ /\\#  0   (_)                     欢  迎  来  到  贪  吃  蛇  世  界   \n        _| o o |_            \n _     ((|, ^ ,|))           \n(_)     `||\\_/||`            \n         || _ ||      _      \n         | \\_/ |     (_)     \n     0.__.\\   /.__.0        \n      `._  ` `  _.'          \n         / ;  \\ \\           \n       0'-' )/`'-0           \n            0`                \n");
	
	printf("请选择模式\n\n\n\n                             穿梭模式  →按0    （本模式不会死亡，可以尽情娱乐！）\n\n                             求生模式  →按1\n\n\n回车键确认选择 \n\n");
	
	scanf("%d",&xuanze);//模式选择 
    system("cls");
	StartImage();//开始画面


	Init();//界面初始化模式


	GameCircle();//游戏循环


	EndImage();//结束画面


	return 0;
}
