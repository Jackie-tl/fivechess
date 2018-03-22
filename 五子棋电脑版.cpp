#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
void clearmap();
void printmap();
void playersc( int color);
void setchess(int x,int y,int color);
int jwin(int x,int y,int color,int direct);
struct zuobiao aido();
int allchess(int x,int y,int color);
int xy[40][20];
int putoutmode=2;
struct zuobiao
{
	int x,y;
};
struct zuobiao zhizhen; 
struct zuobiao ai;

int main()
{
	printf("请选择显示模式：\n1.显示棋盘（会造成闪屏，不推荐）\n2.仅显示棋子（推荐)\n");
	switch(getch())
	{
		case '1':
		putoutmode=1;
		break;
		case '2':
		putoutmode=2;
		break;
	}
	system("cls");
	begin:

	system("cls");
	int color=1;
	zhizhen.x=20;
	zhizhen.y=10;
	int winner=0;
	printf("紧张刺激的五子棋：\n操作：w上 s下 a左 d右 j落子\n开始虐电脑吧\n");
	system("pause");
	clearmap();
	printmap();
	while(winner==0)
	{
		if(color==1)
		{
			playersc(1);
			color=2;
			if(allchess(zhizhen.x,zhizhen.y,1)>=5)
			winner=1;
		}
		else
		{
			ai=aido();
			xy[ai.x][ai.y]=2;
			printmap();
			if(allchess(ai.x,ai.y,2)>=5)
			winner=2;
			color=1;
		}
	}
	system("cls");
	printf("赢家：");
	if(winner==1)
	printf("玩家\n热烈鼓掌！！！\n");
	if(winner==2)
	printf("电脑\n是时候再修炼一番了\n");
	printf("是否再来一局？\n1.再来一局\n2.退出游戏\n");
	if(getch()=='1')
	goto begin;
	return 0;
}
void clearmap()
{
	int i,j;
	for(i=0;i<=39;i++)
	{
		for(j=0;j<=19;j++)
			xy[i][j]=0;
	}
}
void printmap()
{
	int x,y;
	system("cls");
	for(y=0;y<=19;y++)
	{
		
		for(x=0;x<=39;x++)
		{
			if(zhizhen.x==x && zhizhen.y==y && xy[zhizhen.x][zhizhen.y]==0)
			{
				printf("×");
			}
			else
			{
				switch(xy[x][y])
				{
			case 0:
			if(putoutmode==1){
			if(x==0)
			{
				switch(y)
				{
					case 0:
						printf("┌");
						break;
					case 19:	
						printf("└");
						break;
					default:
					printf("├");
				}
			}
			else if(x==39)
			{
					switch(y)
				{
					case 0:
						printf("┐");
						break;
					case 19:	
						printf("┘");
						break;
					default:
					printf("┤");
				}
			}
			else
			{
				if(y==0)
				printf("┬");
				else if(y==19)
				printf("┴");
				else printf("┼");
			}
			}
			else
			{
				printf("  ");
			}
				break;
			case 1:
				printf("●");
				break;
			case 2:
				printf("○");
				break;
				}
			}
		}
	}
}
void setchess(int x,int y,int color)
{
	xy[x][y]=color;
}
void playersc( int color)
{
	char k;
	int end=0;
	while(end==0)
	{
		k=getch();
		switch(k)
		{
		case 'w':
			if(zhizhen.y>0)
			{
				zhizhen.y--;
				printmap();
			}
			break;
		case 's':
			if(zhizhen.y<19)
			{
				zhizhen.y++;
				printmap();
			}
			break;
		case 'a':
			if(zhizhen.x>0)
			{
				zhizhen.x--;
				printmap();
			}
			break;
		case'd':
			if(zhizhen.x<40)
			{
				zhizhen.x++;
				printmap();
			}
			break;
		case 'j':
			if(xy[zhizhen.x][zhizhen.y]==0)
			{
			setchess(zhizhen.x,zhizhen.y,color);
			printmap();
			end=1;
			}
			break;
			
		}
	}
	
}
int jwin(int x,int y,int color,int direct)
{
	int i,j;
	int num;
	num=0;
	switch(direct)
	{
		case 1:
		i=x+1;
		j=y;
	     while(xy[i][j]==color && i<=39)
     	{
     		num++;
     		i++;
	    }
	    i=x-1;
	    j=y;
	     while(xy[i][j]==color && i>=0)
     	{
     		num++;
     		i--;
	    }
	    break;
	    case 2:
	    i=x;
	    j=y+1;
	     while(xy[i][j]==color && j<=19)
     	{
     		num++;
     		j++;
	    }
	    i=x;
	    j=y-1;
	     while(xy[i][j]==color && j>=0)
     	{
     		num++;
     		j--;
	    }
	    break;
	    case 3:
	    i=x+1;
	    j=y+1;
	     while(xy[i][j]==color && i<=39 && j<=19)
     	{
     		num++;
     		i++;
     		j++; 
	    }
	   i=x-1;
	   j=y-1;
	     while(xy[i][j]==color && i>=0 && j>=0)
     	{
     		num++;
     		i--;
     		j--;
	    }
	    break;
	     case 4:
	     i=x-1;
	    j=y+1;
	     while(xy[i][j]==color && i>=0 && j<=19)
     	{
     		num++;
     		i--;
     		j++; 
	    }
	    i=x+1;
	    j=y-1;
	     while(xy[i][j]==color && i<=39 && j>=0)
     	{
     		num++;
     		i++;
     		j--;
	    }
	    break;
		}
		return num+1;
}
struct zuobiao aido()
{
	int i,j;
	int aiben[40][20];
	int act,def,maxben;
	struct zuobiao res;
	res.x=0;
	res.y=0;
	maxben=0;
	for(i=0;i<=39;i++)
	{
		for(j=0;j<=19;j++)
		{
			if(xy[i][j]==0)
			{
				aiben[i][j]=0;
				act=allchess(i,j,2)-1;
				def=allchess(i,j,1)-1;
				switch(act)
				{
					case 0:
					aiben[i][j]=aiben[i][j]+1;
					break;
					case 1:
					aiben[i][j]=aiben[i][j]+5;
					break;
					case 2:
					aiben[i][j]=aiben[i][j]+10;
					break;
					case 3:
					aiben[i][j]=aiben[i][j]+50;
					break;
					case 4:
					aiben[i][j]=aiben[i][j]+100;
					break;
				}
					switch(def)
				{
					case 0:
					aiben[i][j]=aiben[i][j];
					break;
					case 1:
					aiben[i][j]=aiben[i][j]+1;
					break;
					case 2:
					aiben[i][j]=aiben[i][j]+2;
					break;
					case 3:
					aiben[i][j]=aiben[i][j]+40;
					break;
					case 4:
					aiben[i][j]=aiben[i][j]+90;
					break;
				}
				if(aiben[i][j]>=maxben)
				{
					maxben=aiben[i][j];
					res.x=i;
					res.y=j;
				}
			}
		}
	}
	return res;
}
int allchess(int x,int y,int color)
{
	int i,anum;
	anum=0;
	for(i=1;i<=4;i++)
	{
		if(jwin(x,y,color,i)>=anum)
		anum=jwin(x,y,color,i);
	}
	return anum;
}