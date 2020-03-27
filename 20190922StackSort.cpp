//#include <iostream>
//#include <ctime>
//#include <fstream>
//using namespace std;
//
//struct Dataset
//{
//	long long mainkey;
//	int file_No;
//	char division;
//	string province;
//	int int_number;
//	double double_number;
//	string word;
//
//	Dataset()
//	{
//		mainkey = 0;
//		file_No = 0;
//		division = 0;
//		int_number = 0;
//		double_number = 0;
//	}
//	void printInfo()
//	{
//		cout << mainkey << '\t' << file_No << '\t' << division << '\t' << province << '\t';
//		cout << int_number << '\t' << double_number << '\t' << word << endl;
//	}
//};
//
//template<typename T>
//class Stack 
//{
//private:
//	T* stack;
//	int MAXSIZE;
//	int top;
//public:
//	Stack(int maxsize) {
//		MAXSIZE = maxsize;
//		stack = new T[MAXSIZE + 1];
//		top = 0;
//	}
//	bool isEmpty() {
//		if (top == 0)
//			return true;
//		else
//			return false;
//	}
//	bool isFull() {
//		if (top == MAXSIZE)
//			return true;
//		else
//			return false;
//	}
//	void push(T);
//	T pop();
//	T gettop() {
//		if (isEmpty())
//			cout << "The stack is empty!" << endl;
//		else
//			return stack[top - 1];
//	}
//};
//template<>
//Dataset Stack<Dataset>::gettop() {
//	if (isEmpty())
//		cout << "The stack is empty!" << endl;
//	else
//		return stack[top - 1];
//}
//
//template <typename T>
//void Stack<T>::push(T item) 
//{
//	if (!isFull())
//		stack[top++] = item;
//	else
//		cout << "The stack is full!" << endl;
//}
//
//template <typename T>
//T Stack<T>::pop()
//{
//	if (!isEmpty())
//		return stack[--top];
//	else
//		cout << "The stack is empty!" << endl;
//}
//
//
//
//template <typename T>
//T* StackSort2(T* sorting, int len) 
//{
//	Stack<T> first(len + 1), second(len + 1);
//	int k = 0, count = 0, t = 0;
//	T* sorted = new T[len];
//	while (k <= len - 1) 
//	{
//		first.push(sorting[k++]);
//	}
//	T temp;
//	temp = first.pop();
//	second.push(temp);
//	bool second_isEmpty = false;
//	while (!first.isEmpty()) 
//	{
//		temp = first.pop();
//		if (second.gettop() >= temp) {
//			second.push(temp);
//		}
//		else 
//		{
//			while (temp > second.gettop()) 
//			{
//				first.push(second.pop());
//				count++;
//				if (second.isEmpty()) 
//				{
//					second_isEmpty = true;
//					break;
//				}
//			}
//			second.push(temp);
//			while (t < count) 
//			{
//				second.push(first.pop());
//				t++;
//			}
//			count = 0;
//		}
//	}
//	k = 0;
//	while (!second.isEmpty()) 
//	{
//		sorted[k++] = second.pop();
//	}
//	return sorted;
//}
//
//template<> 
//Dataset* StackSort2<Dataset>(Dataset* sorting, int len) 
//{
//	Stack<Dataset> first(len + 1), second(len + 1);
//	int k = 0, count = 0, t = 0;
//	Dataset* sorted = new Dataset[len];
//	while (k <= len - 1)
//	{
//		first.push(sorting[k++]);
//	}
//	Dataset temp;
//	temp = first.pop();
//	second.push(temp);
//	bool second_isEmpty = false;
//	while (!first.isEmpty())
//	{
//		temp = first.pop();
//		if (second.gettop().int_number >= temp.int_number) {
//			second.push(temp);
//		}
//		else
//		{
//			while (temp.int_number > second.gettop().int_number)
//			{
//				first.push(second.pop());
//				count++;
//				if (second.isEmpty())
//				{
//					second_isEmpty = true;
//					break;
//				}
//			}
//			second.push(temp);
//			while (t < count)
//			{
//				second.push(first.pop());
//				t++;
//			}
//			count = 0;
//		}
//	}
//	k = 0;
//	while (!second.isEmpty())
//	{
//		sorted[k++] = second.pop();
//	}
//	return sorted;
//}
//
//int main()
//{
//	int* a = new int[10];
//	srand((unsigned)int(time));
//	Dataset* test = new Dataset[10];
//	Dataset* sorted = new Dataset[10];
//	ifstream infile("E:\\C++\\DataSet\\4.txt");
//	for (int i = 0; i < 10; i++) 
//	{
//		infile >> test[i].mainkey >> test[i].file_No >> test[i].division >> test[i].province >> test[i].int_number >> test[i].double_number >> test[i].word;
//		test[i].printInfo();
//	}
//	cout << endl;
//	sorted = StackSort2<Dataset>(test, 10);
//	for (int i = 0; i < 10; i++)
//	{
//		sorted[i].printInfo();
//	}
//}
//
