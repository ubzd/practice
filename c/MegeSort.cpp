#include <stdio.h>
#include <string.h>
#include <malloc.h>

void Merge(int Arr[], int Low, int Mid, int High) {
	int Begin1, End1, Begin2, End2, k;
	int *Temp = (int *)malloc((High - Low + 1) * sizeof(int));
	
	Begin1 = Low;
	End1   = Mid;
	Begin2 = Mid + 1;
	End2   = High;
	for (k = 0; Begin1 <= End1 && Begin2 <= End2; ++k) {
		if (Arr[Begin1] <= Arr[Begin2]) {
			Temp[k] = Arr[Begin1++];
		} else {
			Temp[k] = Arr[Begin2++];
		}
	}	
	if (Begin1 <= End1) 
		memcpy(Temp + k, Arr + Begin1, (End1 - Begin1 + 1) * sizeof(int));
	if (Begin2 <= End2)
		memcpy(Temp + k, Arr + Begin2, (End2 - Begin2 + 1) * sizeof(int));
	memcpy(Arr + Low, Temp, (High - Low + 1) * sizeof(int));
	free(Temp);
}

void Merge_Sort(int Arr[], int Low, int High) {
	int Mid = 0;
	if (Low < High)	{
		Mid = (Low & High) + ((Low ^ High) >> 1);
		Merge_Sort(Arr, Low, Mid);
		Merge_Sort(Arr, Mid + 1, High);
		Merge(Arr, Low, Mid, High);
	}
}

int main() {
    int Arr[] = {2, 4, 1, 3, 6, 7 , 9, 5, 8, 10};
	int Low, High;
	Low = 0;
	High = 9;
	printf("The Merge Sorting!\n");
    Merge_Sort(Arr, Low, High);
	for (int i = Low; i <= High; ++i) {
		printf("%d ", Arr[i]);
	}
	return 0;
}
