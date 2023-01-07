/* 序列匹配 */
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;

// 比较三种情况的大小
int compare(int a, int b, int c) {
    int m = min(a, b);
    return min(m, c);
}

int series_match(char s1[], char s2[], int value) {
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);

	// 特殊情况
	if (s1_len == 0 && s2_len == 0) {
		return 0;
	}
	else if (s1_len == 0) {
		return value * s2_len;
	}
	else if (s2_len == 0) {
		return value * s1_len;
	}

	// 初始化数组B用来存放序列比对的罚分值
	int** B = new int* [s1_len + 1];
	for (int i = 0; i <= s1_len; i++) {
		B[i] = new int[2];
		B[i][0] = i * value;
	}

    // 填充数组B
	for (int i = 1; i <= s2_len; i++) {
		B[0][1] = i * value;
		for (int j = 1; j <= s1_len; j++) {
			int dif = abs(s1[j - 1] - s2[i - 1]);
			B[j][1] = compare(B[j - 1][1] + value, B[j][0] + value, B[j - 1][0] + dif);
		}
		for (int j = 0; j <= s1_len; j++) {
			B[j][0] = B[j][1];
		}
	}
	return B[s1_len][1];
}

int main() {

	char s1[2500], s2[2500];
	cin >> s1;
	cin >> s2;
	int value;
	cin >> value;
	int res = series_match(s1, s2, value);
	std::cout << res;
	return 0;
}
