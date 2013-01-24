#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1 
#define ERROR 0

typedef struct Row_table { // 行表 
    char *addr;		       // 此行字符串的首地址 
    int length;	           // 字符串的长度 
    int init_size;
}Row, RowTable[1 << 8];    /

RowTable row;    
int next[1 << 8];                     // kmp 中的next数组 
char *_string = (char *) malloc (1);  // 存放文本串的字符串 
int MAX_ROW = 0;                      // 文本中当前最大行 

void LoadString() {
    FILE *fp = fopen("i.txt", "r");   
    char ch;

    for (int i = 0; (ch = getc(fp)) != EOF; ++i) {  
        _string = (char *) realloc (_string, strlen(_string) + 1); 
        _string[i] = ch;                                           
    }
    fclose(fp);
}
void InitTable() {
	row[MAX_ROW].addr = &_string[0];  // 字符串的首地址给第一行的地址记录 
    for (int i = 0, len = 1; i < strlen(_string); ++i, ++len) { 
        if (_string[i] == '\n') {     // 如果是回车，那么行号就加一 
            row[MAX_ROW + 1].addr = &_string[i + 1];  
            row[MAX_ROW].length = len;                // 此行的字符串长度 
            row[MAX_ROW].init_size = len;             // 初始分配的内存大小 
            MAX_ROW++; len = 0;                       // 每换一行，最大行数就加一。把len变成 0，用来记录下一行的长度 
        }
    }
}
void Traverse() {
	printf("行表情况\n------------------------\n");
	for (int i = 0; i < MAX_ROW; ++i)                 // 遍历每一行，i 最大也就是最大行号MAX_ROW 
		printf("%d %d %d\n", i, row[i].addr, row[i].length);  	
	
	puts(""); 
	printf("文本信息\n------------------------\n");
	for (int i = 0; i < MAX_ROW; ++i) {	              // 根据行表的信息，把每一个都输出来 
		printf("%d ", i + 1);                     
		for (int j = 0; j < row[i].length; ++j) {  
			putchar(row[i].addr[j]);              
		}
	}
	puts("");
}
void get_next(char t_str[]) {
	int i = 0, j = -1;
	next[0] = -1;
	
	while (i < strlen(t_str) - 1) {
		if (j == -1 || t_str[i] == t_str[j]){
			++i; ++j;
			if (t_str[i] == t_str[j]) next[i] = next[j];
			else next[i] = j;
		} else j = next[j];
	}
}
void KMP_Search(char t_str[], int &r, int &i) {   
	get_next(t_str);                             
	
	for(; r < MAX_ROW; ++r) {                   
 		int j = 0;                                
		while (i < row[r].length && j < (int)strlen(t_str)) {  
			if (j == -1 || row[r].addr[i] == t_str[j]) {
				++i; ++j;
			} else j = next[j];
		}

	 	if (j >= (int)strlen(t_str)) {         
			printf("找到了！在第%d行，第%d个字符\n", r + 1, (i - strlen(t_str)) + 1);
			break;
		} 
		if (r == MAX_ROW - 1) puts("没有找到！");
		i = 0;                                    
	} 
} 

void Search() {
	puts("请输入要查找的字符串");
	char t_str[1 << 8], ri;
	int row_num = 0, str_num = 0;    
	
	getchar();                      
	fgets(t_str, 1 << 8, stdin);    
	t_str[strlen(t_str) - 1] = '\0'; 

	do{                                       // 循环，直到找到希望的位置 或者 到最后
		KMP_Search(t_str, row_num, str_num);  // KMP算法开始，从第row_num行的第str_num字符位置开始向下查找
 		printf("是这个么？请输入(y 或 n)\n"); // 如果不是希望的位置，就输入n
		scanf("%c", &ri);
		getchar();
		if (ri == 'y') break;
	} while (row_num < MAX_ROW);             // row_num 还是小于最大行号，那么就接着循环
}

void InsertRow() {
	int r;
	char *in = (char *) malloc (1 << 8);    
	
	puts("请输入第几行");
	scanf("%d", &r);                       
	puts("请输入数据");
	getchar();
	fgets(in, 1 << 8, stdin);             
	in[strlen(in) - 1] = '\n';               
	
	for (int i = MAX_ROW; i >= r; --i){      // 在行表中，移动所有这一行之后的数据
		row[i + 1].addr = row[i].addr;       // 后一个 等于 前一个， 直到要输入的那一个行为止
		row[i + 1].length = row[i].length;
	}
	row[r].addr = in;                     
	row[r].length = strlen(in);             
	MAX_ROW++;                             
	
	Traverse();                          
}

void InsertStr() {
	puts("请输入第几行，第几个字符，数据将在插入在这之后");	
	int row_num, str_num, len; 
	char *in = (char *) malloc (1 << 8);
	
	scanf("%d%d", &row_num, &str_num);  
	puts("请输入字符串");
	getchar();
	fgets(in, 1 << 8, stdin);
	in[strlen(in) - 1] = '\0';

	if (row[row_num].init_size < row[row_num].length + strlen(in)) { 
		char *new_str = (char *) malloc (1 << 8);  
		int i = 0, j = 0;
		
		for (; i < str_num; ++i) {     
			new_str[i] = row[row_num].addr[i];
		}
		for (; j < strlen(in); ++j, ++i) {
			new_str[i] = in[j];
		}
		for (j = str_num; j < row[row_num].length; ++j, ++i){
			new_str[i] = row[row_num].addr[j];	
		}	

		new_str[i] = '\0';  
		row[row_num].addr = new_str;  
		row[row_num].length = strlen(new_str);
		row[row_num].init_size = strlen(new_str);
	} else { 
		int i, j = row[row_num].length;

		for (i = row[row_num].length + strlen(in); i >= (str_num + strlen(in) - 1); --i) {
			row[row_num].addr[i] = row[row_num].addr[j--];
		}
		
		for (i = 0; i < strlen(in); ++i) {
			row[row_num].addr[str_num++] = in[i];
		}
		
		row[row_num].length += strlen(in);
	}

	Traverse();
}

void Insert() {
	char c;
	
	puts("请输入命令：插入整行(r)；插入字符串(s)");
	getchar();
	scanf("%c", &c);
	
	switch(c) {
		case 'r' : InsertRow(); break;  // 插入整行 
		case 's' : InsertStr(); break;  // 插入字符串 
		default : break;
	}
}

void DeleteRow() {
	int row_num;
	puts("请输入要删除的行号");
	scanf("%d", &row_num);
	
	for (int i = row_num; i < MAX_ROW - 1; ++i){
		row[i].addr = row[i + 1].addr;
		row[i].length = row[i + 1].length;
		row[i].init_size = row[i + 1].init_size;
	}
	MAX_ROW--;
	
	Traverse();
}

void DeleteStr(){
	int row_num, str_num, del_len, i;
	puts("请输入要删除的行号、位置和长度");
	scanf("%d%d%d", &row_num, &str_num, &del_len);
	for (i = str_num + del_len; i < row[row_num].length; ++i)
		row[row_num].addr[str_num++] = row[row_num].addr[i];
		
	row[row_num].length -= del_len;
	row[row_num].addr[str_num] = '\0';
	
	Traverse();
}

void Delete() {
	char c;
	puts("请输入命令：删除整行(a)；删除字符串(s)");
	getchar();
	scanf("%c", &c); 
	
	switch(c) {
		case 'a' : DeleteRow(); break; 
		case 's' : DeleteStr(); break;
		default : break; 
	}
	getchar();
}

void Do() {
    LoadString(); 
    InitTable(); 
    Traverse(); 
    
	puts("请输入命令：查找(s)；插入(i)；删除(d)；退出(e)");
 	char c; 
 	int ex = 0;
    while (scanf("%c", &c)) { 
    	switch(c){
    		case 's' : Search(); break;      //查找函数                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   break;
    		case 'i' : Insert(); break;      //插入函数 
    		case 'd' : Delete(); break;      //删除函数 
    		case 'e' : ex = 1; break;        //如果退出，把ex标记变为 1 
	    }
   		if (ex) break;        
   		printf("请输入命令：查找(s)；插入(i)；删除(d);退出(e)。\n");
    }
}

int main() {
    Do();    // start
}
