#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1 
#define ERROR 0

typedef struct Row_table { // �б� 
    char *addr;		       // �����ַ������׵�ַ 
    int length;	           // �ַ����ĳ��� 
    int init_size;
}Row, RowTable[1 << 8];    /

RowTable row;    
int next[1 << 8];                     // kmp �е�next���� 
char *_string = (char *) malloc (1);  // ����ı������ַ��� 
int MAX_ROW = 0;                      // �ı��е�ǰ����� 

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
	row[MAX_ROW].addr = &_string[0];  // �ַ������׵�ַ����һ�еĵ�ַ��¼ 
    for (int i = 0, len = 1; i < strlen(_string); ++i, ++len) { 
        if (_string[i] == '\n') {     // ����ǻس�����ô�кžͼ�һ 
            row[MAX_ROW + 1].addr = &_string[i + 1];  
            row[MAX_ROW].length = len;                // ���е��ַ������� 
            row[MAX_ROW].init_size = len;             // ��ʼ������ڴ��С 
            MAX_ROW++; len = 0;                       // ÿ��һ�У���������ͼ�һ����len��� 0��������¼��һ�еĳ��� 
        }
    }
}
void Traverse() {
	printf("�б����\n------------------------\n");
	for (int i = 0; i < MAX_ROW; ++i)                 // ����ÿһ�У�i ���Ҳ��������к�MAX_ROW 
		printf("%d %d %d\n", i, row[i].addr, row[i].length);  	
	
	puts(""); 
	printf("�ı���Ϣ\n------------------------\n");
	for (int i = 0; i < MAX_ROW; ++i) {	              // �����б����Ϣ����ÿһ��������� 
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
			printf("�ҵ��ˣ��ڵ�%d�У���%d���ַ�\n", r + 1, (i - strlen(t_str)) + 1);
			break;
		} 
		if (r == MAX_ROW - 1) puts("û���ҵ���");
		i = 0;                                    
	} 
} 

void Search() {
	puts("������Ҫ���ҵ��ַ���");
	char t_str[1 << 8], ri;
	int row_num = 0, str_num = 0;    
	
	getchar();                      
	fgets(t_str, 1 << 8, stdin);    
	t_str[strlen(t_str) - 1] = '\0'; 

	do{                                       // ѭ����ֱ���ҵ�ϣ����λ�� ���� �����
		KMP_Search(t_str, row_num, str_num);  // KMP�㷨��ʼ���ӵ�row_num�еĵ�str_num�ַ�λ�ÿ�ʼ���²���
 		printf("�����ô��������(y �� n)\n"); // �������ϣ����λ�ã�������n
		scanf("%c", &ri);
		getchar();
		if (ri == 'y') break;
	} while (row_num < MAX_ROW);             // row_num ����С������кţ���ô�ͽ���ѭ��
}

void InsertRow() {
	int r;
	char *in = (char *) malloc (1 << 8);    
	
	puts("������ڼ���");
	scanf("%d", &r);                       
	puts("����������");
	getchar();
	fgets(in, 1 << 8, stdin);             
	in[strlen(in) - 1] = '\n';               
	
	for (int i = MAX_ROW; i >= r; --i){      // ���б��У��ƶ�������һ��֮�������
		row[i + 1].addr = row[i].addr;       // ��һ�� ���� ǰһ���� ֱ��Ҫ�������һ����Ϊֹ
		row[i + 1].length = row[i].length;
	}
	row[r].addr = in;                     
	row[r].length = strlen(in);             
	MAX_ROW++;                             
	
	Traverse();                          
}

void InsertStr() {
	puts("������ڼ��У��ڼ����ַ������ݽ��ڲ�������֮��");	
	int row_num, str_num, len; 
	char *in = (char *) malloc (1 << 8);
	
	scanf("%d%d", &row_num, &str_num);  
	puts("�������ַ���");
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
	
	puts("�����������������(r)�������ַ���(s)");
	getchar();
	scanf("%c", &c);
	
	switch(c) {
		case 'r' : InsertRow(); break;  // �������� 
		case 's' : InsertStr(); break;  // �����ַ��� 
		default : break;
	}
}

void DeleteRow() {
	int row_num;
	puts("������Ҫɾ�����к�");
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
	puts("������Ҫɾ�����кš�λ�úͳ���");
	scanf("%d%d%d", &row_num, &str_num, &del_len);
	for (i = str_num + del_len; i < row[row_num].length; ++i)
		row[row_num].addr[str_num++] = row[row_num].addr[i];
		
	row[row_num].length -= del_len;
	row[row_num].addr[str_num] = '\0';
	
	Traverse();
}

void Delete() {
	char c;
	puts("���������ɾ������(a)��ɾ���ַ���(s)");
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
    
	puts("�������������(s)������(i)��ɾ��(d)���˳�(e)");
 	char c; 
 	int ex = 0;
    while (scanf("%c", &c)) { 
    	switch(c){
    		case 's' : Search(); break;      //���Һ���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   break;
    		case 'i' : Insert(); break;      //���뺯�� 
    		case 'd' : Delete(); break;      //ɾ������ 
    		case 'e' : ex = 1; break;        //����˳�����ex��Ǳ�Ϊ 1 
	    }
   		if (ex) break;        
   		printf("�������������(s)������(i)��ɾ��(d);�˳�(e)��\n");
    }
}

int main() {
    Do();    // start
}
