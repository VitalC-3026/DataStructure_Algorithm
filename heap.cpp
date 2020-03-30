#include <iostream>
#include <ctime>
using namespace std;

//class Node {
//private:
//	int number;
//	Node* leftchild;
//	Node* rightchild;
//public:
//	Node(int num) {
//		number = num;
//		leftchild = nullptr;
//		rightchild = nullptr;
//	}
//	friend class Heap;
//	
//};
//
////´ó¸ù¶Ñ
//class Heap {
//private:
//	Node* root;
//	int barrier;
//	int len;
//	int* sort_arr;
//	Node** tree;
//	void createAheap();
//	
//public:
//	Heap(int num) {
//		barrier = num - 1;
//		len = num;
//		sort_arr = new int[num];
//		sort_arr[0] = -65535;
//		root = nullptr;
//		tree = new Node * [num];
//	}
//	void createAarray(int*, int);
//	void createAbigheap(int*, int);
//	void swap_root(); 
//	void adjust_heap(Node*, int);
//	int compare(Node* root);
//	void heapify(int);
//	void sort();
//	void printArray() {
//		for (int i = 0; i < len; i++) {
//			cout << sort_arr[i] << '\t';
//		}
//		cout << endl;
//	}
//};
//
//void Heap::createAarray(int* arr, int n) {
//	if (n != barrier) {
//		return;
//	}
//	for (int i = 0; i < n; i++) {
//		sort_arr[i] = arr[i];
//	}
//	
//}
//
////void Heap::createAheap(){
////	if (sort_arr[0] == -65535) {
////		return;
////	}
////	
////	if (root == nullptr) {
////		root = new Node(sort_arr[0]);
////		tree[0] = root;
////		int t = 1;
////		while (t < len) {
////			if (t % 2 != 0) {
////				tree[(t - 1) / 2]->leftchild = new Node(sort_arr[t]);
////			}
////			else {
////				tree[(t - 2) / 2]->rightchild = new Node(sort_arr[t]);
////			}
////			t++;
////		}
////	}
////}
//
//void Heap::createAbigheap(int* sort, int len) {
//	if (barrier != len - 1 || len != this->len) {
//		cout << "error" << endl;
//		return;
//	}
//	for (int i = len - 1; i >= 0; i--) {
//		sort_arr[i] = sort[i];
//		heapify(i);
//	}
//}
//
//void Heap::swap_root() {
//	int temp = sort_arr[0];
//	sort_arr[0] = sort_arr[barrier];
//	sort_arr[barrier--] = temp;
//}
//
//void Heap::adjust_heap(Node* root, int index) {
//	if (2 * index + 1 == barrier) {
//		return;
//	}
//	int temp = 0;
//	switch (compare(root)) {
//		case 0:
//			return;
//		case 1:
//			if (2 * index + 2 == barrier) {
//				return;
//			}
//			temp = root->number;
//			root->number = root->rightchild->number;
//			root->rightchild->number = temp;
//			temp = sort_arr[index];
//			sort_arr[index] = sort_arr[2 * index + 2];
//			sort_arr[2 * index + 2] = temp;
//			adjust_heap(root->rightchild, 2 * index + 2);
//			break;
//		case -1:
//			temp = root->number;
//			root->number = root->leftchild->number;
//			root->leftchild->number = temp;
//			temp = sort_arr[index];
//			sort_arr[index] = sort_arr[2 * index + 2];
//			sort_arr[2 * index + 1] = temp;
//			adjust_heap(root->rightchild, 2 * index + 2);
//			adjust_heap(root->leftchild, 2 * index + 1);
//			break;
//	}
//
//}
//
//int Heap::compare(Node* root){
//	if (root->number >= root->leftchild->number) {
//		if (root->number >= root->rightchild->number) {
//			return 0;
//		}
//		else {
//			return 1;
//		}
//	}
//	else {
//		if (root->leftchild->number >= root->rightchild->number) {
//			return -1;
//		}
//		else {
//			return 1;
//		}
//	}
//}
//
//void Heap::heapify(int currNode) {
//	int max = currNode;
//	int left = 2 * currNode + 1;
//	int right = 2 * currNode + 2;
//	if (currNode >= barrier) {
//		return;
//	}
//	if (left > barrier && right > barrier) {
//		return;
//	}
//	if (left <= barrier && sort_arr[max] < sort_arr[left]) {
//		max = left;
//	}
//	if (right <= barrier && sort_arr[max] < sort_arr[right]) {
//		max = right;
//	}
//	if (max != currNode) {
//		int temp = sort_arr[max];
//		sort_arr[max] = sort_arr[currNode];
//		sort_arr[currNode] = temp;
//		heapify(max);
//	}
//	
//}
//
//void Heap::sort() {
//	//createAbigheap(this->sort_arr, this->len);
//	while (barrier > 0) {
//		swap_root();
//		heapify(0);
//	}
//}
//
//int* generateNumber(int n) {
//	int* arr = new int[n];
//	srand((unsigned)time(NULL));
//	for (int i = 0; i < n; i++) {
//		arr[i] = rand() % 30000 + 1;
//	}
//	return arr;
//}

//int main() {
//	/*int n = 10;
//	int* arr;
//	arr = generateNumber(n);
//	for (int i = 0; i < n; i++) {
//		cout << arr[i] << '\t';
//	}
//	cout << endl;
//	Heap h(n);
//	h.createAbigheap(arr, n);
//	cout << "After heapify:" << endl;
//	h.printArray();
//	cout << "After sorting:" << endl;
//	h.sort();   
//	h.printArray();*/
//
//	return 0;
//}
