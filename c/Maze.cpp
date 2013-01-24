#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXN 10
#define STACK_INIT_SIZE 100

typedef int Status;

typedef struct {
    int x, y;
} PosType;

typedef struct {
    int ord;
    PosType seat;
    int di;
} SElemType;

typedef struct {
    SElemType *top;
    SElemType *base;
    int stacksize;
} SqStack;

/************* STACK **************/
Status CreateStack(SqStack &s) {
   s.base = (SElemType *) malloc (STACK_INIT_SIZE * (sizeof(SElemType)));
   s.top = s.base;
   s.stacksize = STACK_INIT_SIZE;

   return OK;
}

Status isEmpty(SqStack s) {
    if (s.top == s.base)
        return 1;
    return 0;
}

Status Push(SqStack &s, SElemType e) {
    if (s.top - s.base >= s.stacksize) {
        s.base = (SElemType *) realloc (s.base, (STACK_INIT_SIZE + s.stacksize) * sizeof(SElemType));
        if (!s.base) return ERROR;
        s.top = s.base + s.stacksize;
        s.stacksize += STACK_INIT_SIZE;
    }
    *s.top++ = e;

    return OK;
}

SElemType Pop(SqStack &s) {
    if (!isEmpty(s)) {
        return *--s.top;
    } else printf("Empty error!\n");  
}

SElemType GetTop(SqStack s) {
    if (!isEmpty(s)) {
        return *--s.top;
    } else printf("Empty error!\n");
    
}
/************* STACK **************/

/************* BEGIN MAZE AGORITHM **************/
int Maze[MAXN][MAXN] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/* 判断是否已经走过或者已经是死胡同 */
bool isMarked(PosType pos) {
    if (Maze[pos.x][pos.y] > 1)    
        return 1;
    return 0;
}

/* 判断是否走通 */
bool CanPass(PosType pos) {
    if (Maze[pos.x][pos.y] == 0 || isMarked(pos))
        return 0;
    return 1;
}

/* 按顺时针改变方向 */
PosType getNext(PosType pos, int di) {
    switch (di) {
        case 1: pos.y++; break;
        case 2: pos.x++; break;
        case 3: pos.y--; break;
        case 4: pos.x--; break;   
		default: break;    
    }
    
    return pos;
}

/* 如果迷宫当前位置的值为2为就说明是已经走过的 */
Status FootPrint(PosType &pos) {   
    Maze[pos.x][pos.y] = 2;
    return OK;
}

/*同上，3为死胡同*/
Status MarkPrint(PosType &pos) { 
    Maze[pos.x][pos.y] = 3;
    return OK;
}

bool MazePath(SqStack s) {
    SElemType e;
    PosType start, end, curpos;
    start.x = 1; 
    start.y = 1;
    end.x = 8;
    end.y = 8;
    curpos = start;
    int curstep = 1;

    do {
        if (CanPass(curpos)) { // 先判断这个格子能不能走通 
            FootPrint(curpos); // 矩阵的值是 2 是走过的，是可以走通的，但是不能往回走的 
            e.ord = curstep;
            e.seat = curpos;
            e.di = 1;
            Push(s, e);  // 把这个格子放到站里面 
            if ((curpos.x == end.x)  && (curpos.y == end.y)) return true; // 判断是不是终点 
            curpos = getNext(curpos, 1); // 换方向 
            curstep++; //步子加一 
        } else {
            if (!isEmpty(s)) {
                e = Pop(s);  
                while (e.di == 4 && !isEmpty(s)) { //如果四个方向都走过了，那么就弹出 
                    MarkPrint(e.seat); // 矩阵的值变成3 是死胡同 
                    e = Pop(s);
                }
				
                if (e.di < 4) {  //如果四个方向都没有走过，那么就换一个方向走走 
                    e.di++; Push(s, e);
                    curpos = getNext(e.seat, e.di);   // 换个方向 
                }
            }       
        }

    } while (!isEmpty(s));

    return false;
}

void TraverseMaze() {
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            printf("%d ", Maze[i][j]);
        }
        puts("");
    }
}
/************* END MAZE AGORITHM **************/

int main() {
    SqStack S;
    CreateStack(S);
    
    if (MazePath(S)) puts("Can pass!");
    else puts("OH~~ CAN NOT PASS");
    TraverseMaze();

    return 0;
}

