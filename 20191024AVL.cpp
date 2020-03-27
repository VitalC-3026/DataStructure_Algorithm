#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

struct Dataset
{
	long long mainkey;
	int file_No;
	char division;
	string CNWord;
	int int_num;
	double double_num;
	string EnglishWord;
	Dataset() 
	{
		mainkey = 0;
		file_No = 0;
		division = 0;
		int_num = 0;
		double_num = 0;
	}
	Dataset(long long mainkey, int file_No, char division, string CNword, string EngWord, int i, double d) {
		this->mainkey = mainkey;
		this->file_No = file_No;
		this->division = division;
		this->CNWord = CNWord;
		this->int_num = i;
		this->double_num = d;
		this->EnglishWord = EngWord;
	}
	void SetDataset(Dataset d) 
	{
		this->mainkey = d.mainkey;
		this->file_No = d.file_No;
		this->division = d.division;
		this->CNWord = d.CNWord;
		this->int_num = d.int_num;
	}
	Dataset GetDataset(Dataset d) 
	{
		return *this;
	}
	void printInfo()
	{
		cout << "mainkey: " << mainkey<<" file_No: "<<file_No<<" division: "<<division;
		cout << " int_number: " << int_num << " double_number: " << double_num;
		cout << " Chinese: " << CNWord << " English: " << EnglishWord << endl;
	}
};

//left_higher<0 equal_height=0 right_higher>0
class TreeNode {
private:
	Dataset content;
	int balance_index;
	TreeNode* leftchild;
	TreeNode* rightchild;

public:
	TreeNode() 
	{
		balance_index = 0;
		leftchild = nullptr;
		rightchild = nullptr;
	}
	TreeNode(Dataset d) 
	{
		content = d;
		balance_index = 0;
		leftchild = nullptr;
		rightchild = nullptr;
 	}
	
	~TreeNode() {}
	Dataset getContent()
	{
		return content;
	}
	friend class AVL;
};

class AVL {
private:
	TreeNode* root;
public:
	AVL() 
	{
		root = nullptr;
	}
	int TreeHeight(TreeNode* root);
	void setAllBalanceFactor(TreeNode*&);
	int setBalanceFactor(TreeNode*&);
	//void getBalanceFactorIsTwo(TreeNode*, TreeNode*&);//不在返回值中获取这个节点是因为递归调用无法在入口函数得到经过很多层函数底下的那个节点
	//void getBalanceFactorIsTwoFather(TreeNode*, TreeNode*&);
	TreeNode* getParent(TreeNode*, TreeNode*, TreeNode* &parent);
	void LLAdjust(TreeNode*&);
	void LRAdjust(TreeNode*&);
	void RRAdjust(TreeNode*&);
	void RLAdjust(TreeNode*&);
	bool insert(const Dataset& d, TreeNode*& root, bool& taller);
	bool Insert(const Dataset& d, bool& taller) 
	{
		bool res = insert(d, this->root, taller);
		return res;
	}
	void levelTraverse(TreeNode* root);
	TreeNode* getRoot() 
	{
		return this->root;
	}
	TreeNode*& find(TreeNode*, int item, int& count);
	bool Find(int num, int& count) {
		count = 0;
		TreeNode* res = find(this->root, num, count);
		if (res == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}
	bool remove(Dataset d);
	void BiTreeToArray(TreeNode* t, Dataset[], int, int&);
	void LevelTraverse(TreeNode*, Dataset[], int);
	~AVL() {}
	
};

TreeNode*& AVL::find(TreeNode* root, int item, int& count)
{
	if (root == nullptr )
	{
		count++;
		//cout << "NO:" << count << endl;
		return root;
	}
	else if (root->content.mainkey == item) {
		count++;
		//cout << "YES:" << count << endl;
		return root;
	}
	else if (root->content.mainkey > item)
	{
		count++;
		return find(root->leftchild, item, count);
	}
	else if (root->content.mainkey < item)
	{
		count++;
		return find(root->rightchild, item, count);
	}
}

int AVL::TreeHeight(TreeNode* root) 
{
	try{
		int left_sub = 0, right_sub = 0;
		if (root == nullptr)
		{
			return 0;
		}
		else
		{
			if (root->leftchild == nullptr) {
				left_sub = 0;
			}
			else {
				left_sub = TreeHeight(root->leftchild);
			}
			if (root->rightchild == nullptr) {
				right_sub = 0;
			}
			else {
				right_sub = TreeHeight(root->rightchild);
			}
		}
		int res = (left_sub > right_sub ? left_sub : right_sub) + 1;
		return res;
	}
	catch (exception e) {
		e.what();
		return 0;
	}
	
}

int AVL::setBalanceFactor(TreeNode* &root) 
{
	int left_height = 0, right_height = 0;
	if (root) 
	{
		if (root->leftchild) {
			left_height = TreeHeight(root->leftchild);
		}
		else {
			left_height = 0;
		}
		if (root->rightchild) {
			right_height = TreeHeight(root->rightchild);
		}
		else {
			right_height = 0;
		}
		root->balance_index = right_height - left_height;
		return root->balance_index;
	}
	else {
		return 0;
	}
	
}

void AVL::setAllBalanceFactor(TreeNode* &root) 
{
	if (root == nullptr) {
		return;
	}
	setBalanceFactor(root);
	setAllBalanceFactor(root->leftchild);
	setAllBalanceFactor(root->rightchild);
}

//void AVL::getBalanceFactorIsTwo(TreeNode* root, TreeNode*& goal) 
//{
//	if (root == nullptr) {
//		return;
//	}
//	else {
//		if (root->balance_index == 2) {
//			root = goal;
//		}
//		else if(root->balance_index == -2){
//			root = goal;
//		}
//		getBalanceFactorIsTwo(root->leftchild, goal);
//		getBalanceFactorIsTwo(root->rightchild, goal);
//	}
//}
//
//void AVL::getBalanceFactorIsTwoFather(TreeNode* root, TreeNode* & father) 
//{
//	if (root != nullptr) {
//		if (root->leftchild != nullptr) {
//			if (root->leftchild->balance_index == 2 || root->leftchild->balance_index == -2) {
//				father = root;
//			}
//		}
//		if (root->rightchild != nullptr) {
//			if (root->rightchild->balance_index == 2 || root->rightchild->balance_index == -2) {
//				father = root;
//			}
//		}
//		getBalanceFactorIsTwoFather(root->leftchild, father);
//		getBalanceFactorIsTwoFather(root->rightchild, father);
//	}
//}

TreeNode* AVL::getParent(TreeNode* root, TreeNode* goal, TreeNode* &parent) 
{
	if (root == nullptr) {
		cout << "no father found";
		return nullptr;
	}
	else if (root->leftchild == goal || root->rightchild == goal) {
		parent = root;
		return root;
	}
	else {
		if (root->content.mainkey < goal->content.mainkey) {
			getParent(root->rightchild, goal, parent);
		}
		if (root->content.mainkey > goal->content.mainkey) {
			getParent(root->leftchild, goal, parent);
		}
	}
}

bool AVL::insert(const Dataset& d, TreeNode*& root, bool& taller)
{
	if (root == nullptr){
		root = new TreeNode(d);
		setAllBalanceFactor(this->root);
		taller = true;
		return true;;
	}
	else{
		if (d.mainkey < root->content.mainkey){
			insert(d, root->leftchild, taller);
			if (taller && root->balance_index == -2) {			
				switch (root->leftchild->balance_index) {
				case -1: {
					LLAdjust(root);
					taller = false;
					setAllBalanceFactor(this->root);
					break;
				}
				case 1: {
					LRAdjust(root);
					taller = false;
					setAllBalanceFactor(this->root);
					break;
				}
				case 0: {
					std::cout << "There is something wrong in LAdjust!" << endl;
					break;
				}
				}
			}	
		}
		else if (d.mainkey > root->content.mainkey) {
			insert(d, root->rightchild, taller);
			if (taller && root->balance_index == 2) {
				switch (root->rightchild->balance_index) {
				case -1: {
					RLAdjust(root);
					taller = false;
					setAllBalanceFactor(this->root);
					break;
				}
				case 1: {
					RRAdjust(root);
					taller = false;
					setAllBalanceFactor(this->root);
					break;
				}
				case 0: {
					std::cout << "There is something wrong in RAdjust!" << endl;
					break;
				}
				}
			}
		}
		else {
			//cout << "The NODE has been inserted." << endl;
			taller = false;
			return false;
		}
	}
	//setAllBalanceFactor(root);
	return true;
}

void AVL::LLAdjust(TreeNode*& root)
{
	if (root == this->root) {
		TreeNode* newRoot = root->leftchild;
		root->leftchild = newRoot->rightchild;
		newRoot->rightchild = root;
		this->root = newRoot;
	}
	else {
		TreeNode* newRoot = root->leftchild, * rootParent; 
		getParent(this->root, root, rootParent);
		if (rootParent) {
			if (rootParent->leftchild == root) {
				root->leftchild = newRoot->rightchild;
				newRoot->rightchild = root;
				rootParent->leftchild = newRoot;
			}
			else if (rootParent->rightchild == root) {
				root->leftchild = newRoot->rightchild;
				newRoot->rightchild = root;
				rootParent->rightchild = newRoot;
			}
			else {
				cout << "I am at LLadjust(); RootParent is not the parent of root!" << endl;
				return;
			}
		}
		else {
			cout << "I cannot find my parent!" << endl;
		}
	}
}

void AVL::LRAdjust(TreeNode*& root) 
{
	if (root == this->root) {
		TreeNode* temp = root->leftchild, * newRoot = temp->rightchild;
		root->leftchild = temp->rightchild->rightchild;
		temp->rightchild = temp->rightchild->leftchild;
		newRoot->leftchild = temp;
		newRoot->rightchild = root;
		this->root = newRoot;
	}
	else {
		TreeNode* temp = root->leftchild, * newRoot = temp->rightchild, * rootParent;
		getParent(this->root, root, rootParent);
		if (rootParent) {
			if (rootParent->leftchild == root) {
				root->leftchild = temp->rightchild->rightchild;
				temp->rightchild = temp->rightchild->leftchild;
				newRoot->leftchild = temp;
				newRoot->rightchild = root;
				rootParent->leftchild = newRoot;
			}
			else if (rootParent->rightchild == root) {
				root->leftchild = temp->rightchild->rightchild;
				temp->rightchild = temp->rightchild->leftchild;
				newRoot->leftchild = temp;
				newRoot->rightchild = root;
				rootParent->rightchild = newRoot;
			}
			else {
				cout << "I am at LRadjust(); RootParent is not the parent of root!" << endl;
				return;
			}
		}
		else {
			cout << "I cannot find my parent." << endl;
		}
		
	}
	//setAllBalanceFactor(this->root);
}

void AVL::RRAdjust(TreeNode*& root) 
{
	if (root == this->root) {
		TreeNode* newRoot = root->rightchild;
		root->rightchild = newRoot->leftchild;
		newRoot->leftchild = root;
		this->root = newRoot;
	}
	else {
		TreeNode* newRoot = root->rightchild, * rootParent;
		getParent(this->root, root,rootParent);
		if (rootParent) {
			if (rootParent->leftchild == root) {
				root->rightchild = newRoot->leftchild;
				newRoot->leftchild = root;
				rootParent->leftchild = newRoot;
			}
			else if (rootParent->rightchild == root) {
				root->rightchild = newRoot->leftchild;
				newRoot->leftchild = root;
				rootParent->rightchild = newRoot;
			}
			else {
				cout << "I am at RRadjust(); RootParent is not the parent of root!" << endl;
				return;
			}
		}
		else {
			cout << "I cannot find my parent!" << endl;
		}
	}
}

void AVL::RLAdjust(TreeNode*& root) 
{
	if (root == this->root) {
		TreeNode* temp = root->rightchild, *newRoot = temp->leftchild;
		root->rightchild = temp->leftchild->leftchild;
		temp->leftchild = temp->leftchild->rightchild;
		newRoot->leftchild = root;
		newRoot->rightchild = temp;
		this->root = newRoot;
	}
	else {
		TreeNode* temp = root->rightchild, * newRoot = temp->leftchild, * rootParent;
		getParent(this->root, root, rootParent);
		if (rootParent) {
			if (rootParent->leftchild == root) {
				root->rightchild = temp->leftchild->leftchild;
				temp->leftchild = temp->leftchild->rightchild;
				newRoot->leftchild = root;
				newRoot->rightchild = temp;
				rootParent->leftchild = newRoot;
			}
			else if (rootParent->rightchild == root) {
				root->rightchild = temp->leftchild->leftchild;
				temp->leftchild = temp->leftchild->rightchild;
				newRoot->leftchild = root;
				newRoot->rightchild = temp;
				rootParent->rightchild = newRoot;
			}
			else {
				cout << "I am at RLadjust(); RootParent is not the parent of root!" << endl;
				return;
			}
		}
		else {
			cout << "I cannot find my parent!" << endl;
		}
		
	}
	//setAllBalanceFactor(this->root);

}

TreeNode* queue[10000];
void AVL::levelTraverse(TreeNode* root) 
{
	if (root) {
		int head = 0, rear = 0;
		queue[rear++] = root;
		while (head < rear && head < 10000 && rear < 10000)
		{
			if (queue[head] == nullptr) {
				head++;
				continue;
			}
			else { 
				queue[rear++] = queue[head]->leftchild;
				queue[rear++] = queue[head]->rightchild;
				queue[head++]->content.printInfo(); 
			}
		}
	}
	else {
		cout << "There is no tree here." << endl;
	}
	
}

void AVL::BiTreeToArray(TreeNode* T, Dataset A[], int i, int& count)
{
	if (T != NULL)
	{
		A[i] = T->content;
		if (i > count)
			count = i;
		BiTreeToArray(T->leftchild, A, 2 * i, count);
		BiTreeToArray(T->rightchild, A, 2 * i + 1, count);
	}
}

void AVL::LevelTraverse(TreeNode* T, Dataset B[], int num)
{
	int n, i, j, t, q, s, p, m = 0, k = 0;
	n = (int)((log(num) / log(2)) + 1);
	p = n;
	for (i = 0; i < n; i++)
	{
		k = pow(2, m) + k;
		t = pow(2, m);
		j = pow(2, p - 1) - 1;
		q = pow(2, p) - 1;
		s = q;
		for (j; j > 0; j--)
		{
			cout << " ";
		}
		for (t; t <= k; t++)
		{
			if (B[t].mainkey == 0)
			{
				cout << "*";
				for (q; q > 0; q--)
					cout << " ";
				q = s;
			}
			else {
				cout << B[t].mainkey;
				for (q; q > 0; q--)
					cout << " ";
				q = s;
			}
		}
		m++;
		p--;
		j = n - i - 1;
		cout << endl;
	}
}


int main()
{
	ifstream fi;
	AVL testTree[] = { AVL(), AVL(),AVL() };
	int i = 0, n[] = { 10,100, 10000 };
	Dataset item;
	Dataset D1[105], D2[1005];
	bool taller = false;
	for (int j = 0; j < 3; j++) {
		fi.open("E:\\C++\\DataSet\\10000.txt");
		while (!fi.eof() && i < n[j]) {
			fi >> item.mainkey >> item.file_No >> item.division >> item.CNWord >> item.int_num >> item.double_num >> item.EnglishWord;
			testTree[j].Insert(item, taller);
			i++;
		}
		fi.close();
		int iii = 1, length = 1;
		/*testTree[j].BiTreeToArray(testTree->getRoot(), D1, iii, length);
		testTree[j].LevelTraverse(testTree->getRoot(), D1, length);*/
		//testTree[j].levelTraverse(testTree[j].getRoot());
	}
	
	
	srand((unsigned)time(NULL));
	int t = 0, p = 0;
	int count = 0, yes_count = 0, no_count = 0;
	for (int j = 0; j < 3; j++) {
		t = 0, p = 0;
		count = 0, yes_count = 0, no_count = 0;
		while (t < 100) {
			int i = rand() % 10000;
			//cout << i<<" ";
			bool res = testTree[j].Find(i, count);
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



