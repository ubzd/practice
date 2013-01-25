#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct List {
    ElemType Data;
    struct List *next;
} LNode, *LinkList;

/* 求链表的长度 */
Status ListLength(LinkList L) {
    if (!L) return ERROR;
    int Length;
    for (Length = 0; L != NULL; ++Length, L = L->next);

    return Length;
}

/* 输出链表  */
Status Print(LinkList L) {
    if (!L) return ERROR;
    for (; L != NULL; L = L->next) 
        printf("%d ", L->Data);
    printf("\n");

    return OK;
}

/* 创建链表 */
Status InitList(LinkList &L, int n) {
    L = (LinkList) malloc (sizeof(LNode));
    LinkList head = (LinkList) malloc (sizeof(LNode));
    L->next = NULL;
    
    printf("请输入%d个数\n", n);
    for (int i = 0; i < n; ++i) {
        LinkList p = (LinkList) malloc (sizeof(LNode));
        scanf("%d", &p->Data);
        p->next = NULL;

        if (!i) L = head = p;
        else {
            L->next = p;
            L = p;
        }
    }
    L = head;

    return OK;
}

/* 插入节点 */
Status InsertNode(LinkList &L, int i, ElemType e) {
    LinkList p = (LinkList) malloc (sizeof(LNode));
    LinkList head = (LinkList) malloc (sizeof(LNode));
    head = L;
    p->Data = e;
    
    if (i <= 0 || i > ListLength(L) + 1) return ERROR;
    if (i == 1) {
        p->next = L;
        L = head = p;
    } else if (i == ListLength(L)) {
        for (; L->next != NULL; L = L->next);      
        L->next = p;
        p->next = NULL;
    } else {
        for (int j = 1; j <= i - 1; ++j, L = L->next);
        p->next = L->next;
        L->next = p;
    }
    L = head;
    
    return OK;
}

/* 链表删除 */
Status DeleteNode(LinkList &L, int i) {
    LinkList p = (LinkList) malloc (sizeof(LNode));
    LinkList q = (LinkList) malloc (sizeof(LNode));
    if(i <= 0 || i > ListLength(L)) return ERROR;
    int j = 0;

    if (i == 1) {
        q = L;    
        L = L->next;
    } else if (i == ListLength(L) + 1) {
        for (p = L; p->next->next != NULL; p = p->next)
            q = p->next->next;
        p->next = NULL;
    } else {
        p = L;
        while (p->next && j < i - 2) {
            p = p->next; ++j;
        }
        if (!p->next || j > i - 1) return ERROR;

        q = p->next;
        p->next = q->next;
    }
    free(q);

    return OK;
}

int main() {
    //freopen("./c/list.in", "r", stdin);
    LinkList L = (LinkList) malloc (sizeof(LNode));
    /* 创建链表 */
    int n;
    printf("请输入链表的长度(n >= 0):");
    while (scanf("%d", &n) && n < 0) printf("请输入大于等于0的长度!\n");;
    InitList(L, n);

    /* 插入节点 */
    int i, e;
    printf("请输入需要插入的位置与数据:");
    scanf("%d%d", &i, &e);
    if (!InsertNode(L, i, e)) printf("error\n");
    else Print(L);

    /* 删除节点 */
    printf("请输入需要删除的位置:");
    scanf("%d", &i);
    if (!DeleteNode(L, i)) printf("error\n");
    else Print(L);

    return 0;
}
