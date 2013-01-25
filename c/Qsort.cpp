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

