#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <vector>


using namespace std;

struct Dataset
{
	long long mainkey;
	int file_No;
	char division;
	string province;
	int int_number;
	double double_number;
	string word;

	Dataset()
	{
		mainkey = 0;
		file_No = 0;
		division = 0;
		int_number = 0;
		double_number = 0;
	}
	void printInfo()
	{
		cout << "主键:" << mainkey << '\t' << "文件:" << file_No << '\t' << "分区:" << division << '\t' << "中文字符串:" << province << '\t';
		cout << "整型:" << int_number << '\t' << "浮点型:" << double_number << '\t' << "英文字符串:" << word << endl;
	}
	void change_div(char div) {
		this->division = div;
	}

};

class Node
{
private:
	Dataset d;
	Node* next;

public:
	Node(Dataset d, Node* next)
	{
		this->d = d;
		this->next = next;
	}
	friend class List;
	Dataset getDataset() { return d; }
	Node* getNext() { return next; }
	void insert_node_orderedKey(List*& l, int i, int len);
	~Node() {}
};

class List
{
private:
	Node* head;

public:
	List()
	{
		Dataset pre;
		head = new Node(pre, NULL);
	}
	~List() {}
	void set_index(char div) {
		head->d.change_div(div);
	}
	Node* getHead() { return head; }
	bool isEmpty() {
		if (head->next == NULL) return true;
		else return false;
	}
	bool isFull(Node * current) {
		if (current != head && current->next == nullptr) { return true; }
		else return false;
	}
	int insert_node(Dataset);
	int insert_node_orderedKey(Dataset);
	void delete_node(long long mainkey);
	void printInfo(ofstream & outfile);
	void printToScreen();
	int FindMainkey(int, int);
	void insert(int,int);
};

int List::insert_node(Dataset d)
{
	Dataset d0;
	int node_count = 0;
	Node* current = head;
	while (current->next != nullptr && current->next->d.int_number < d.int_number)
	{
		current = current->next;
	}
	current->next = new Node(d, current->next);
	node_count++;
	return node_count;
}

//生成第i个文件的长度为len的主键顺序链表
void List::insert(int i, int len) 
{
	ifstream Fin[10] = { ifstream("E:\\C++\\DataSet\\1.txt"),ifstream("E:\\C++\\DataSet\\2.txt"),
	   ifstream("E:\\C++\\DataSet\\3.txt"),ifstream("E:\\C++\\DataSet\\4.txt"),ifstream("E:\\C++\\DataSet\\5.txt"),
	   ifstream("E:\\C++\\DataSet\\6.txt"),ifstream("E:\\C++\\DataSet\\7.txt"),ifstream("E:\\C++\\DataSet\\8.txt"),
	   ifstream("E:\\C++\\DataSet\\9.txt"),ifstream("E:\\C++\\DataSet\\10.txt") };
	Node* curr = this->head;
	Dataset temp;
	
	int k = 0;
	Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;
	curr->next = new Node(temp, curr->next);
	k++;
	while (k < len && !Fin[i].eof())
	{
		Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;
		curr->next = new Node(temp, curr->next);
		k++;
	}
	Fin[i].close();
	
	
}

int List::insert_node_orderedKey(Dataset d)
{
	int node_count = 0;
	Node* curr = this->head;
	ifstream FBin[10] = { ifstream("E:\\C++\\DataSet\\DataSet\\01.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\02.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\03.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\04.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\05.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\06.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\07.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\08.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\09.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\010.dat",ios::in | ios::binary) };;
	
	Dataset temp;
	//int k = 0;
	//Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;
	//FBin[i].read((char*)(&temp),sizeof(Dataset));
	//curr->next = new Node(temp, curr->next);
	//k++;
	while (curr->next != nullptr)
	{
		curr = curr->next;
	}
	curr->next = new Node(temp, curr->next);
	node_count++;
	return node_count;
	
}

void List::delete_node(long long mainkey)
{
	Node* current = head, * temp;
	while (current->next != nullptr && current->next->d.mainkey < mainkey)
	{
		current = current->next;
	}
	if (current->next != nullptr && current->next->d.mainkey == mainkey) {
		temp = current->next;
		current->next = current->next->next;
		delete temp;
	}
	else if (current->next != nullptr && current->next->d.mainkey > mainkey)
	{
		cout << "找不到主键为" << mainkey << "的信息" << endl;
		return;
	}
	else if (isFull(current))
	{
		cout << "找不到主键为" << mainkey << "的信息" << endl;
		return;
	}
}

void List::printInfo(ofstream& outfile)
{
	Node* current = head->next;
	Dataset d;
	/*outfile << "主键" << '\t' << "文件" << '\t' << "分区" << '\t' << "省份" << '\t';
	outfile << "整型" << '\t' << "浮点" << '\t' << "单词" << endl;*/
	while (current->next != nullptr) {
		d = current->getDataset();
		outfile << d.mainkey << '\t' << d.file_No << '\t' << d.division << '\t' << d.province << '\t';
		outfile << d.int_number << '\t' << d.double_number << '\t' << d.word << endl;
		//outfile.write((char*)(&d), sizeof(Dataset));
		current = current->next;
	}
	d = current->getDataset();
	outfile << d.mainkey << '\t' << d.file_No << '\t' << d.division << '\t' << d.province << '\t';
	outfile << d.int_number << '\t' << d.double_number << '\t' << d.word << endl;
	//outfile.write((char*)(&d), sizeof(Dataset));
}

void List::printToScreen()
{
	Node* current = head->next;
	Dataset d;
	int t = 0;
	cout << "主键" << '\t' << "文件" << '\t' << "分区" << '\t' << "省份" << '\t';
	cout << "整型" << '\t' << "浮点" << '\t' << "单词" << endl;
	while (t < 10) {
		d = current->getDataset();
		cout << d.mainkey << '\t' << d.file_No << '\t' << d.division << '\t' << d.province << '\t';
		cout << d.int_number << '\t' << d.double_number << '\t' << d.word << endl;
		current = current->next;
		t++;
	}
}

int List::FindMainkey(int mainkey, int len) 
{
	Node* curr = this->head;
	int t = 0;
	while (curr != nullptr && t < len) 
	{
		t++;
		if (curr->getDataset().mainkey == mainkey && mainkey != 0)
		{
			cout << "List: " << endl;
			curr->getDataset().printInfo();
			return t - 1;
		}
		else if (curr->getDataset().mainkey == mainkey && curr->getDataset().mainkey == 0)
		{
			break;
		}
		curr = curr->next;
	}
	cout << "list: NOT FOUND!" << endl;
	return t;
}

struct dataset
{
	int mainkey;
	int file;
	char div;
	double d;
	int i;
	string province;
	string word;

	dataset(int m, int f, char div, char pro[], int int_num, double double_num, char word[])
	{
		mainkey = m;
		file = f;
		this->div = div;
		province = pro;
		this->word = word;
		i = int_num;
		d = double_num;
	}
	dataset()
	{
		mainkey = 0;
		file = 0;
		div = 0;
		
		i = 0;
		d = 0;
	}
	void printInfo()
	{
		cout << "主键:" << mainkey << '\t' << "文件:" << file << '\t' << "分区:" << div << '\t' << "中文字符串:" << province << '\t';
		cout << "整型:" << i << '\t' << "浮点型:" << d << '\t' << "英文字符串:" << word << endl;
	}
};

class TreeNode 
{
private:
	dataset content;
	TreeNode* leftchild;
	TreeNode* rightchild;
public:
	TreeNode() 
	{
		leftchild = nullptr;
		rightchild = nullptr;
	}
	TreeNode(dataset content) 
	{
		this->content = content;
		leftchild = nullptr;
		rightchild = nullptr;
	}
	int getLeftContent() 
	{
		if (this->leftchild != nullptr) 
		{
			return this->leftchild->content.mainkey;
		}
		else 
		{
			return -1;
		}
	}
	int getRightContent() 
	{
		if(this->rightchild != nullptr)
		{
			return this->rightchild->content.mainkey;
		}
		else 
		{
			return -1;
		}
	}
	friend class BST;
};

class BST 
{
private:
	TreeNode* root;
	int NodeDegree(TreeNode*);
public:
	BST() 
	{
		root = new TreeNode();
	}
	bool insert(TreeNode* &, dataset item);
	bool Insert(dataset* item, int len);
	TreeNode*& find(TreeNode*, int item);
	TreeNode* find_non(TreeNode*&, int, int&);
	//TreeNode* find_parent(TreeNode*, int);
	int Find(int item);
	bool remove(int item);
	void traverse(TreeNode* root);
	void Traverse();
	

};

int BST::NodeDegree(TreeNode* node) 
{
	if (node->leftchild == nullptr && node->rightchild == nullptr) 
	{
		return 0;
	}
	else if (node->leftchild == nullptr || node->rightchild == nullptr) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

bool BST::insert(TreeNode* &root, dataset item) 
{
	if (root == nullptr) 
	{
		root = new TreeNode(item);
		return true;
	}
	if (root->content.mainkey == 0)
	{
		root->content = item;
		return true;
	}
	else if (root->content.mainkey < item.mainkey) 
	{
		insert(root->rightchild, item);
	}
	else if (root->content.mainkey > item.mainkey) 
	{
		insert(root->leftchild, item);
	}
	else if (root->content.mainkey == item.mainkey)
	{
		/*cout << "Fail to insert Node:";
		item.printInfo();
		cout << " There has already been a TreeNode in the tree." << endl;*/
		return false;
	}
	return true;
}

bool BST::Insert(dataset* item, int len) 
{
	int k = 0;
	while (k < len) 
	{
		insert(root, item[k]);
		k++;
	}
	return true;
}

TreeNode*& BST::find(TreeNode* root, int item)
{
	if (root == nullptr || root->content.mainkey == item)
	{

		return root;
	}
	else if (root->content.mainkey > item)
	{

		return find(root->leftchild, item);
	}
	else if (root->content.mainkey < item)
	{

		return find(root->rightchild, item);
	}
}

TreeNode* BST::find_non(TreeNode* &parent, int item, int& num) 
{
	TreeNode* curr = root;
	num = 0;
	while (curr != nullptr && curr->content.mainkey != item) 
	{
		num++;
		if (curr->content.mainkey < item) 
		{
			parent = curr;
			curr = curr->rightchild;
		}
		else if (curr->content.mainkey > item) 
		{
			parent = curr;
			curr = curr->leftchild;
		}
		else if (curr->content.mainkey == item && item == 0) 
		{
			break;
		}
	}
	return curr;
	/*if (curr == nullptr) 
	{
		return nullptr;
	}
	if (curr->content == item) 
	{
		return curr;
	}*/
}


int BST::Find(int item) 
{
	TreeNode* result = nullptr;
	int num = 0;
	result = find_non(root, item, num); 
	find(root, item);
	if (result == nullptr || item == 0) 
	{
		cout << "Binary Search Tree: NOT FOUND!" << endl;
		return num;
	}
	else 
	{
		cout << "Binary Search Tree: " << endl;
		result->content.printInfo();
		return num;
	}
}

void BST::traverse(TreeNode* root)
{
	if (root == nullptr)
		return;
	traverse(root->leftchild);
	root->content.printInfo();
	traverse(root->rightchild);
}

bool BST::remove(int item) 
{
	TreeNode* parent = nullptr;
	int num = 0;
	TreeNode* node = find_non(parent, item, num);
	if (node == nullptr) 
	{
		cout << "Failed to find the TreeNode!" << endl;
		return false;
	}
	else 
	{
		switch (NodeDegree(node)) 
		{
		case 0: 
		{
			delete node;
			break;
		}
		case 1: 
		{
			if (node->leftchild != nullptr) 
			{
				if (parent->leftchild == node) 
				{
					parent->leftchild = node->leftchild;
					delete node;
					break;
				}
				else 
				{
					parent->rightchild = node->leftchild;
					delete node;
					break;
				}
			}
			else if (node->rightchild != nullptr) 
			{
				if (parent->leftchild == node) 
				{
					parent->leftchild = node->rightchild;
					delete node;
					break;
				}
				else 
				{
					parent->rightchild = node->rightchild;
					delete node;
					break;
				}
			}
			break;
		}
		case 2: 
		{
			TreeNode* ParentOfCurr = nullptr;
			TreeNode* curr = node;
			while(curr->rightchild != nullptr) 
			{
				curr = curr->rightchild;
			}
			if (curr->leftchild == nullptr) 
			{
				node->content = curr->content;
				delete curr;
				break;
			}
			else 
			{
				find_non(ParentOfCurr, curr->content.mainkey, num);
				if (ParentOfCurr->leftchild == curr)
				{
					ParentOfCurr->leftchild = curr->leftchild;
					node->content = curr->content;
					delete curr;
					break;
				}
				else
				{
					ParentOfCurr->rightchild = curr->leftchild;
					node->content = curr->content;
					delete curr;
					break;
				}
			}
		}
		}
		return true;
	}
}

void BST::Traverse() 
{
	traverse(root);
}

//生成10个主键乱序的链表
List* GenerateChaoticNumber(int len)
{
	ifstream Fin[10] = { ifstream("E:\\C++\\DataSet\\1.txt"),ifstream("E:\\C++\\DataSet\\2.txt"),
	ifstream("E:\\C++\\DataSet\\3.txt"),ifstream("E:\\C++\\DataSet\\4.txt"),ifstream("E:\\C++\\DataSet\\5.txt"),
	ifstream("E:\\C++\\DataSet\\6.txt"),ifstream("E:\\C++\\DataSet\\7.txt"),ifstream("E:\\C++\\DataSet\\8.txt"),
	ifstream("E:\\C++\\DataSet\\9.txt"),ifstream("E:\\C++\\DataSet\\10.txt") };
	ofstream Fout[10] = { ofstream("E:\\C++\\DataSet\\01.txt"),ofstream("E:\\C++\\DataSet\\02.txt"),
	ofstream("E:\\C++\\DataSet\\03.txt"),ofstream("E:\\C++\\DataSet\\04.txt"),ofstream("E:\\C++\\DataSet\\05.txt"),
	ofstream("E:\\C++\\DataSet\\06.txt"),ofstream("E:\\C++\\DataSet\\07.txt"),ofstream("E:\\C++\\DataSet\\08.txt"),
	ofstream("E:\\C++\\DataSet\\09.txt"),ofstream("E:\\C++\\DataSet\\010.txt") };
	ifstream FBin[10] = { ifstream("E:\\C++\\DataSet\\DataSet\\01.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\02.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\03.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\04.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\05.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\06.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\07.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\08.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\09.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\010.dat",ios::in | ios::binary) };;
	ofstream FBout[10] = { ofstream("E:\\C++\\DataSet\\DataSet\\1.dat",ios::out | ios::binary),ofstream("E:\\C++\\DataSet\\DataSet\\2.dat",ios::out | ios::binary),
	ofstream("E:\\C++\\DataSet\\DataSet\\3.dat",ios::out | ios::binary),ofstream("E:\\C++\\DataSet\\DataSet\\4.dat",ios::out | ios::binary),ofstream("E:\\C++\\DataSet\\DataSet\\5.dat",ios::out | ios::binary),
	ofstream("E:\\C++\\DataSet\\DataSet\\6.dat",ios::out | ios::binary),ofstream("E:\\C++\\DataSet\\DataSet\\7.dat",ios::out | ios::binary),ofstream("E:\\C++\\DataSet\\DataSet\\8.dat",ios::out | ios::binary),
	ofstream("E:\\C++\\DataSet\\DataSet\\9.dat",ios::out | ios::binary),ofstream("E:\\C++\\DataSet\\DataSet\\10.dat",ios::out | ios::binary) };;

	List* list = new List[10];
	Dataset temp;
	for (int i = 0; i < 10; i++)
	{
		int k = 0;
		Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;
		list[i].insert_node(temp);
		k++;
		while (k < len && !Fin[i].eof()) 
		{
			Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;
			//FBin[i].read((char*)(&temp), sizeof(Dataset));
			list[i].insert_node(temp);
			k++;
		}

		Fin[i].close();
		list[i].printInfo(Fout[i]);
		//list[i].printToScreen();
	}
	return list;
}

List* GenerateOrderedNumber(int len) 
{
	ifstream Fin[10] = { ifstream("E:\\C++\\DataSet\\1.txt"),ifstream("E:\\C++\\DataSet\\2.txt"),
	   ifstream("E:\\C++\\DataSet\\3.txt"),ifstream("E:\\C++\\DataSet\\4.txt"),ifstream("E:\\C++\\DataSet\\5.txt"),
	   ifstream("E:\\C++\\DataSet\\6.txt"),ifstream("E:\\C++\\DataSet\\7.txt"),ifstream("E:\\C++\\DataSet\\8.txt"),
	   ifstream("E:\\C++\\DataSet\\9.txt"),ifstream("E:\\C++\\DataSet\\10.txt") };
	List* list = new List[10];
	Dataset temp;
	for (int i = 0; i < 10; i++)
	{
		int k = 0;
		Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;
		list[i].insert_node(temp);
		k++;
		while (k < len && !Fin[i].eof())
		{
			Fin[i] >> temp.mainkey >> temp.file_No >> temp.division >> temp.province >> temp.int_number >> temp.double_number >> temp.word;

			list[i].insert_node_orderedKey(temp);
			k++;
		}

		Fin[i].close();
	}
	return list;
}

//生成第i个文件的长度为len的主键乱序数组
dataset* disorderedKeyArray(int i,int len) 
{
	
	ifstream FB[10] = { ifstream("E:\\C++\\DataSet\\DataSet\\1.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\2.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\3.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\4.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\5.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\6.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\7.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\8.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\9.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\10.dat",ios::in | ios::binary) };
	ifstream Fin[10] = { ifstream("E:\\C++\\DataSet\\01.txt"),ifstream("E:\\C++\\DataSet\\02.txt"),
	ifstream("E:\\C++\\DataSet\\03.txt"),ifstream("E:\\C++\\DataSet\\04.txt"),ifstream("E:\\C++\\DataSet\\05.txt"),
	ifstream("E:\\C++\\DataSet\\06.txt"),ifstream("E:\\C++\\DataSet\\07.txt"),ifstream("E:\\C++\\DataSet\\08.txt"),
	ifstream("E:\\C++\\DataSet\\09.txt"),ifstream("E:\\C++\\DataSet\\010.txt") };
	
	dataset* test;
	test = new dataset[len];
	int t = 0;
	Fin[i] >> test[t].mainkey >> test[t].file >> test[t].div >> test[t].province >> test[t].i >> test[t].d >> test[t].word;
	t++;
	while (!Fin[i].eof() && t < len)
	{
		Fin[i]>> test[t].mainkey >> test[t].file >> test[t].div >> test[t].province >> test[t].i >> test[t].d >> test[t].word;
		//FB[i].read((char*)(&test[t]), sizeof(dataset));
		t++;
	}
	Fin[i].close();
	return test;
}

int ArrayFind(dataset* toFind, int len, int mainkey) 
{
	int t = 0;
	while (t < len) 
	{
		if (toFind[t].mainkey == mainkey && mainkey != 0)
		{
			cout << "Array: " << endl;
			toFind[t].printInfo();
			return t;
		}
		if (toFind[t].mainkey == mainkey && toFind[t].mainkey == 0)
		{
			break;
		}
		t++;
	}
	cout << "Array: NOT FOUND!" << endl;
	return t;
}
int ArrayFind(Dataset* toFind, int len, int mainkey)
{
	
	int t = 0;
	while (t < len)
	{
		if (toFind[t].mainkey == mainkey && mainkey != 0)
		{
			cout << "Array: " << endl;
			toFind[t].printInfo();
			return t;
		}
		if (toFind[t].mainkey == mainkey && toFind[t].mainkey == 0)
		{
			break;
		}		
		t++;
	}
	cout << "Array: NOT FOUND!" << endl;
	return t;
}

//生成第i个文件的长度为len的主键顺序数组
Dataset* orderedKeyArray(int i, int len)
{
	Dataset* d = new Dataset[len];
	ifstream FBin[10] = { ifstream("E:\\C++\\DataSet\\DataSet\\01.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\02.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\03.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\04.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\05.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\06.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\07.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\08.dat",ios::in | ios::binary),
	ifstream("E:\\C++\\DataSet\\DataSet\\09.dat",ios::in | ios::binary),ifstream("E:\\C++\\DataSet\\DataSet\\010.dat",ios::in | ios::binary) };;
	ifstream Fin[10] = { ifstream("E:\\C++\\DataSet\\01.txt"),ifstream("E:\\C++\\DataSet\\02.txt"),
	ifstream("E:\\C++\\DataSet\\03.txt"),ifstream("E:\\C++\\DataSet\\04.txt"),ifstream("E:\\C++\\DataSet\\05.txt"),
	ifstream("E:\\C++\\DataSet\\06.txt"),ifstream("E:\\C++\\DataSet\\07.txt"),ifstream("E:\\C++\\DataSet\\08.txt"),
	ifstream("E:\\C++\\DataSet\\09.txt"),ifstream("E:\\C++\\DataSet\\010.txt") };

	Dataset temp;
	int t = 0;
	Fin[i] >> d[t].mainkey >> d[t].file_No >> d[t].division >> d[t].province >> d[t].int_number >> d[t].double_number >> d[t].word;
	//FBin[i].read((char*)(&d[t]), sizeof(Dataset));
	t++;
	while (t < len && !FBin[i].eof()) 
	{
		Fin[i] >> d[t].mainkey >> d[t].file_No >> d[t].division >> d[t].province >> d[t].int_number >> d[t].double_number >> d[t].word;
		//FBin[i].read((char*)(&d[t]), sizeof(Dataset));
		t++;
	}
	Fin[i].close();
	return d;
}

int main()
{
	List l;
	l.insert(1,10);
	
	l.printToScreen();
	srand((unsigned)time(NULL));
	//srand(42);
	BST* testTree;
	List mainkeyorderedList[10],* mainkeydisorderedList;
	dataset** mainkeydisorderedArray;
	Dataset** mainkeyorderedArray;
	mainkeydisorderedArray = new dataset * [10];
	mainkeyorderedArray = new Dataset * [10];
	testTree = new BST[10];
	int amount[] = { 10,100,10000 };
	int counter[5][3] = { 0 }, toFind = 0;
	for (int t = 0; t < 3; t++) 
	{
		toFind = rand() % amount[t] + 1;
		mainkeydisorderedList = GenerateChaoticNumber(amount[t]);
		//mainkeyorderedList = GenerateOrderedNumber(amount[t]);
		for (int i = 0; i < 10; i++)
		{
			mainkeyorderedList[i].insert(i,amount[t]);
			mainkeyorderedArray[i] = orderedKeyArray(i, amount[t]);
			mainkeydisorderedArray[i] = disorderedKeyArray(i, amount[t]);
			mainkeyorderedList[i].printToScreen();
			testTree[i].Insert(mainkeydisorderedArray[i], amount[t]);
			counter[0][t] += ArrayFind(mainkeyorderedArray[i], amount[t], mainkeyorderedArray[i][toFind].mainkey);
			counter[1][t] += ArrayFind(mainkeydisorderedArray[i], amount[t], mainkeydisorderedArray[i][toFind].mainkey);
			counter[2][t] += mainkeyorderedList[i].FindMainkey(mainkeyorderedArray[i][toFind].mainkey, amount[t]);
			counter[3][t] += mainkeydisorderedList[i].FindMainkey(mainkeydisorderedArray[i][toFind].mainkey, amount[t]);
			counter[4][t] += testTree[i].Find(mainkeydisorderedArray[i][toFind].mainkey);
		}
		counter[0][t] = counter[0][t] / 10;
		counter[1][t] = counter[1][t] / 10;
		counter[2][t] = counter[2][t] / 10;
		counter[3][t] = counter[3][t] / 10;
		counter[4][t] = counter[4][t] / 10;
	}
	
	for (int i = 0; i < 5; i++) 
	{
		switch (i) 
		{
		case 0:
			cout << "orderedArray: ";
			break;
		case 1:
			cout << "disorderedArray: ";
			break;
		case 2:
			cout << "orderedList: ";
			break;
		case 3:
			cout << "disorderedList: ";
			break;
		case 4:
			cout << "Binary Search Tree: ";
			break;
		}
		for (int j = 0; j < 3; j++) 
		{
			cout << "数据量:" << amount[j] << ":" << counter[i][j] << " ";
		}
		cout << endl;
	}
}


