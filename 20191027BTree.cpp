#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;


struct Dataset {
	long long mainkey;
	int file_No;
	char division;
	string CWord;
	int i_num;
	double d_num;
	string EWord;
	Dataset() {
		mainkey = 0;
		file_No = 0;
		division = 0;
		i_num = 0;
		d_num = 0;
	}
	Dataset(long long m,int file_No, char div, string CNWord, int i,double d, string EWord) {
		mainkey = m;
		this->file_No = file_No;
		division = div;
		CWord = CNWord;
		i_num = i;
		d_num = d;
		this->EWord = EWord;
	}
	void printInfo() {
		cout << "mainkey: " << mainkey << " " << "fileNo: " << file_No << " " << "division: " << division << " ";
		cout << "int_number: " << i_num << " " << "double_number: " << d_num << " " << "CWord: " << CWord << " ";
		cout << "EWord: " << EWord << endl;
	}
};

void sort(Dataset*&, int);
bool operator<(const Dataset& d1, const Dataset& d2);
bool operator>(const Dataset& d1, const Dataset& d2);
bool operator==(const Dataset& d1, const Dataset& d2);

const int Order = 4;
const int MAXSIZE = 3;
const int MINSIZE = 2;
class TreeNode {
private:
	Dataset* content;
	int count;
	TreeNode** pointer;
public:
	TreeNode() {
		content = new Dataset[MAXSIZE];
		count = 0;
		pointer = new TreeNode * [MAXSIZE + 1];
		for (int i = 0; i < MAXSIZE + 1; i++) {
			pointer[i] = nullptr;
		}

	}
	TreeNode(const Dataset d) {
		content = new Dataset[MAXSIZE];
		content[0] = d;
		count = 1;
		pointer = new TreeNode * [MAXSIZE + 1];
		for (int i = 0; i < MAXSIZE + 1; i++) {
			pointer[i] = nullptr;
		}
	}
	
	~TreeNode() {
		delete[] content;
		delete[] pointer;
	}
	friend class Node;
	friend class BTree;
};

class BTree {
private:
	TreeNode* root;
public:
	BTree() {
		root = nullptr;
	}
	bool insert(TreeNode*, const Dataset& item);
	bool Insert(const Dataset& d); 
	bool findParent(const TreeNode* target, TreeNode*& parent) {
		bool res = FindParent(this->root, target, parent);
		return res;
	}
	bool FindParent(TreeNode* root, const TreeNode*& target, TreeNode*& parent);
	void split_node(TreeNode*&, const Dataset&, TreeNode*& d, int pos, Dataset& median, TreeNode*& right);
	void push_in(const Dataset& target, TreeNode*&, int location, TreeNode*& right);
	bool find(TreeNode*, const Dataset& d, int&, int&);
	bool Find(const Dataset& d, int& pos, int& count) {
		count = 0;
		bool res = find(this->root, d, pos, count);
		return res;
	}
	Dataset& getMedian(const TreeNode*,const Dataset&);
	void elevation(TreeNode*, const Dataset&, TreeNode*&, int, Dataset&, TreeNode*&);
	void traverse(TreeNode* root); 
	void Traverse() {
		traverse(root);
	}
};

bool BTree::find(TreeNode* root, const Dataset& d, int& position, int& count) {
	bool res = false;
	position = 0;
	if (root->pointer[0] == nullptr) {
		count++;
		//cout << count << endl;
		if (d < root->content[0]) {
			//cout << "Failed!" << endl;
			return false;
		}
		else if (d > root->content[root->count - 1]) {
			//cout << "Failed!" << endl;
			return false;
		}
		else{
			while (position < root->count) {
				
				if (d == root->content[position]) {
					//cout << "Successful!" << endl;
					return true;
				}
				position++;
			}
			//cout << "Failed!" << endl;
			return false;
		}	
	}
	else {
		int t = 0;
		while (t < root->count) {
			if (d < root->content[t]) {
				count++;
				res = find(root->pointer[t], d, position,count);
				return res;
			}
			else if (d == root->content[t]) {
				//cout << "Successful!" << endl;
				return true;
			}
			t++;
		}
		count++;
		res = find(root->pointer[root->count], d, position,count);
		return res;
	}
	
}

bool BTree::Insert(const Dataset& item) 
{
	bool res = insert(this->root, item);
	return res;
}
	
bool BTree::insert(TreeNode* root, const Dataset& item) {
	TreeNode* rightbranch = nullptr, * newbranch = nullptr;
	Dataset median;
	if (this->root == nullptr) {
		this->root = new TreeNode(item);
		return true;
	}
	int size = root->count;
	if (root->pointer[0] == nullptr) {
		int t = 0;
		while (t < size) {
			if (item < root->content[t]) {
				break;
			}
			if (item == root->content[t]) {
				//cout << "duplicate!" << endl;
				return false;
			}
			t++;
		}
		if (root->count == MAXSIZE) {
			elevation(root,item,newbranch,t,median,rightbranch);
		}
		else{
			push_in(item, root, t, rightbranch);
		}
		
	}
	else {
		int t = 0;
		while (t < size) {
			if (item < root->content[t]) {
				break;
			}
			if (item == root->content[t]) {
				//cout << "duplicate!" << endl;
				return false;
			}
			t++;
		}
		insert(root->pointer[t], item);
	}
	//root->count++;
}

//when node is full, use this function to insert
void BTree::elevation(TreeNode* curr, const Dataset& new_entry, TreeNode*& new_branch, int location, Dataset& median, TreeNode*& right)  {
	TreeNode* parent;
	findParent(curr, parent);
	split_node(curr, new_entry, new_branch, location, median, right);
	if (parent == nullptr) {
		TreeNode* new_root = new TreeNode();
		new_root->content[0] = median;
		new_root->pointer[0] = curr;
		new_root->pointer[1] = right;
		new_root->count++;
		this->root = new_root;
		return;
	}
	if (parent->count < MAXSIZE && parent->count > 0) {
		int t = 0;
		while (t < parent->count) {
			if (median < parent->content[t]) {
				break;
			}
			t++;
		}
		push_in(median, parent, t, right);
	}
	else if (parent->count == MAXSIZE) {
		TreeNode* median_branch = new TreeNode();//entry_branch
		for (int i = 0; i < right->count;i++) {
			median_branch->content[i] = right->content[i];
			median_branch->pointer[i] = right->pointer[i];
		}
		median_branch->pointer[right->count] = right->pointer[right->count];
		int t = 0;
		while (t < parent->count) {
			if (median < parent->content[t]) {
				break;
			}
			t++;
		}
		Dataset entry = median;
		elevation(parent, entry, median_branch, t, median, right);
	}
}

void BTree::split_node(TreeNode*& curr,const Dataset& extra_entry, TreeNode*& extra_branch, int pos, Dataset& median, TreeNode*& right) 
{
	right = new TreeNode();
	int mid = Order / 2;
	if (pos <= mid) {
		for (int i = mid; i < Order - 1; i++) {
			right->content[i - mid] = curr->content[i];
			right->pointer[i + 1 - mid] = curr->pointer[i + 1];
		}
		curr->count = mid;
		right->count = Order - mid - 1;
		push_in(extra_entry, curr, pos, extra_branch);
	}
	else {
		mid++;
		for (int i = mid; i < Order - 1; i++) {
			right->content[i - mid] = curr->content[i];
			right->pointer[i + 1 - mid] = curr->pointer[i + 1];
		}
		curr->count = mid;
		right->count = Order - mid - 1;
		push_in(extra_entry, right, pos - mid, extra_branch);
	}
	median = curr->content[curr->count - 1];
	right->pointer[0] = curr->pointer[curr->count];
	curr->count--;
}

//when node is not full, use this function to insert
void BTree::push_in(const Dataset& d, TreeNode*& root, int location, TreeNode*& right) {
	for (int i = root->count; i > location; i--) {
		root->pointer[i + 1] = root->pointer[i];
		root->content[i] = root->content[i - 1];
	}
	
	root->content[location] = d;
	root->pointer[location + 1] = right;
	root->count++;
}

Dataset& BTree::getMedian(const TreeNode* root,const Dataset& new_entry) {
	int size = root->count;
	int t = 0, r = 0;
	Dataset* temp = new Dataset[size + 1];
	while (t < size) {
		if (new_entry > root->content[t]) {
			temp[r++] = new_entry;
		}
		else {
			temp[r++] = root->content[t++];
		}
	}
	Dataset median = temp[(size + 1) / 2];
	delete[] temp;
	return median;
}

bool BTree::FindParent(TreeNode* curr, const TreeNode*& target, TreeNode*& parent) {
	if (target == this->root) {
		parent = nullptr;
		return true;
	}
	if (curr == target) {
		return true;
	}
	int t = 0, size = curr->count;
	while (t < size) {
		if (target->content[target->count - 1] < curr->content[t]) {
			break;
		}
		t++;
	}
	parent = curr;
	curr = curr->pointer[t];
	FindParent(curr, target, parent);
}

void BTree::traverse(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	if (root->pointer[0] == nullptr) {
		int i = 0;
		while (i < root->count) {
			root->content[i++].printInfo();
		}
		return;
	}
	int t = 0;
	while (t < root->count) {
		traverse(root->pointer[t]);
		root->content[t].printInfo();
		t++;
	}
	traverse(root->pointer[t]);
}

int main()
{
	ifstream fi;
	BTree testTree[] = { BTree(), BTree(),BTree() };
	int i = 0, n[] = { 10,100, 10000 };
	Dataset item;
	bool taller = false;
	for (int j = 0; j < 3; j++) {
		fi.open("E:\\C++\\DataSet\\10000.txt");
		while (!fi.eof() && i < n[j]) {
			fi >> item.mainkey >> item.file_No >> item.division >> item.CWord >> item.i_num >> item.d_num >> item.EWord;
			testTree[j].Insert(item);
			i++;
		}
		//cout << i << endl;
		fi.close();
		//testTree[j].Traverse();
	}
	
	srand((unsigned)time(NULL));
	int t = 0, pos = 0;
	int count = 0, yes_count = 0, no_count = 0, p = 0;
	for (int j = 0; j < 3; j++) {
		t = 0; count = 0, yes_count = 0, no_count = 0, p = 0;
		while (t < 100) {
			Dataset s;
			
			s.mainkey = rand() % 10000;
			bool res = testTree[j].Find(s, pos, count);
			if (res) {
				yes_count += count;
				p++;
			}
			else {
				no_count += count;
			}
			t++;
		}
		cout << pow(10, pow(2, j)) << ":  查找到的次数:" << yes_count / (p + 1) << " 查找不到的查找次数:" << no_count / (101 - p) << endl;
	}
	return 0;
}

void sort(Dataset*& temp, int len)
{
	for (int i = 0; i < len; i++) {
		for (int j = len - 1; j > i; j--) {
			if (temp[i].mainkey > temp[j].mainkey) {
				Dataset t = temp[i];
				temp[i] = temp[j];
				temp[j] = t;
			}
		}
	}
}

bool operator<(const Dataset& d1, const Dataset& d2) 
{
	if (d1.mainkey < d2.mainkey) {
		return true;
	}
	else {
		return false;
	}
}
bool operator>(const Dataset& d1, const Dataset& d2)
{
	if (d1.mainkey > d2.mainkey) {
		return true;
	}
	else {
		return false;
	}
}
bool operator==(const Dataset& d1, const Dataset& d2)
{
	if (d1.mainkey == d2.mainkey) {
		return true;
	}
	else {
		return false;
	}
}
