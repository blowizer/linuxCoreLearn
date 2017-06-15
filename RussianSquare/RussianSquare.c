#include <stdio.h>

#include <string.h>

#include <sys/timeb.h>

#include <time.h>

#include <stdlib.h>

#include "keyboard/keyboard.h"

#include "linklist/linklist.h"

#include "dcirclelist/dcirclelist.h"

#define HIGH 24 //图形高度范围
#define	WIDTH 15 //图形宽度范围
#define MIDDLE (WIDTH / 2) //图形生成x位置
#define BWIDTH (2 * (WIDTH + 3)) //整个背景宽度
#define BHIGH (HIGH + 4)//整个背景高度

#define BC 0//背景颜色0
#define CS 8//8种颜色

#define Y_NEXT ((HIGH / 2) - 2)
#define X_NEXT (WIDTH + 4 + (MIDDLE / 2))
#define X_SEVEN_SHAPE (WIDTH + 5 + MIDDLE) 
#define X_SEVEN_NUMBER (X_SEVEN_SHAPE + 4)

typedef struct timeb TimeB;//timeb别名
typedef unsigned int Color;//定义Color类型

//每种图形的个数
static int ShapeNumber[7] = {0};

//每种图形打印时的颜色
static Color ShapeColor[7] = {0};

//方块位置相对基准点偏移量
typedef struct _block {
	int x;
	int y;
} Block;

//会用到的方块相对基准点信息
static const Block block_kinds[][5] = {
	{{-2,-2},{-2,-1},{-2, 0},{-2, 1},{-2, 2}},
	{{-1,-2},{-1,-1},{-1, 0},{-1, 1},{-1, 2}},
	{{ 0,-2},{-0,-1},{ 0, 0},{ 0, 1},{ 0, 2}},
	{{ 1,-2},{ 1,-1},{ 1, 0},{ 1, 1},{ 1, 2}},
	{{ 2,-2},{ 2,-1},{ 2, 0},{ 2, 1},{ 2, 2}}
};

static const int X = 2;//基准点x在数组中位置
static const int Y = 2;//基准点y在数组中位置

//画方块、图形方式(背景，下一个图形，当前图形)
enum  DrawMethod { BackGround,NextShape,CurrentShape };

//移动图形方式(左，右，旋转，掉落)
enum  MoveMethod { Left,Right,Circle,Drop };

//下面的二维数组每个元素对应方块的填充类型
enum FilledSort { Empty,Filled };

//每个方块的填充类型和颜色，更真实一些，所以叫real block
typedef struct Real_Block {
	enum FilledSort fs;
	Color c;
} RBlock;


//二维数组Array,包含背景每个方块的信息：是否填充和颜色
static RBlock Array[HIGH][WIDTH] = {{Empty,BC}};

//枚举类型，表示在NextShape区域中打印信息的种类
enum PrintKind { Start,Normal,End,Time,Score,Lines,MaxLine,Count,Level,Next };

//获得8种颜色种的7种，除了BC
static int get_color ( ) {
	Color ret = rand() % CS;

	if ( ret == BC ) {
		ret = (ret + rand() % (CS - 1) + 1) % CS;			
	}

	return ret;
}

//打印信息的函数，在NextShape区域中打印
static void print ( int x,int y,enum PrintKind p,int num,Color c ) {//num 对于Start和End是颜色,对于其他种类是相关数据
	const int flag = (4+WIDTH <= x) && (x < BWIDTH-2) && (2 <= y) && (y < BHIGH-2) && (0 <= c) && (c < 8); 

	if ( flag == 1 ) {
		printf("\033[%d;%dH",y+2,2*x+1);
	
		switch ( p ) {
		case Start:
			printf("\033[%dm\033[%dmGame Start!",30+c,40+BC);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Normal:
			printf("\033[%dm\033[%dmGame Start!",30+BC,40+BC);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case End:
			printf("\033[%dm\033[%dmGame Over!",30+c,40+BC);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Time:
			printf("\033[%dm\033[%dmTime:",30+c,40+BC);
			printf("\033[%d;%dH",y+3,2*x+1);
			printf("\033[%dm\033[%dm%2d:%2d:%2d",30+c,40+BC,(num/3600),((num/60) % 60),(num%60));
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Lines:
			printf("\033[%dm\033[%dmLines:%d",30+c,40+BC,num);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case MaxLine:
			printf("\033[%dm\033[%dmMax Line:%d",30+c,40+BC,num);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Score:
			printf("\033[%dm\033[%dmScore:",30+c,40+BC);
			printf("\033[%d;%dH",y+3,2*x+1);
			printf("\033[%dm\033[%dm  %d",30+c,40+BC,num);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Count:
			printf("\033[%dm\033[%dm%d",30+c,40+BC,num);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Level:
			printf("\033[%dm\033[%dmLevel:%d",30+c,40+BC,num);
			printf("\033[0m");	
			fflush(stdout);
			break;
		case Next:
			printf("\033[%dm\033[%dmNext Shape:",30+c,40+BC);
			printf("\033[0m");	
			fflush(stdout);
			break;
		default:
			printf("\033[0m");	
			break;
		}
	}
}

//print各种图形的数目
static void print_shape_number ( int i,int count,Color c ) {		
	if ( (0<= i) && (i < 7) ) {
		if ( i < 2 ) {
			print(X_SEVEN_NUMBER,(4 + 2 * i),Count,count,c);
		} else if ( i < 5 ) {
			print(X_SEVEN_NUMBER,(1 + 4 * i),Count,count,c);
		} else if ( i == 5 ) {
			print(X_SEVEN_NUMBER,(4 * i),Count,count,c);
		} else if ( i == 6 ) {
			print(X_SEVEN_NUMBER,(4 * i - 1),Count,count,c);
		}
	}
}

//创建每一种图形一共7类
static LinkList * creat_one_shape ( const int i ) {
	LinkList * ret = LinkList_Creat();
	ret->header.data = (LinkListNodeData*)i;

	switch ( i ) {
	case 0:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y - 1)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y - 1)),LinkList_Length(ret));	
		break;
	case 1:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 2)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X - 1)) + (Y + 0)),LinkList_Length(ret));	
		break;
	case 2:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y - 1)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 1)),LinkList_Length(ret));	
		break;
	case 3:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 1)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y - 1)),LinkList_Length(ret));	
		break;
	case 4:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X - 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y - 1)),LinkList_Length(ret));	
		break;
	case 5:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X - 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X - 1)) + (Y - 1)),LinkList_Length(ret));	
		break;
	case 6:
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X - 1)) + (Y + 0)),LinkList_Length(ret));	
		LinkList_Insert(ret,(LinkListNodeData*)(*(block_kinds + (X + 0)) + (Y - 1)),LinkList_Length(ret));	
		break;
	default :
		LinkList_Destroy(ret);
		break;	
	} 	

//	printf("length = %d\n",ret->length);	
	return ret;
}

//向左旋转图形90度
void circle_left ( LinkList *list ) {
	const int flag = (list != NULL) && ((int)(list->header.data) != 0);

	if ( flag == 1 ) { 
		LinkListNode *cur = (LinkListNode*)list;
		cur = cur->next;
		int i = 0;
		int j = 0;
		int	length = LinkList_Length(list);
		
		if ( cur != NULL ) { //改变单链表里边四个node的data
			for ( int k=0;(k<length) && (cur != NULL);k++ ) {
				i = 4 - (((Block*)cur->data)->y + Y);
				j = ((Block*)cur->data)->x + X;
				cur->data = (LinkListNodeData*)(*(block_kinds + i) + j);
//				printf("(i=%d,j=%d)|(x|%2d),(y|%2d) ||",i,j,block_kinds[i][j].x,block_kinds[i][j].y);
				cur = cur->next;
			}
			
//			printf("\n");
		}	
	}
}

//生成一个图形
static LinkList * born_one_shape ( DCircleList * dlist ) {
	LinkList *ret = NULL;
	
	const int length_dlist = DCircleList_Length(dlist);
	int r = -1;

	if ( length_dlist > 0 ) {	
		r = rand() % length_dlist;
	}

	ret = DCircleList_Get(dlist,r);			
	
	const int length_ret = LinkList_Length(ret);
	int times = 0;//生成图形之后左旋的次数
	
	if ( length_ret > 0 ) {
		times = rand() % length_ret;
	}

	for (int i=0;i<times;i++ ) {
		circle_left(ret);	
	}		

	return ret;
}

//创建图形库
static DCircleList * creat_allkinds_shapes ( ) {
	DCircleList *ret = DCircleList_Creat();
	
	for ( int i=0;i<7;i++ ) {
		DCircleList_Insert(ret,(DCircleListNodeData*)creat_one_shape(i),DCircleList_Length(ret));
	}

	return ret;	
}

//画图形单元(一个方块),返回0表示成功
static int draw_element ( int x,int y,Color c,enum DrawMethod d ) {
	int ret = -1;
	int flag = 0;
	
	if ( d == CurrentShape ) {
		flag =  (0 <= x) && (x < WIDTH) && (0 <= y) && (y < HIGH) && (0 <= c) && (c <= CS);
	} else if ( d == BackGround ) {
		flag =  (0 <= x) && (x < BWIDTH) && (0 <= y) && (y < BHIGH) && (0 <= c) && (c <= CS);
	} else if ( d == NextShape ) {
		flag =  (4+WIDTH <= x) && (x < BWIDTH-2) && (2 <= y) && (y < BHIGH-2) && (0 <= c) && (c <= CS);
	} 

	if ( flag == 1 ) {
		if ( d == CurrentShape ) {
			printf("\033[%d;%dH",y+4,2*x+5);
		} else if ( (d == BackGround) || (d == NextShape) ) {
			printf("\033[%d;%dH",y+2,2*x+1);
		}

		printf("\033[%dm\033[%dm[]",30+c,40+c);
		printf("\033[0m");	
		fflush(stdout);
		
		ret = 0;
	}
	
	return ret;
}

//创建背景
static void creat_background ( ) {
	Color temp = rand() % CS;
	Color color = -1;		

	if ( temp == BC ) {
		color = (temp + rand() % (CS - 1) + 1) % CS;			
	} else {
		color =  temp;
	}

	int flag = 0;
	
//	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
	for ( int x=0;x<BWIDTH;x++ ) {
		for ( int y=0;y<BHIGH;y++ ) {
			flag = (((2 <= x) && (x < 2+WIDTH)) || ((4+WIDTH <= x) && (x < BWIDTH-2))) 
				&& (((2 <= y) && (y < BHIGH-2)));

			if ( flag == 1 ) {
				draw_element(x,y,BC,BackGround);
			} else {
				draw_element(x,y,color,BackGround);
			}
		}
	}	
}

//画图形
static void draw_shape ( int x,int y,Color color,LinkList *list,enum DrawMethod d ) {
	const int flag = (list != NULL);

	if ( flag == 1 ) {
		LinkListNode *cur = (LinkListNode*)list;
		int length = LinkList_Length(list);
		cur = cur->next;
	
		if ( cur != NULL ) {
			for ( int i=0;(i<length) && (cur != NULL);i++ ) {
				draw_element((x + ((Block*)(cur->data))->x),(y + ((Block*)(cur->data))->y),color,d);	
				cur = cur->next;
			}
		}	
	}
}

//画7种图形
static void draw_seven_shapes ( DCircleList *dlist) {
	int length = DCircleList_Length(dlist);
	LinkList *shape_one = NULL;
	int h = -1;

	Color temp = rand() % CS;
	Color c = -1;		

	if ( temp == BC ) {
		c = (temp + rand() % (CS - 1) + 1) % CS;			
	} else {
		c =  temp;
	}

	for ( int i=0;i<length;i++ ) {
		shape_one = (LinkList*)DCircleList_Get(dlist,i);
			
		h = (int)(shape_one->header.data);
		
		if ( (0<= h) && (h < length) ) {
			ShapeColor[h] = c;	
			
			if ( h < 2 ) {
				draw_shape(X_SEVEN_SHAPE,(4 + 2 * h),c,shape_one,NextShape);
				print(X_SEVEN_NUMBER,(4 + 2 * h),Count,0,c);
			} else if ( h < 5 ) {
				draw_shape(X_SEVEN_SHAPE,(1 + 4 * h),c,shape_one,NextShape);
				print(X_SEVEN_NUMBER,(1 + 4 * h),Count,0,c);
			} else if ( h == 5 ) {
				draw_shape(X_SEVEN_SHAPE,(4 * h),c,shape_one,NextShape);
				print(X_SEVEN_NUMBER,4 * h,Count,0,c);
			} else if ( h == 6 ) {
				draw_shape(X_SEVEN_SHAPE,(4 * h - 1),c,shape_one,NextShape);
				print(X_SEVEN_NUMBER,(4 * h - 1),Count,0,c);
			}

			c = (((c + 1)) % CS == BC) ? ((c + 2) % CS) : ((c + 1) % CS);
				
		}
	}
}

//向下掉落图形
static void drop_shape ( int *x,int *y,Color color,LinkList *list ) {
	draw_shape(*x,*y,BC,list,CurrentShape);//清空上一次生成的图形	
	draw_shape(*x,++(*y),color,list,CurrentShape);//重新生成的图形
}

//向左移动图形
static void move2left ( int *x,int *y,Color color,LinkList *list ) {
	draw_shape(*x,*y,BC,list,CurrentShape);//清空上一次生成的图形	
	draw_shape(--(*x),(*y),color,list,CurrentShape);//重新生成的图形
}

//向右移动图形
static void move2right ( int *x,int *y,Color color,LinkList *list ) {
	draw_shape(*x,*y,BC,list,CurrentShape);//清空上一次生成的图形	
	draw_shape(++(*x),(*y),color,list,CurrentShape);//重新生成的图形
}

//旋转图形(向左)
static void circle_shape ( int x,int y,Color color,LinkList *list ) {
	draw_shape(x,y,BC,list,CurrentShape);//清空上一次生成的图形	

	circle_left(list);
		
	draw_shape(x,y,color,list,CurrentShape);//重新生成一个图形	
}

//space操作之后返回y的位置
static int get2down ( int x,int y,LinkList *list ) {
	int ret = -5;
	const int flag = (list != NULL);

	if ( flag == 1 ) {
		int yc = y + 1;

		for ( ;yc<HIGH;yc++ ) { //yc，即y current
			LinkListNode *cur = (LinkListNode*)list;
			int length = LinkList_Length(list);
			cur = cur->next;
	
			if ( cur != NULL ) {
				int i = -1;
				int j = -1;
				int k = 0;
				int flag_break = 0;//退出循环信息

				for ( k=0;(k<length) && (cur != NULL);k++ ) {
					i = ((Block*)(cur->data))->x + x;
					j = ((Block*)(cur->data))->y + yc;
					const int flag_i = (0 <= i) && (flag_i < WIDTH);
					
					if ( (j >= HIGH) || ((0 <= j) && flag_i && (Array[j][i].fs == Filled)) ) {
						flag_break = 1;
						break;
					}

					cur = cur->next;
				}

				if ( flag_break == 1 ) {
					break;
				}
			} 
		}
		
		if ((0 <= yc) && (yc <= HIGH) ) {
			ret = yc - 1;
		}
	}

	return ret;
}

//移动图形到底部
static void move2down ( int *x,int *y,Color color,LinkList *list,enum DrawMethod d ) {
	draw_shape(*x,*y,BC,list,d);//清空上一次生成的图形	

	const int y_get = get2down(*x,*y,list);//返回y可以到达的最大位置
	
	if ((-1 <= y_get) && (y_get < HIGH) ) {
		*y = y_get;	
	}
	
	draw_shape(*x,*y,color,list,d);//重新生成的图形
}

//处理是否可以移动问题，返回非0表示可以，0为假
static int can_move_step ( int x,int y,LinkList *list,const enum MoveMethod m ) {
	const int flag = (list != NULL) && ((m == Left) || (m == Right) || (m == Drop) || (m == Circle));
	int ret = 0;

	if ( flag == 1 ) { 
		if ( m == Circle ) {
			circle_left(list);
		}

		LinkListNode *cur = (LinkListNode*)list;
		cur = cur->next;
		int i = 0;
		int j = 0;
	
		if ( cur != NULL ) { 
			int k = 0;
			int length = LinkList_Length(list);

			for ( k=0;(k<length) && (cur != NULL);k++ ) {
				j = ((Block*)cur->data)->y + y;
				i = ((Block*)cur->data)->x + x;
				
				const int flag_i = (0 <= i) && (i < WIDTH);
				const int flag_j = (0 <= j) && (j < HIGH);	

				if ( m == Left ) {
					if ( (i-1 < 0) ||(flag_j && (Array[j][i-1].fs == Filled)) ) {	
						break;//如果左移越界或不能左移，break
					}	
				} else if ( m == Right ) {
					if ( (i+1 >= WIDTH) || (flag_j && (Array[j][i+1].fs == Filled)) ) {
						break;//如果右移越界或不能右移，break
					}
				} else if ( m == Drop ) {
					if ( (j+1 >= HIGH ) || (flag_j && (Array[j+1][i].fs == Filled)) ) {
						break;//如果掉落越界或不能掉落，break
					}	
				} else if ( m == Circle ) {
					//如果旋转越界或不能旋转，break
					if ( (i< 0) || (i >= WIDTH) || (j >= HIGH) ) {
						break;
					} else if ( (j >= 0) && ( Array[j][i].fs == Filled) ) {	
						break;
					}
				}

				cur = cur->next;
			}

			if ( (k == length) || (cur == NULL) ) {
				ret = 1;
			}
			
			if ( m == Circle ) {
				circle_left(list);
				circle_left(list);
				circle_left(list);
			}
		}	
	}

	return ret;
}

//处理是否可以移动的问题
static int can_move ( int x,int y,LinkList *list,enum MoveMethod m  ) {
	int ret = 0;

	switch ( m ) {
	case Left:
		ret = can_move_step(x,y,list,Left);
		break;
	case Right:
		ret = can_move_step(x,y,list,Right);
		break;
	case Drop:
		ret = can_move_step(x,y,list,Drop);
		break;
	case Circle:
		ret = can_move_step(x,y,list,Circle);
		break;
	default:
		break;
	}	

	return ret;
}

//处理键盘信息,返回非0表示正常，返回0表示退出
static int do_keyboard ( int *x,int *y,Color color,LinkList *list ) {
	int ret = -1;
	const int flag = (x != NULL) && (y != NULL) && (0 <= color) && (color <= CS);

	if ( flag == 1 ) {
		const int key = get_key();
		
		if ( is_up(key) == 1 ) {
			if ( can_move(*x,*y,list,Circle) != 0 ) {
				circle_shape(*x,*y,color,list);	//旋转图形
			}
		} else if ( is_down(key) == 1 ) {//down，将方块移动到下方
			if ( can_move(*x,*y,list,Drop) != 0 ) {
				drop_shape(x,y,color,list);
			}
		} else if ( is_left(key) == 1 ) {//left,将方块移动到左边
			if ( can_move(*x,*y,list,Left) != 0 ) {
				move2left(x,y,color,list);
			}
		} else if ( is_right(key) == 1 ) {//right将方块移动到右边
			if ( can_move(*x,*y,list,Right) != 0 ) {
				move2right(x,y,color,list);
			}
		} else if ( is_esc(key) == 1 ) {//esc退出游戏
			ret = 0;
		} else if ( is_space(key) == 1 ) {//space将方块移动到最下方
			if ( can_move(*x,*y,list,Drop) != 0 ) {
				move2down(x,y,color,list,CurrentShape);
			}
		} else if ( is_enter(key) == 1 ) { //enter暂停游戏,再次enter继续
			recover_keyboard();//去除键盘控制
			
			scanf("%*[^\n]");//清空缓存
			getchar();//接收换行

			init_keyboard();//开启键盘控制	
		}	
	}	

	return ret;
}

//闪烁图形
static void blink_shape ( int x,int y,Color c ) {
	const int flag = (0 <= y) && (y < HIGH);
	
	printf("\033[%d;%dH",y+4,2*x+5);
	printf("\033[5m");	
	printf("\033[%dm\033[%dm[]",30+c,40+c);
	printf("\033[0m");	
	fflush(stdout);
}


//填充,0表示失败，非0表示成功
static int filled_Array ( int x,int y,LinkList *list,Color color ) {
	int ret = 1;
	const int flag = (list != NULL);

	if ( flag == 1 ) {
		LinkListNode *cur = (LinkListNode*)list;
		int length = LinkList_Length(list);
		cur = cur->next;
	
		if ( cur != NULL ) {
			int i = -1;
			int j = -1;
			int k = 0;
			int flag_area = -1;

			for ( k=0;(k<length) && (cur != NULL);k++ ) {
				i = ((Block*)(cur->data))->x + x;
				j = ((Block*)(cur->data))->y + y;
		
				flag_area = (0 <= i) && (i < WIDTH) && (0 <= j) && (j < HIGH);	

				if ( (flag_area == 1) && (Array[j][i].fs == Empty) ) {
					Array[j][i].fs = Filled;	
					Array[j][i].c = color;	
				} else {
					ret = 0;//填充失败

				/*	
					printf("k = %d,cur = %p\n",k,cur);
					printf("i = %d,j= %d\n",i,j);
					printf("x = %d,y = %d\n",x,y);
					printf("data x = %d,data y = %d\n",i-x,j-y);
					printf("Array .fs = %d\n",Array[j][i].fs);
				*/
					
					break;
				}
						
				cur = cur->next;
			}	
	
		}
	}	

	return ret;
}

//执行消行判断，并返回消掉的行数
static int disappeared_lines ( ) {
	int ret = 0;
	int flag = 1;

	for ( int j=HIGH-1;j>=0;j-- ) {
		flag = 1;

		for ( int i=0;i<WIDTH;i++ ) {
	
			if ( Array[j][i].fs == Empty ) {
				flag = 0;
				break;
			}	
		}

		if ( flag == 1 ) {
			ret ++;
			
			for ( int k=j;k>=0;k-- ) {	
				if ( k != 0 ) {	
					memcpy(*(Array + k),*(Array +k - 1),sizeof(RBlock) * WIDTH);
				} else {
					memset(Array,0x00,sizeof(RBlock) * WIDTH);
				}
			}

			j++;
			continue;
		}
	}

	return ret;
}

//执行消行操作
static void disappear_current_lines ( ) {
	for ( int j=0;j<HIGH;j++ ) {
		for ( int i=0;i<WIDTH;i++ ) {
			draw_element(i,j,Array[j][i].c,CurrentShape);
		}	
	}
}

//初始化Array
static void initialize_Array ( ) {
	memset(Array,0x00,sizeof(Array));//0初始化Array,将所有填充位置设为0,即Empty
	
	for ( int i=0;i<WIDTH;i++ ) {
		for ( int j=0;j<HIGH;j++ ) {
			Array[j][i].c = BC;	//用背景颜色初始化Array数组中的每个颜色标识
		}
	}	
}

//输入level
static int input_level ( ) {
	int ret = -1;

	int level = -1;
	int level_flag = 0;

	while ( level < 0 ) {
		printf("Input level!([lowest]1-9[fastest]):");
		level_flag = scanf(" %d",&level);
		scanf("%*[^\n]");//清空缓存
		scanf("%*c");//同上
		
		if ( level_flag == 0 ) {
			printf("Input level is illeagl!Please input again!\n");
			level = -1;
			continue;
		} else if ( level == 1 ) {
			if ( (0 < level) && (level < 10) ) {
				break;		
			} else {
				printf("Input level is not useful!Please input again!\n");
				level = -1;
				continue;
			}
		}	
	}

	ret = level;	

	return ret;
}		

//开始游戏
static void start_game ( ) {
	TimeB timeCur,timePre;
	int level = -1;
//	printf("block kinds = %d\n",sizeof(block_kinds)/sizeof(Block));
//	printf("sizeof Block is %d\n",sizeof(Block));
//	printf("sizeof block_kinds is %d\n",sizeof(block_kinds));
//	printf("a[%d][%d].x = %d,a[%d][%d].y = %d\n",X,Y,block_kinds[X][Y].x,X,Y,block_kinds[X][Y].y);
//	printf("BackGround = %d,NextShape = %d,CurrentShape = %d\n",BackGround,NextShape,CurrentShape);

	//输入level	
	level = input_level();

	//初始化数组Array
	initialize_Array();	

	memset(ShapeNumber,0x00,sizeof(ShapeNumber));
	memset(ShapeColor,0x00,sizeof(ShapeColor));

 	//以下初始化x,y,color,time,等信息	
	int x = MIDDLE;
	int y = 0;
	int time = 0;//timeCur 与timePre 的时间差(ms)
	long long  time_play = 0;
	int ms_level = 1000 / level;//掉落时间
	int flag_drop = -1;//是否可以掉落的标识

//	printf("long size = %d",sizeof(long));
//	getchar();

	DCircleList * dlist1 = creat_allkinds_shapes();//创建7种图形种类，每种用单链表控制4个方块，
	DCircleList * dlist2 = creat_allkinds_shapes();//用双链表控制7种图形，并且生成两个双链表dlist1、dlist2以防干扰
//	printf("dlist1 length = %d\n",dlist1->length);

	//当前图形的颜色
	Color color_cur = get_color();

	//下次图形的颜色
	Color color_next = get_color();

	creat_background ();//创建背景
	draw_seven_shapes(dlist1);	//在NextShape区域显示七种方块

	LinkList *shape_cur = born_one_shape(dlist1);//当前图形
	LinkList *shape_next = born_one_shape(dlist2);//下次图形


	//更改对应图形的数目并显示
	int index_shape_cur = (int)(shape_cur->header.data);
	
	if ( (0 <= index_shape_cur) && (index_shape_cur < 7) ) {
		ShapeNumber[index_shape_cur] ++;
		
		print_shape_number(index_shape_cur,ShapeNumber[index_shape_cur],ShapeColor[index_shape_cur]);	
		
	}

//	circle_shape(x,y,color_cur,shape_next);
/*
	printf("Empty = %d,Filled = %d\n",Empty,Filled);
	
	for ( int i=0;i<WIDTH;i++ ) {
		for ( int j=0;j<HIGH;j++ ) {
			printf("%d,%d|",Array[j][i].fs,Array[j][i].c);
		}
		
		printf("\n");
	}
	getchar();
*/

	draw_shape(X_NEXT,Y_NEXT,color_next,shape_next,NextShape);//显示下一个图形
	print((X_NEXT - 2),(Y_NEXT - 3),Next,-1,color_next);//显示下一个图形文字

	//Game Start的颜色
	Color color_Start = get_color();

	print((X_NEXT - 2),(Y_NEXT - 5),Start,-1,color_Start);//显示Start!

	//Time的颜色
	Color color_Time = get_color();

	print((X_NEXT - 2),(Y_NEXT + 12),Time,(time_play/1000),color_Time);//显示Time
	
	//Level的颜色
	Color color_Level = get_color();

	print((X_NEXT - 2),(Y_NEXT + 3),Level,level,color_Level);//显示Level
	
	//Score的颜色
	Color color_Score = get_color();

	print((X_NEXT - 2),(Y_NEXT + 5),Score,0,color_Score);//显示Score

	//Game Over!的颜色	
	Color color_End = get_color();

	//lines
	int lines = 0;
	Color color_Lines = get_color();
	print((X_NEXT - 2),(Y_NEXT + 8),Lines,lines,color_Lines);//显示lines
		
	//maxline
	int maxline = 0;
	Color color_MaxLine = get_color();
	print((X_NEXT - 2),(Y_NEXT + 10),MaxLine,maxline,color_MaxLine);//显示maxline

	ftime(&timePre);//把此时时间给timePre

	init_keyboard();//开启键盘控制
	for ( int control=0,score_total=0;1; ) {//进入游戏循环
		ftime(&timeCur);//把此时时间给timeCur
		time = (timeCur.time - timePre.time) * 1000 + (timeCur.millitm - timePre.millitm);//算出时间差
	
		if ( time > ms_level ) {//如果时间差大于预设值,进行掉落判断
			timePre = timeCur;

			time_play += time;
			print((X_NEXT -2),(Y_NEXT + 12),Time,(int)(time_play/1000),color_Time);//显示Time

			if ( (flag_drop = can_move(x,y,shape_cur,Drop)) != 0 ) {//如果可以掉落，掉落
				drop_shape(&x,&y,color_cur,shape_cur);
			} else if ( flag_drop == 0 ) {//如果不可以掉落，执行以下操作
//				draw_shape(x,y,EC,shape_cur,CurrentShape);
				
				if ( control == 0 ) {
					print((X_NEXT - 2),(Y_NEXT - 5),Normal,-1,-1);//清除Game Start
				}

				int flag_fill = filled_Array(x,y,shape_cur,color_cur);//填充，返回非0表示成功填充,0表示失败
				
//				printf("x = %d,y = %d\n");
		
				if ( flag_fill == 0 ) {
					print((X_NEXT - 2),(Y_NEXT - 5),End,-1,color_End);//显示Game Over!
					
/*
					for ( int j=0;j<HIGH;j++ ) {
						for ( int i=0;i<WIDTH;i++ ) {
						printf(" %d",Array[j][i].fs);
						}

						printf("\n");
					}		
*/
					break;//不能继续填充，退出游戏
				} else {
					int dlines = disappeared_lines();//执行消行判断，若有消行进行Array数据更新并返回消掉的行数
					
					if ( (0 < dlines) && (dlines < 5) ) {	
						lines += dlines;	
						print((X_NEXT - 2),(Y_NEXT + 8),Lines,lines,color_Lines);//显示lines

						if ( (maxline != 4) && (dlines > maxline) ) {
							maxline = dlines;
							
							print((X_NEXT - 2),(Y_NEXT + 10),MaxLine,maxline,color_MaxLine);//显示maxline
						}
						
						int score_cur = 0;

						for ( ;dlines>0;dlines-- ) {
							score_cur += 100 * dlines;
						}

						score_total += score_cur;//更新分数
						print((X_NEXT - 2),(Y_NEXT + 5),Score,score_total,color_Score);//显示Score
						
						if ( score_total >= 1000 * level ) {
							print((X_NEXT - 2),(Y_NEXT + 3),Level,++level,color_Level);//显示Level

							ms_level = 1000/level;
						}
	
						disappear_current_lines();//执行消行操作
					}
				}
	
				//以下重设x,y位置
				y = -1;
				x = MIDDLE;
			
				//获得下一个图形信息：形状以及颜色
				shape_cur = shape_next;
				color_cur = color_next;
	
				//更改对应图形的数目并显示
				index_shape_cur = (int)(shape_cur->header.data);
	
				if ( (0 <= index_shape_cur) && (index_shape_cur < 7) ) {
					ShapeNumber[index_shape_cur] ++;
		
					print_shape_number(index_shape_cur,ShapeNumber[index_shape_cur],ShapeColor[index_shape_cur]);	
				}


				draw_shape(X_NEXT,Y_NEXT,BC,shape_next,NextShape);//清除下一个图形显示位置的图形
				
				//选择dlist1还是dlist2生成下一个图形	
				if ( ++control % 2 == 1 ) {
					shape_next = born_one_shape(dlist1);
				} else {
					shape_next = born_one_shape(dlist2);
				}
				
				//生成下一个图形的颜色	
				color_next = get_color();

				print((X_NEXT-2),(Y_NEXT - 3),Next,-1,color_next);//显示下一个图形文字
				draw_shape(X_NEXT,Y_NEXT,color_next,shape_next,NextShape);//在下一个图形位置显示下一个图形
			}
		}

		if ( do_keyboard(&x,&y,color_cur,shape_cur) == 0 ) {//处理键盘获得的信息,0表示退出
			print((X_NEXT - 2),(Y_NEXT - 5),End,-1,color_End);//显示Game Over!
					
			break;//0退出游戏(ESC)
		}
	}	
	recover_keyboard();//消除键盘控制

	//销毁dlist1
	while ( DCircleList_Length(dlist1) > 0 ) {
		LinkList_Destroy((LinkList*)DCircleList_Delete(dlist1,0));
	}	
	DCircleList_Destroy(dlist1);

	//销毁dlist2
	while ( DCircleList_Length(dlist2) > 0 ) {
		LinkList_Destroy((LinkList*)DCircleList_Delete(dlist2,0));
	}	
	DCircleList_Destroy(dlist2);
} 

int main ( void ) {
	srand(time(NULL));
	
	start_game();			
		
	return 0;
}
