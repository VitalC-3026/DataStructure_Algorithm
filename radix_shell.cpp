//Shell Sorting
#include <iostream>
#include <ctime>
using namespace std;
void printArray(int*, int);

void swap(int* A, int i, int j) {
	if (A[i] > A[j]) {
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
}

void selection_sort(int* A, int num, int incr, int init) {
	for (int i = init; i < num; i += incr)  {
		for (int j = i + incr; j < num; j += incr)
			swap(A, i, j);
	}
	printArray(A, num);
}

void shellsort(int* A, int num) {
	for (int i = num / 3; i > 3; i = i / 3) {
		for (int j = 0; j < i; j++) {
			selection_sort(A, num, i, j);
		}
	}
	selection_sort(A, num, 1, 0);
}

void Radixsort(int* A, int num, int roi) {
	int* mark = new int[roi];
	int* B = new int[num];
	int max = 0;
	for (int i = 0; i < num; i++) {
		if (A[i] > max) {
			max = A[i];
		}
	}
	int k = 0;
	while (max != 0) {
		max = max / roi;
		k++;
	}
	for (int t = 0, r = 1; t < k; t++, r *= roi) {
		for (int i = 0; i < roi; i++) {
			mark[i] = 0;
		}
		for (int i = 0; i < num; i++) {
			mark[(A[i] / r) % roi]++;
		}
		for (int i = 1; i < roi; i++) {
			mark[i] = mark[i] + mark[i - 1];
		}
		for (int i = num - 1; i >= 0; i--) {
			B[--mark[(A[i] / r) % roi]] = A[i];
		}
		for (int i = 0; i < num; i++) {
			A[i] = B[i];
		}
	}
	
	
}

int Partition(int* A, int low, int high) {
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) { high--; }
		swap(A, low, high);
		while (low < high && A[low] < pivot) { low++; }
		swap(A, low, high);
	}
	return low;
}

void Quicksort(int* A, int low, int high) {
	if (low < high) {
		int pivotpos = Partition(A, low, high);
		Quicksort(A, low, pivotpos - 1);
		Quicksort(A, pivotpos + 1, high);
	}
}

int* generateNumber(int n) {
	int* arr = new int[n];
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 30000 + 1;
	}
	return arr;
}

void printArray(int* A, int n) {
	for (int i = 0; i < n; i++) {
		cout << A[i] << '\t';
	}
	cout << endl << "---------------------------" << endl;
}

int main()
{
	int n = 16;
	int* arr1, * arr2;
	arr1 = generateNumber(n);
	printArray(arr1, n);
	arr2 = generateNumber(n);
	printArray(arr2, n);
	//shellsort(arr1, n);
	//Radixsort(arr2, n, 10);
	Quicksort(arr2, 0, n - 1);
	printArray(arr2, n);
	return 0;
}
