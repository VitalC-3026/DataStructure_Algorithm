//#include <iostream>
//#include <cmath>
//
//using namespace std;
//
//int MAXSIZE = 256;
//
//
//class TreeNode 
//{
//	int content;
//	TreeNode* left;
//	TreeNode* right;
//
//public:
//	TreeNode(int content) 
//	{
//		this->content = content;
//		left = nullptr;
//		right = nullptr;
//	}
//	TreeNode() {
//		content = -1;
//		left = nullptr;
//		right = nullptr;
//	}
//	int getContent() {
//		return content;
//	}
//	friend class BNTree;
//};
//
//class StackNode 
//{
//private:
//	int content;
//	StackNode* next;
//public:
//	StackNode(int content) 
//	{
//		this->content = content;
//		next = nullptr;
//	}
//	StackNode() 
//	{
//		content = -1;
//		next = nullptr;
//	}
//	friend class Queue;
//};
//
//class Stack 
//{
//private:
//	int top;
//	TreeNode** stack;
//	int MAXSIZE;
//public:
//	Stack(int MAXSIZE) 
//	{
//		stack = new TreeNode * [MAXSIZE + 1];
//		top = -1;
//		this->MAXSIZE = MAXSIZE;
//	}
//	bool isEmpty() 
//	{
//		if (top == -1) return true;
//		else return false;
//	}
//	bool isFull() 
//	{
//		if (top == MAXSIZE - 1) return true;
//		else return false;
//	}
//	void push(TreeNode*);
//	TreeNode* pop(); 
//	TreeNode* GetTop();
//};
//
//void Stack::push(TreeNode* item) 
//{
//	if (isFull()) 
//	{
//		return;
//	}
//	else 
//	{
//		stack[++top] = item;
//	}
//}
//
//TreeNode* Stack::pop() 
//{
//	if (isEmpty()) 
//	{
//		return nullptr;
//	}
//	else 
//	{
//		return stack[top--];
//	}
//}
//
//TreeNode* Stack::GetTop() 
//{
//	if (isEmpty())
//	{
//		return nullptr;
//	}
//	else
//	{
//		return stack[top];
//	}
//}
//
//class Queue {
//private:
//	int first;
//	int rear;
//	TreeNode** queue;
//public:
//	Queue() 
//	{
//		queue = new TreeNode*[MAXSIZE];
//		first = rear = 0;
//	}
//	/*Queue(int len) 
//	{
//		try{
//			queue = new int[len + 1];
//			first = rear = 0;
//		}
//		catch (exception e) 
//		{
//			queue = new int[MAXSIZE];
//			cout << "队列长度超限,已按照最大规格生成" << endl;
//		}
//		
//	}*/
//	int out() 
//	{
//		if (isEmpty()) 
//		{
//			return -1;
//		}
//		int num = -1;
//		if (queue[(first) % MAXSIZE] != nullptr) 
//		{
//			num = queue[first % MAXSIZE]->getContent();
//		}
//		else 
//		{
//			num = -1;
//		}
//		first++;
//		return num;
//	}
//	void in(TreeNode* item) 
//	{
//		if(isFull())
//		{
//			return;
//		}
//		if (item == nullptr) 
//		{
//			return;
//		}
//		queue[rear%MAXSIZE] = item;
//		rear++;
//	}
//	bool isEmpty() 
//	{
//		if (first == rear) 
//		{
//			return true;
//		}
//		return false;
//	}
//	bool isFull() 
//	{
//		if (rear - first == MAXSIZE) 
//		{
//			return true;
//		}
//		return false;
//	}
//	TreeNode* getFirst() 
//	{
//		return queue[first];
//	}
//};
//
//class BNTree 
//{
//	int height;
//	TreeNode* root;
//	TreeNode** tree; 
//public:
//	BNTree() 
//	{
//		root = nullptr;
//		tree = nullptr;
//		height = 0;
//	}
//	BNTree(int* a, int len) 
//	{
//		root = nullptr;
//		tree = new TreeNode * [len + 1];
//		height = 0;
//	}
//	bool CreateATree(int* a, int len);
//	void preorder(TreeNode*);
//	void inorder(TreeNode*);
//	void inorder_non(TreeNode*);
//	void NonInorder(TreeNode*);
//	void postorder(TreeNode*);
//	void levelorder(TreeNode*);
//	int getHeight(TreeNode*);
//	int Height(TreeNode* root) 
//	{
//		height = getHeight(root) + 1;
//		return height;
//	}
//	TreeNode* getRoot() 
//	{
//		return root;
//	}
//
//};
//
//bool BNTree::CreateATree(int* a, int len)
//{
//	if (a == nullptr || a[0] == -1) //a[0]无内容，不知道它是什么内容
//	{
//		cout << "The tree is empty!" << endl;
//		return false;
//	}
//	int t = 1, level = 0;
//	root = new TreeNode(a[0]);
//	tree[0] = root;
//	while (t < len)
//	{
//		if (a[t] == -1) //a[0]无内容，不知道它是什么内容
//		{
//			t++;
//			continue;
//		}
//		if (t % 2 == 0)
//		{
//			if (a[(t - 1) / 2] != -1)
//			{
//				tree[(t - 1) / 2]->right = new TreeNode(a[t]);
//				tree[t] = tree[(t - 1) / 2]->right;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		else
//		{
//			if (a[t / 2] != -1)
//			{
//				tree[t / 2]->left = new TreeNode(a[t]);
//				tree[t] = tree[t / 2]->left;
//			}
//			else 
//			{
//				return false;
//			}
//		}
//		t++;
//	}
//	return true;
//}
//
//void BNTree::preorder(TreeNode* visit) 
//{
//	if (visit == nullptr) { return; }
//	cout << visit->content << endl;
//	preorder(visit->left);
//	preorder(visit->right);
//}
//
//void BNTree::inorder(TreeNode* visit)
//{
//	if (visit == nullptr) { return; }
//	inorder(visit->left);
//	cout << visit->content << endl;
//	inorder(visit->right);
//}
//
//void BNTree::postorder(TreeNode* visit)
//{
//	if (visit == nullptr) { return; }
//	postorder(visit->left);
//	postorder(visit->right);
//	cout << visit->content << endl;
//}
//
//void BNTree::inorder_non(TreeNode* root) 
//{
//	Stack s(Height(root));
//	if (height == 0) { return;  }
//	TreeNode* curr = root; 
//	TreeNode* temp = nullptr;
//	bool flag = false;
//	//!s.isEmpty() || curr == root || curr != nullptr
//	while (true) 
//	{
//		//cout << curr->content << " ";
//		s.push(curr);
//		if (curr->left != nullptr) 
//		{
//			curr = curr->left;
//		}
//		else 
//		{
//			if (curr->right != nullptr) 
//			{
//				cout << s.pop()->content << " ";
//				curr = curr->right;
//			}
//			else 
//			{
//				cout << s.pop()->content << " ";
//				while (nullptr != s.GetTop() && s.GetTop()->right == nullptr) 
//				{
//					cout << s.pop()->content << " ";
//				}
//				if (nullptr == s.GetTop()) 
//				{
//					cout << endl;
//					return;
//				}
//				else 
//				{
//					temp = s.pop();
//					cout << temp->getContent() << " ";
//					curr = temp->right;
//				}
//				
//			}
//		}
//
//	}
//}
//
//void BNTree::NonInorder(TreeNode* root) 
//{
//	TreeNode* curr = root;
//	Stack s(Height(root));
//	while (curr || !s.isEmpty()) 
//	{
//		while (curr)
//		{
//			s.push(curr);
//			curr = curr->left;
//		}
//		if (!s.isEmpty()) 
//		{
//			curr = s.pop();
//			cout << curr->content;
//			curr = curr->right;
//		}
//	}
//}
//
//void BNTree::levelorder(TreeNode* root) 
//{
//	Queue traverse;
//	TreeNode* curr = root;
//	traverse.in(root);
//	while (!traverse.isEmpty()) 
//	{
//		traverse.in(curr->left);
//		traverse.in(curr->right);
//		int num = traverse.out();
//		if (num != -1) 
//		{
//			cout << num << '\t';
//		}
//		curr = traverse.getFirst();
//	}
//}
//
//int BNTree::getHeight(TreeNode* root) 
//{
//	int max(int a, int b);
//	int left_height = 0, right_height = 0;
//	if (root->left == nullptr && root->right == nullptr) 
//	{
//		return 0;
//	}
//	if (root->left == nullptr) 
//	{ 
//		left_height = 0;
//	}
//	else 
//	{
//		left_height = getHeight(root->left);
//	}
//	if (root->right == nullptr) 
//	{
//		right_height = 0;
//	}
//	else 
//	{
//		right_height = getHeight(root->right);
//	}
//	//height = max(left_height, right_height) + 1;
//	return max(left_height, right_height) + 1;
//}
//
//int main()
//{
//	int a[] = {0,1,2,3,4,5,6,-1,-1,7,-1,-1,8,9,10};
//	BNTree Test(a,15);
//	Test.CreateATree(a, 15);
//	TreeNode* root = Test.getRoot();
//	cout << "递归的先序遍历" << endl;
//	Test.preorder(root);
//	cout << "递归的中序遍历" << endl;
//	Test.inorder(root);
//	cout << "递归的后序遍历" << endl;
//	Test.postorder(root);
//	cout << "非递归的中序遍历" << endl;
//	Test.inorder_non(root);
//	Test.NonInorder(root);
//	cout << "层序遍历" << endl;
//	Test.levelorder(root);
//}
//
//int max(int a, int b) 
//{
//	return a > b ? a : b;
//}