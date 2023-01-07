#include <iostream>
using namespace std;
int* find_Knapsack(int n, int w, int value[][2], int** opt);

int* Knapsack(int n, int w, int value[][2], int& maxValue) {
	int** opt = new int* [n + 1];
	for (int i = 0; i < n + 1; i++) {
		opt[i] = new int[w + 1];
		opt[i][0] = 0;
	}
	for (int i = 0; i < w + 1; i++) {
		opt[0][i] = 0;
	}
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < w + 1; j++) {
			if (value[i - 1][1] > j) {
				opt[i][j] = opt[i - 1][j];
			}
			else {
				if (opt[i - 1][j] > opt[i - 1][j - value[i - 1][1]] + value[i - 1][0]) {
					opt[i][j] = opt[i - 1][j];
				}
				else {
					opt[i][j] = opt[i - 1][j - value[i - 1][1]] + value[i - 1][0];
				}

			}
		}
		
	}
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < w + 1; j++) {
			cout << opt[i][j] << " ";
		}
		cout << endl;
	}
	int* res = find_Knapsack(n, w, value, opt);
	maxValue = opt[n][w];
	for (int i = 0; i < n + 1; i++) {
		delete[] opt[i];
	}
	delete[] opt;
	return res;
}

int* find_Knapsack(int n, int w, int value[][2], int** opt) {
	int* res = new int[n];
	for (int i = 0; i < n; i++) {
		res[i] = 0;
	}
	int t = 0;
	for (int i = n; i > 0; i--) {
		if (opt[i][w] > opt[i - 1][w]) {
			res[t++] = i;
			w = w - value[i - 1][1];
			if (w == 0) {
				break;
			}
		}
	}
	return res;
}

int main()
{
  // 背包的价值和重量
	int value[][2] = {1, 1,  6, 2, 22, 5, 18, 6, 28, 7};
  // 背包的总个数n，允许的最大载重量w
	int n = 5, w = 11, maxValue = 0;
	int* res = Knapsack(5, 11, value, maxValue);
	cout << "背包的最大价值为：" << maxValue << endl;
	cout << "选择的背包为：";
	for (int i = 0; i < n && res[i] != 0; i++) {
		cout << res[i] << " ";
	}
	return 0;
}
