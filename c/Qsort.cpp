#include <stdio.h> 

int Partition(int Array[], int Low, int High) {
	int Key;
	Key = Array[Low];
	while (Low < High) {
		for (; Low < High && Array[High] >= Key; --High);
		Array[Low] = Array[High];
		for (; Low < High && Array[Low] <= Key; ++Low);
		Array[High] = Array[Low];
	}
	Array[Low] = Key;
   	return Low;
}

void Qsort(int Array[], int Low, int High) {
	int Mid = 0;
	if (Low < High) {
		Mid = Partition(Array, Low, High);
		Qsort(Array, Low, Mid - 1);
		Qsort(Array, Mid + 1, High);
	}
}


int main() {
	int Low, High;
	int Array[] = {6, 7, 3, 8, 10, 9, 1, 4, 5, 2};
	Low = 0;
	High= 9;
	Qsort(Array, Low, High);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", Array[i]);
	}
	return 0;
}



procedure Sort(l,r:longint);
var
  i,j,x,tmp: longint;
begin
  i:=l; j:=r;
  x:=a[l+random(r-l+1)];
  repeat
    while a[i] < x do inc(i);
    while x < a[j] do dec(j);
    if i <= j then
    begin
      tmp:=a[i]; a[i]:=a[j]; a[j]:=tmp;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then Sort(l,j);
  if i < r then Sort(i,r);
end;
