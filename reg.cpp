//#include<iostream>
//using namespace std;
//
//int MAX = (int)(pow(2, 16)) - 1;
//enum sign {infinite = 1};
//enum loc { start = 1, stop = 2 };
//enum visit { unvisited, visited };
//class Edge;
//struct node {
//	int next_vertex;
//	char edge_content;
//	node* next;
//	node(int i, char c) {
//		next_vertex = i;
//		edge_content = c;
//		next = nullptr;
//	}
//};
//class Vertex {
//	char content;
//	int inf = 0;
//	char inf_content = 0;
//	int s_e = 0;
//	int index = -1;
//	Edge** edge;
//	node* next;
//public:
//	Vertex() {
//		next = nullptr;
//		edge = nullptr;
//	}
//	Vertex(char content, int sign, int loc) {
//		this->content = content;
//		this->inf = sign;
//		this->s_e = loc;
//		next = nullptr;
//		edge = nullptr;
//	}
//	Vertex(char content) {
//		this->content = content;
//		edge = nullptr;
//		next = nullptr;
//	}
//	void setIndex(int i) {
//		index = i;
//	}
//	void setInfinite(char content) {
//		inf = infinite;
//		inf_content = content;
//	}
//	void setStart() {
//		s_e = start;
//	}
//	void setEnd() {
//		s_e = stop;
//	}
//	//void setNewVertex(Edge e, char content, int s_e, int inf, int index);
//	friend class Graph;
//};
//class Edge {
//	int in;
//	int out;
//	char content;
//	
//public:
//	Edge() {
//		in = 0; 
//		out = 0;
//		content = 0;
//	}
//	Edge(int i, int o, char c) {
//		in = i;
//		out = o;
//		content = c;
//	}
//	friend class Graph;
//	friend class Vertex;
//};
//class Graph {
//private:
//	int vertex;
//	int edge;
//	int* E_mark;
//	int* V_mark;
//	Vertex** adjacency_list;
//
//public:
//	Graph(int numV) {
//		vertex = numV;
//		edge = 0;
//		E_mark = new int[numV];
//		V_mark = new int[numV];
//		adjacency_list = new Vertex* [numV];
//		for (int i = 0; i < numV; i++) {
//			E_mark[i] = unvisited;
//			V_mark[i] = unvisited;
//			adjacency_list[i] = nullptr;
//		}
//	}
//	~Graph() {
//		delete[] E_mark;
//		delete[] V_mark;
//		delete[] adjacency_list;
//	}
//	int v() {
//		return vertex;
//	}
//	int e() {
//		return edge;
//	}
//	void add_vertex(char content, int s_e, int inf, int inf_content);
//	void Add_edge(int i, int j, char content);
//	void add_edge(Graph&, int i, int j, char content);
//	int is_edge(int i, int j);
//	bool IsStringAccepted(char* str, int len);
//	int Traverse(char* str, int len, int start);
//
//};
//
//void Graph::add_vertex(char content, int s_e, int inf, int i_content) {
//	int i = 0;
//	while (i < vertex) {
//		if (adjacency_list[i] == nullptr) break;
//		i++;
//	}
//	if (i >= vertex) {
//		return;
//	}
//	else {
//		adjacency_list[i] = new Vertex(content);
//		if (s_e == 1) {
//			adjacency_list[i]->setStart();
//		}
//		else if (s_e == 2) {
//			adjacency_list[i]->setEnd();
//		}
//		if (inf == 1) {
//			adjacency_list[i]->setInfinite(i_content);
//		}
//		adjacency_list[i]->setIndex(i);
//	}
//}
////更理想的数据结构应该是vertex有一个node的节点，存放vertex指向的下一个节点以及它的边的权重，以此串成链表
//void Graph::Add_edge(int v, int w, char content) {
//	add_edge(*this, v, w, content);
//}
//void Graph::add_edge(Graph& g, int v, int w, char content) {
//	if (v < vertex && w < vertex) {
//		if (adjacency_list[v] != nullptr) {
//			node* curr_node = g.adjacency_list[v]->next;
//			while (curr_node != nullptr && curr_node->next != nullptr && curr_node->next_vertex != w) {
//				curr_node = curr_node->next;
//			}
//			if (curr_node == nullptr) {
//				curr_node = new node(w, content);
//				g.adjacency_list[v]->next = curr_node;
//				return;
//			}
//			else if (curr_node != nullptr && curr_node->next == nullptr){
//				curr_node->next = new node(w, content);
//				g.adjacency_list[v]->next = curr_node;
//				return;
//			}
//			else if(curr_node != nullptr && curr_node->next_vertex == w){
//				cout << "Duplicate." << endl;
//				return;
//			}
//			else {
//				cout << "The edge cannot be added." << endl;
//			}
//		}
//	}
//	else {
//		cout << "The edge doesn't exist." << endl;
//	}
//
//}
//
////int Graph::is_edge(int v, int w) {
////	if (v < vertex && w < vertex) {
////		Vertex* curr = adjacency_list[v];
////		while (curr != nullptr && curr->index != w) {
////			curr = curr->next;
////		}
////		if (curr == nullptr) {
////			cout << "The edge doesn't exist." << endl;
////			return -1;
////		}
////		else if (curr->index == w) {
////			cout << "The edge exists." << endl;
////			return (int)(curr->content);
////		}
////	}
////	else {
////		return -1;
////	}
////}
//
//bool Graph::IsStringAccepted(char* str, int len) {
//	int res = -1;
//	if (str[0] == '1') {
//		res = Traverse(str, len, 1);
//	}
//	else {
//		res = Traverse(str, len, 0);
//	}
//	if (res == 0) {
//		return true;
//	}
//	return false;
//}
//
//int Graph::Traverse(char* str, int len, int start) {
//	int status = start;
//	Vertex* curr = adjacency_list[status];
//	node* curr_node;
//	int t = 1;
//	while (t < len) {
//		curr_node = curr->next;
//		while (curr != nullptr && curr_node != nullptr && curr_node->next != nullptr && curr_node->edge_content != str[t]) {
//			curr_node = curr_node->next;
//		}
//		if (curr == nullptr) {
//			return -1;
//		}
//		if (curr_node == nullptr) {
//			return -1;
//		}
//		if (curr_node->edge_content == str[t]) {
//			curr = adjacency_list[curr_node->next_vertex];
//			status = curr_node->next_vertex;
//		}
//		t++;
//	}
//	return status;
//}
//
//
//void createArule(Graph& g) {
//	g.add_vertex('0', 2, 1, 0);
//	g.add_vertex('1', 1, 0, -1);
//	g.add_vertex('2', 0, 0, -1);
//	g.add_vertex('3', 0, 0, -1);
//	g.add_vertex('4', 0, 1, -1);
//	g.Add_edge(0, 0, '0');
//	g.Add_edge(0, 1, '1');
//	g.Add_edge(1, 2, '0');
//	g.Add_edge(1, 3, '1');
//	g.Add_edge(2, 4, '0');
//	g.Add_edge(2, 0, '1');
//	g.Add_edge(3, 1, '0');
//	g.Add_edge(3, 2, '1');
//	g.Add_edge(4, 3, '0');
//	g.Add_edge(4, 4, '1');
//}
//
//int binaryTodecimal(char* s, int len) {
//	int k = len - 1;
//	int res = 0;
//	while (k >= 0) {
//		res += ((int)s[k--] - 48) * pow(2, len - k - 1);
//	}
//	return res;
//}
//
//
//int main() {
//	Graph g = Graph(5);
//	createArule(g);
//	char str1[] = { "10110" };
//	char str2[] = { "1111" };
//	char* str = new char[80];
//	int len1 = strlen(str1);
//	int len2 = strlen(str2);
//	cout << "预检测序列为:" << endl;
//	cout << "10110" << "十进制:" << binaryTodecimal(str1, len1) << endl;
//	cout << "1111" << "十进制:" << binaryTodecimal(str2, len2) << endl;
//	cout << "请输入你想检测的01序列:" << endl;
//	cin.getline(str,80);
//	int len = strlen(str);
//	cout << "十进制:" << binaryTodecimal(str, len) << endl;
//	bool res1, res2, res;
//	res1 = g.IsStringAccepted(str1, len1);
//	res2 = g.IsStringAccepted(str2, len2);
//	res = g.IsStringAccepted(str, len);
//	cout << boolalpha << res1 << " " << res2 << endl;
//	cout << boolalpha << res << endl;
//	return 0;
//}
//
