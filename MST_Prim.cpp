#include <queue>
#include <iostream>

using namespace std;

class Graph {
private:
	int v, e;
	int** weight;
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
	}
	Graph(int vertex, int edge) {
		v = vertex;
		e = edge;
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
	}
	~Graph(){
		for (int i = 0; i < v; i++) {
			delete[] weight[i];
		}
		delete[] weight;
		delete[] visited;
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
};
struct Edge {
	int v1;
	int v2;
	int weight;
	Edge(int v1, int v2, int weight) {
		this->v1 = v1;
		this->v2 = v2;
		this->weight = weight;
	}
};

struct comp {
	comp() {}
	~comp() {}
	bool operator() (Edge e1, Edge e2) {
		return e1.weight > e2.weight;
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



int main()
{
	int vertex, edge;
	cin >> vertex >> edge;
	Graph g = Graph(vertex, edge);
	for (int i = 0; i < edge; i++) {
		int v1, v2, weight;
		cin >> v1 >> v2 >> weight;
		g.setWeight(v1 - 1, v2 - 1, weight);
	}
	int mst_count = 0;
	try {
		mst_count = prim(g);
	}
	catch (exception e) {
		e.what();
	}
	
	cout << mst_count;
	return 0;
}
