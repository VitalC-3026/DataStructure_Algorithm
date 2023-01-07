#include <iostream>
#include <stack>

using namespace std;

int main()
{
	int** man, ** woman, ** man_rank, * man_match, * woman_match;
	int n = 0;
	cout << "请输入人数n: ";
	cin >> n;
	man = new int* [n];
	woman = new int* [n];
	man_rank = new int* [n];
	man_match = new int[n];
	woman_match = new int[n];
	for (int i = 0; i < n; i++) {
		man[i] = new int[n + 1];
		man[i][n] = 0;
		woman[i] = new int[n + 1];
		woman[i][n] = 0;
		man_rank[i] = new int[n];
		man_match[i] = 0;
		woman_match[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> man[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> woman[i][j];
			man_rank[i][woman[i][j] - 1] = j;
		}
	}
	stack<int> man_to_match;
	for (int i = n - 1; i >= 0; i--) {
		man_to_match.push(i);
	}
	
	while (!man_to_match.empty()) {
		int man2match = man_to_match.top();
		int index_woman = man[man2match][n];
		int woman_to_match = man[man2match][index_woman] - 1;
		
		if (woman[woman_to_match][n] == 0) {
			man_match[man2match] = woman_to_match + 1;
			woman_match[woman_to_match] = man2match + 1;
			woman[woman_to_match][n] = -1;
			man_to_match.pop();
		}
		else { 
			int flag = man_rank[woman_to_match][man2match] < man_rank[woman_to_match][woman_match[woman_to_match] - 1];
			if (flag) {
				int deserted_man = woman_match[woman_to_match] - 1;
				man_match[man2match] = woman_to_match + 1;
				man_match[deserted_man] = 0;
				man[deserted_man][n]++;
				woman_match[woman_to_match] = man2match + 1;
				woman[woman_to_match][n] = -1;
				man_to_match.pop();
				man_to_match.push(deserted_man);
			}
			else {
				man[man2match][n]++;
			}
		}
		
	}
	for (int i = 0; i < n; i++) {
		cout << man_match[i] << " ";
	}
	cout << endl;
	return 0;
}


