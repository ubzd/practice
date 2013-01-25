#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int next[1 << 16];
void getNext(string b) {
	int i = 0, j = -1; 
	next[0] = -1;
	while (i <= b.size()) {
		if (j == -1 || b[i] == b[j]) {
			++i; ++j;
			if (b[i] != b[j]) next[i] = j;
			else next[i] = next[j];
		} else j = next[j];
	}
}
int KMP(string a, string b) {
	int i = 0, j = 0;
	getNext(b);
	while (i < a.size() && j < b.size()) {
		if (j == -1 || a[i] == b[j]) {
			++i; ++j;
		} else {
			j = next[j];
		}
	}

	if (j >= b.size()) 
		return i - b.size();
	else return 0;
}

int main() {
	string a, b;
	cin >> a >> b;
	int index = KMP(a, b);
	cout << index << " " << a[index];
}

