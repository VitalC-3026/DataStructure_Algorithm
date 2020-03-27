#include <iostream>


using namespace std;

class Node {
	int status;
	int original;
	Node* next;
	Node() {
		status = -1;
		original = -1;
		next = nullptr;

	}
	Node(int i, Node* n) {
		status = i;
		original = i;
		next = n;
	}
	friend class CircularList;
	
};

class CircularList 
{
private:
	Node* head;
	int number_Node;
	int kill_Node;

public:
	CircularList(int number, int kill){
		this->kill_Node = kill;
		this->number_Node = number;
		int k = 1;
		head = new Node(-1, nullptr);
		head->next = new Node(k++, nullptr);
		Node* current = head->next;
		while (k <= number_Node - 1) {
			current->next = new Node(k++, nullptr);
			current = current->next;
		}
		if (k == number_Node) 
		{
			current->next = new Node(k, head->next);
		}
	}
	int getNumber_Node() { return number_Node; }
	int getKill_Node() { return kill_Node; }
	void delete_Node();
	void reset_number(Node* tmp);
	void printInfo();
};

void CircularList::delete_Node()
{
	Node* tmp, * current = head->next;
	while (current->next->status < kill_Node && current->status < current->next->status) 
	{
		current = current->next;
	}
	if (current->next->status == kill_Node) 
	{
		tmp = current->next;
		current->next = current->next->next;
		head = current->next;
		number_Node--;
		reset_number(tmp);
		//printInfo();
	}
	else if (current->next->status < current->status) 
	{
		cout << "Game over!" << endl;
		//printInfo();
		return;
	}
}

void CircularList::reset_number(Node* tmp) 
{
	Node* current = tmp->next;
	int k = 1;
	current->status = k++;
	current = current->next;
	while (current != tmp->next) 
	{
		current->status = k++;
		current = current->next;
	}
}

void CircularList::printInfo() 
{
	Node* current = head->next;
	cout << "kill:" << kill_Node << "total:" << number_Node << endl;
	while (current->next != head->next) 
	{
		cout << "original:" << current->original << "\tpresent:" << current->status << endl;
		current = current->next;
	}
	cout << "original:" << current->original << "\tpresent:" << current->status << endl;
}

int main()
{
	CircularList l(9,3);
	int kill = l.getKill_Node();
	int total = l.getNumber_Node();
	while (total >= kill) 
	{
		l.delete_Node();
		total--;
		l.printInfo();
	}
}

