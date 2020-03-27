#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
using namespace std;

struct Dataset {
	long long mainkey;
	int file;
	char division;
	int i;
	double d;
	string Cword;
	string Eword;

	Dataset() {
		mainkey = 0;
		file = 0;
		division = 0;
		i = 0;
		d = 0;
	}
	Dataset(long long m,int f, char div,int i,double d,string c,string e) {
		mainkey = m;
		file = f;
		division = div;
		this->i = i;
		this->d = d;
		Cword = c;
		Eword = e;
	}
	void printInfo() {
		cout << "mainkey: " << mainkey << " " << "fileNo: " << file << " " << "division: " << division << " ";
		cout << "int_number: " << i << " " << "double_number: " << d << " " << "CWord: " << Cword << " ";
		cout << "EWord: " << Eword << endl;
	}
	//operator==是const的成员函数
	bool operator==(const Dataset& d) const{
		if (this->mainkey == d.mainkey) {
			return true;
		}
		return false;
	}
	//friend bool operator==(const Dataset& d1, const Dataset& d2);
};
//bool operator==(const Dataset&, const Dataset&);
enum type { red, black };
class TreeNode {
private:
	type color;
	Dataset content;
	TreeNode* leftchild;
	TreeNode* rightchild;
public:
	TreeNode() {
		leftchild = nullptr;
		rightchild = nullptr;
		color = red;
	}
	TreeNode(Dataset d) {
		content = d;
		leftchild = nullptr;
		rightchild = nullptr;
		color = red;
	}
	friend class RBTree;
	//friend bool operator > (TreeNode* t1, TreeNode* t2);
	//bool operator>(TreeNode* t);
};

class RBTree {
private:
	TreeNode* root;
public:
	RBTree() {
		root = nullptr;
	}
	bool Find(const Dataset& item, int& count) {
		count = 0;
		TreeNode* res = find(this->root, item, count);
		if (res == nullptr) {
			return false;
		}
		return true;
	}
	TreeNode*& find(TreeNode*&, const Dataset& item, int& count);
	void findParent(TreeNode*, const TreeNode*, TreeNode*&);
	bool Insert(const Dataset& item) {
		bool res = insert(this->root, item);
		return res;
	}
	bool insert(TreeNode*&, const Dataset& item);
	void adjustColor(TreeNode*&);
	void Traverse() {
		InOTraverse(this->root);
	}
	void InOTraverse(TreeNode* root);
};

void RBTree::InOTraverse(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	InOTraverse(root->leftchild);
	root->content.printInfo();
	InOTraverse(root->rightchild);
}

TreeNode*& RBTree::find(TreeNode*& root, const Dataset& item, int& count) {
	if (root == nullptr) {
		count++;
		return root;
	}
	if (root->content.mainkey == item.mainkey) {
		count++;
		return root;
	}
	else if (root->content.mainkey < item.mainkey) {
		count++;
		find(root->rightchild, item, count);
	}
	else{
		count++;
		find(root->leftchild, item, count);
	}
}

void RBTree::findParent(TreeNode* root, const TreeNode* target, TreeNode*& parent) {
	if (target->content.mainkey == this->root->content.mainkey) {
		parent = nullptr;
		return;
	}
	if (root == nullptr) {
		cout << "the parameter is a nullptr" << endl;
		return;
	}
	if (root->content.mainkey == target->content.mainkey) {
		return;
	}
	else if (target->content.mainkey < root->content.mainkey) {
		parent = root;
		findParent(root->leftchild, target, parent);
	}
	else{
		parent = root;
		findParent(root->rightchild, target, parent);
	}
}

bool RBTree::insert(TreeNode*& curr, const Dataset& item)  {
	if (curr == nullptr) {
		curr = new TreeNode(item);
		adjustColor(curr);
		return true;
	}
	if (item == curr->content) {
		//cout << "duplicate!" << endl;
		return false;
	}
	else if (curr->content.mainkey > item.mainkey) {
		insert(curr->leftchild, item);
	}
	else{
		insert(curr->rightchild, item);
	}
}

void RBTree::adjustColor(TreeNode*& child) {
	TreeNode* parent = nullptr, * grandparent = nullptr, * greatgrandparent = nullptr;
	findParent(this->root, child, parent);
	if (child == nullptr) {
		return;
	}
	if (parent == nullptr) {
		child->color = black;
		return;
	}
	if (parent->color == black) {
		return;
	}
	else {
		findParent(this->root, parent, grandparent);
		findParent(this->root, grandparent, greatgrandparent);
		if (grandparent != nullptr) {
			if (grandparent->leftchild == parent) {
				if (grandparent->rightchild != nullptr && grandparent->rightchild->color == red) {
					grandparent->color = red;
					grandparent->rightchild->color = black;
					parent->color = black;
					adjustColor(grandparent);
				}
				else {
					if (parent->leftchild == child) {
						if (grandparent == this->root) {
							grandparent->leftchild = parent->rightchild;
							grandparent->color = red;
							parent->rightchild = grandparent;
							this->root = parent;
							this->root->color = black;
							return;
						}
						else {
							if (greatgrandparent != nullptr) {
								if (greatgrandparent->leftchild == grandparent) {
									grandparent->leftchild = parent->rightchild;
									grandparent->color = red;
									parent->rightchild = grandparent;
									parent->color = black;
									greatgrandparent->leftchild = parent;
									return;
								}
								else {
									grandparent->leftchild = parent->rightchild;
									grandparent->color = red;
									parent->rightchild = grandparent;
									parent->color = black;
									greatgrandparent->rightchild = parent;
									return;
								}								
							}
							else {
								cout << "Error:Greatparent is a nullptr but grandparent is not the root." << endl;
							}
						}
					}
					if (parent->rightchild == child) {
						if (grandparent == this->root) {
							TreeNode* temp = child;
							grandparent->leftchild = child->rightchild;
							grandparent->color = red;
							parent->rightchild = child->leftchild;
							parent->color = red;
							temp->leftchild = parent;
							temp->rightchild = grandparent;
							this->root = temp;
							this->root->color = black;
							return;
						}
						else {
							if (greatgrandparent != nullptr) {
								if (greatgrandparent->leftchild == grandparent) {
									TreeNode* temp = child;
									grandparent->leftchild = child->rightchild;
									grandparent->color = red;
									parent->rightchild = child->leftchild;
									parent->color = red;
									temp->leftchild = parent;
									temp->rightchild = grandparent;
									temp->color = black;
									greatgrandparent->leftchild = temp;
									return;
								}
								else {
									TreeNode* temp = child;
									grandparent->leftchild = child->rightchild;
									grandparent->color = red;
									parent->rightchild = child->leftchild;
									parent->color = red;
									temp->leftchild = parent;
									temp->rightchild = grandparent;
									temp->color = black;
									greatgrandparent->rightchild = temp;
									return;
								}
							}
							else {
								cout << "Error:Greatparent is a nullptr but grandparent is not the root." << endl;
							}
						}
					}
				}
			}
			else if (grandparent->rightchild == parent) {
				if (grandparent->leftchild != nullptr && grandparent->leftchild->color == red) {
					grandparent->color = red;
					grandparent->leftchild->color = black;
					parent->color = black;
					adjustColor(grandparent);
				}
				else {
					if (parent->leftchild == child) {
						if (grandparent == this->root) {
							TreeNode* temp = child;
							grandparent->rightchild = child->leftchild;
							grandparent->color = red;
							parent->leftchild = child->rightchild;
							parent->color = red;
							temp->leftchild = grandparent;
							temp->rightchild = parent;
							this->root = temp;
							this->root->color = black;
							return;
						}
						else {
							if (greatgrandparent != nullptr) {
								if (greatgrandparent->leftchild == grandparent) {
									TreeNode* temp = child;
									grandparent->rightchild = child->leftchild;
									grandparent->color = red;
									parent->leftchild = child->rightchild;
									parent->color = red;
									temp->leftchild = grandparent;
									temp->rightchild = parent;
									temp->color = black;
									greatgrandparent->leftchild = temp;
									return;
								}
								else {
									TreeNode* temp = child;
									grandparent->rightchild = child->leftchild;
									grandparent->color = red;
									parent->leftchild = child->rightchild;
									parent->color = red;
									temp->leftchild = grandparent;
									temp->rightchild = parent;
									temp->color = black;
									greatgrandparent->rightchild = temp;
									return;
								}
							}
							else {
								cout << "Error:Greatparent is a nullptr but grandparent is not the root." << endl;
							}
						}
					}
					if (parent->rightchild == child) {
						if (grandparent == this->root) {
							grandparent->rightchild = parent->leftchild;
							grandparent->color = red;
							parent->leftchild = grandparent;
							this->root = parent;
							this->root->color = black;
							return;
						}
						else {
							if (greatgrandparent != nullptr) {
								if (greatgrandparent->leftchild == grandparent) {
									grandparent->rightchild = parent->leftchild;
									grandparent->color = red;
									parent->leftchild = grandparent;
									parent->color = black;
									greatgrandparent->leftchild = parent;
									return;
								}
								else {
									grandparent->rightchild = parent->leftchild;
									grandparent->color = red;
									parent->leftchild = grandparent;
									parent->color = black;
									greatgrandparent->rightchild = parent;
									return;
								}
							}
							else {
								cout << "Error:Greatparent is a nullptr but grandparent is not the root." << endl;
							}
						}
						
					}
				}
			}
			else {
				cout << "Error:Grandparent has more than two children." << endl;
				return;
			}
		}
	}
}

int main()
{
	ifstream fi;
	RBTree testTree[] = { RBTree(), RBTree(),RBTree() };
	int i = 0, n[] = { 10,100, 10000 };
	Dataset temp;
	for (int j = 0; j < 3; j++) {
		fi.open("E:\\C++\\DataSet\\10000.txt");
		while (!fi.eof() && i < n[j]) {
			fi >> temp.mainkey >> temp.file >> temp.division >> temp.Cword >> temp.i >> temp.d >> temp.Eword;
			testTree[j].Insert(temp);
			i++;
		}
		fi.close();
	}
	//testTree[2].Traverse();
	srand((unsigned)time(NULL));
	int t, p;
	int count = 0, yes_count = 0, no_count = 0;
	for (int j = 0; j < 3; j++) {
		t = 0; p = 0;
		count = 0, yes_count = 0, no_count = 0;
		while (t < 100) {
			Dataset s;
			s.mainkey = rand()%10000;
			bool res = testTree[j].Find(s, count);
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

bool operator<(Dataset d1, Dataset d2) {
	if (d1.mainkey < d2.mainkey) {
		return true;
	}
	return false;
}
bool operator>(Dataset d1, Dataset d2) {
	if (d1.mainkey > d2.mainkey) {
		return true;
	}
	return false;
}
//bool operator==(const Dataset& d1, const Dataset& d2) {
//	if (d1.mainkey == d2.mainkey) {
//		return true;
//	}
//	return false;
//}
bool operator<(Dataset& d1, const Dataset& d2) {
	if (d1.mainkey < d2.mainkey) {
		return true;
	}
	return false;
}
//bool operator>(TreeNode* t1, TreeNode* t2) {
//	if (t1->content.mainkey > t2->content.mainkey) {
//		return true;
//	}
//	return false;
//}


