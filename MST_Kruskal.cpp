#include <queue>
#include <iostream>

using namespace std;

struct EdgeNode {
	int v1;
	int v2;
	int weight;
	EdgeNode* next;
	
	EdgeNode(int v1, int v2, int weight, EdgeNode* next) {
		this->v1 = v1;
		this->v2 = v2;
		this->weight = weight;
		this->next = next;
	}
};

class Graph {
private:
	int v, e;
	int** weight;
	EdgeNode* head;
	bool* visited;
public:
	Graph(int vertex) {
		v = vertex;
		weight = new int* [vertex];
		visited = new bool [vertex];
		for (int i = 0; i < vertex; i++) {
			weight[i] = new int[vertex];
			visited[i] = false;
		}
		for (int i = 0; i < vertex; i++) {
			for (int j = 0; j < vertex; j++) {
				weight[i][j] = INT16_MAX;
			}
		}
		head = nullptr;
	}
	Graph(int vertex, int edge) {
		v = vertex;
		e = edge;
		head = nullptr;
		weight = new int* [vertex];
		visited = new bool[vertex];
		for (int i = 0; i < vertex; i++) {
			weight[i] = new int[vertex];
			visited[i] = false;
		}
		for (int i = 0; i < vertex; i++) {
			for (int j = 0; j < vertex; j++) {
				weight[i][j] = INT16_MAX;
			}
		}
	}
	Graph(const Graph& g) {
		for (int i = 0; i < g.v; i++) {
			for (int j = 0; j < g.v; j++) {
				weight[i][j] = g.weight[i][j];
			}
			visited[i] = g.visited[i];
		}
		head->next = g.head->next;
		head->v1 = g.head->v1;
		head->v2 = g.head->v2;
		head->weight = g.head->weight;
	}
	~Graph(){
		for (int i = 0; i < v; i++) {
			delete[] weight[i];
		}
		delete[] weight;
		delete[] visited;
		delete head;
	}
	bool setWeight(int v1, int v2, int weights) {
		if (v1 >= v || v2 >= v) {
			return false;
		}
		weight[v1][v2] = weights;
		weight[v2][v1] = weights;
		return true;
	}
	int getWeight(int v1, int v2) {
		if (v1 >= v || v2 >= v) {
			return -1;
		}
		return weight[v1][v2];
	}
	int getVertex() {
		return v;
	}
	int isVisited(int i) {
		if (i >= v) {
			return -1;
		}
		else {
			return visited[i];
		}
	}
	bool Visit(int i) {
		if (i >= v) {
			return false;
		}
		visited[i] = true;
		return true;
	}
	void setEdge(int v1, int v2, int weight) {
		if (head == nullptr) {
			head = new EdgeNode(-1, -1, 0, new EdgeNode(v1, v2, weight, nullptr));
		}
		else {
			EdgeNode* curr = head -> next;
			while (curr->next && curr->next->weight <= weight) {
				curr = curr->next;
			}
			if (curr->next == nullptr) {
				if (curr->weight > weight) {
					EdgeNode* temp = head;
					while (temp && temp->next != curr) {
						temp = temp->next;
					}
					temp->next = new EdgeNode(v1, v2, weight, curr);
				}
				else {
					curr->next = new EdgeNode(v1, v2, weight, nullptr);
				}
			}
			else if (curr->next->weight > weight) {
				curr->next = new EdgeNode(v1, v2, weight, curr->next);
			}
		}
	}
	EdgeNode* getEdge() {
		return head;
	}
};

struct Edge {
	int v1, v2, weight;
	Edge(int i, int j, int w) {
		v1 = i;
		v2 = j;
		weight = w;
	}
};


struct comp {
	comp() {}
	~comp() {}
	bool operator()(const Edge a, const Edge b) {
		return a.weight > b.weight;//最小堆，从小到大排序
	}
};

class Union {
private:
	int* pre;
	int len;
public:
	Union(int len) {
		pre = new int[len];
		for (int i = 0; i < len; i++) {
			pre[i] = i;
		}
		this->len = len;
	}
	int find(int i) {
		if (pre[i] == i) return i;
		else return pre[i] = find(pre[i]);
	}
	void merge(int i, int j) {
		int parentI = find(i), parentJ = find(j);
		if (parentI != parentJ) {
			pre[parentI] = parentJ;
		}
	}
	void setPre(int loc, int parent) {
		if (loc < len) {
			pre[loc] = parent;
		}
	}
};

int prim(Graph& g) {
	priority_queue<Edge, vector<Edge>, comp> smallest_edge;
	int i = 0;
	int mst_count = 0;
	g.Visit(0);
	while (i == 0 || !smallest_edge.empty()) {
		int min = INT16_MAX;
		for (int j = 0; j < g.getVertex(); j++) {
			if (!g.isVisited(j) && g.getWeight(i, j) < min) {
				Edge edge = Edge(i, j, g.getWeight(i, j));
				smallest_edge.push(edge);
			}
		}
		Edge edge = Edge(smallest_edge.top());
		if (g.isVisited(edge.v1) != 0 && g.isVisited(edge.v2) != 0) {
			smallest_edge.pop();
			continue;
		}
		mst_count += edge.weight;
		i = edge.v2;
		g.Visit(i);
		smallest_edge.pop();
	}
	return mst_count;
}

int Kruskal(Graph& g, Union& u) {
	EdgeNode* curr = g.getEdge()-> next;
	int mst_count = 0;
	while (curr) {
		int parent1 = u.find(curr->v1), parent2 = u.find(curr->v2);
		if (parent1 != parent2) {
			u.merge(curr->v1, curr->v2);
			// u.setPre(curr->v2, parent1);
			mst_count += curr->weight;
		}
		curr = curr->next;
	}
	return mst_count;
}

int main()
{
	int vertex, edge;
	cin >> vertex >> edge;
	Graph g = Graph(vertex, edge);
	Union u = Union(vertex);
	for (int i = 0; i < edge; i++) {
		int v1, v2, weight;
		cin >> v1 >> v2 >> weight;
		g.setWeight(v1 - 1, v2 - 1, weight);
		g.setEdge(v1 - 1, v2 - 1, weight);
	}
	int mst_count1 = 0, mst_count2 = 0;;
	try {
		mst_count1 = prim(g);
		mst_count2 = Kruskal(g, u);
	}
	catch (exception e) {
		e.what();
	}
	
	cout << "prim: " << mst_count1 << endl;
	cout << "kruskal: " << mst_count2 << endl;
	return 0;
}
