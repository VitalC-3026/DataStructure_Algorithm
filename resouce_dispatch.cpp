#include <iostream>
#include <cmath>
using namespace std;
int MAX = pow(2, 16) - 1;
enum mark{unvisited, visited} m;
class Tag {
private:
	int visit;
	int weight;
	int start_vertex;
	int end_vertex;
	Tag* path1;
	Tag* path2;
public:
	Tag() {
		visit = unvisited;
		weight = INTMAX_MAX;
		start_vertex = 0;
		end_vertex = 0;
		path1 = nullptr;
		path2 = nullptr;
	}
	Tag(int start, int end, int weight) {
		visit = unvisited;
		start_vertex = start;
		end_vertex = end;
		path1 = nullptr;
		path2 = nullptr;
	}
	friend class Graph;
};
class Graph {
private:
	int vertex;
	int edge;
	int* E_mark;
	int* V_mark;
	int** matrix;
	Tag** adjacency_list;
public:
	Graph(int numV) {
		vertex = numV;
		edge = 0;
		E_mark = new int[numV];
		V_mark = new int[numV];
		matrix = new int* [numV + 1];
		adjacency_list = new Tag * [numV];
		for (int i = 0; i < numV; i++) {
			E_mark[i] = unvisited;
			V_mark[i] = unvisited;
			matrix[i] = new int[numV + 1];
		}
		matrix[numV] = new int[numV + 1];
		for (int i = 0; i < numV; i++) {
			for (int j = 0; j < numV; j++) {
				matrix[i][j] = MAX;
			}
		}
	}
	~Graph() {
		/*delete[] E_mark;
		delete[] V_mark;
		for (int i = 0; i < vertex; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		delete[] adjacency_list;*/
	}
	int v() {
		return vertex;
	}
	int e() {
		return edge;
	}
	void creatAgraph(int** matrix, int num);
	void add_edge(int i, int j, int weight);
	void del_edge(int i, int j);
	int first(int i);
	int next(int i, int j);
	int is_edge(int i, int j);
	int cost(int v, int w) {
		return matrix[v][w];
	}
	int getMaxTime(int i);
	void print() {
		for (int i = 0; i < vertex; i++) {
			for (int j = 0; j < vertex; j++) {
				cout << matrix[i][j] << '\t';
			}
			cout << endl;
		}
	}
	//friend void singlesource_shortest_path(Graph g);
	void all_pairs_shortest_path();

};

void Graph::creatAgraph(int** m, int num) {
	if (num != vertex) {
		cout << "Uncompatible size!" << endl;
		return;
	}
	if (m != nullptr) {
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				this->matrix[i][j] = m[i][j];
			}
		}
	}
}

void Graph::add_edge(int v, int w, int weight) {
	if (v < vertex && w < vertex) {
		matrix[v][w] = weight;
	}
	else {
		cout << "The edge doesn't exist." << endl;
	}
	
}

void Graph::del_edge(int v, int w) {
	if (v < vertex && w < vertex) {
		matrix[v][w];
	}
	else {
		cout << "The edge doesn't exist." << endl;
	}
}

int Graph::is_edge(int v, int w) {
	if (v < vertex && w < vertex) {
		return matrix[v][w];
	}
	else {
		return -1;
	}
}

int Graph::first(int v) {
	if (v < vertex) {
		for (int j = 0; j < vertex; j++) {
			if (matrix[v][j] != MAX) {
				return j;
			}
		}
		return this->v();
	}
	return this->v();
}

int Graph::next(int v, int w) {
	for (int i = w + 1; i < vertex; i++) {
		if (matrix[v][i] != MAX) {
			return i;
		}
	}
	return this->v();

}

int Graph::getMaxTime(int i) {
	int maxtime = 0;
	for (int j = 0; j < v(); j++) {
		if (matrix[i][j] > maxtime && j != i) {
			maxtime = matrix[i][j];
		}
	}
	return maxtime;
}

//void singlesource_shortest_path(Graph g) {
//	int* dist = new int[g.v()];
//	int* max = new int[g.v()];
//	for (int i = 0; i < g.v(); i++) {
//		max[i] = 0;
//	}
//	//int min_content = UINTMAX_MAX, min_index = 0;
//	int max_content, min_index, min_content = MAX;
//	for(int t = 0;t < g.v(); t++){
//		//dist[t] = 0;
//		min_index = t;
//		min_content = MAX;
//		/*for (int i = 1; i < g.v(); i++) {
//			for (int j = g.first(min_index); j < g.v(); j = g.next(t, j)) {
//				if (dist[j] > g.cost(i, j) + dist[i]) {
//					dist[j] = g.cost(i, j) + dist[i];
//				}
//				if (dist[j] < min_content) {
//					min_index = j;
//				}
//			}
//			g.V_mark[min_index] = visited;
//		}*/
//		for (int i = g.first(t); i < g.v(); i = g.next(t, i)) {
//			dist[i] = g.cost(t, i);
//		}
//		for (int i = 0; i < g.v(); i++) {
//			int curr = min_index;
//			for (int j = g.first(min_index); j < g.v(); j = g.next(t, j)) {
//				if (dist[j] > g.cost(curr, j) + dist[curr]) {
//					dist[j] = g.cost(curr, j) + dist[curr];
//				}
//				if (dist[j] < min_content) {
//					min_index = j;
//				}
//				if (dist[j] > max[t]) {
//					max[t] = dist[j];
//				}
//			}
//			g.V_mark[min_index] = visited;
//		}
//		
//	}
//	
//
//}

void Graph::all_pairs_shortest_path() {
	int min(int, int);
	for (int k = 0; k < v(); k++) {
		for (int i = 0; i < v(); i++) {
			if (matrix[i][k] == MAX) continue;
			for (int j = 0; j < v(); j++) {
				if (matrix[k][j] == MAX) continue;
				if (i == j) continue;
				/*if (g.matrix[i][j] == MAX) {
					g.matrix[i][j] = max(g.matrix[i][j], g.matrix[i][k] + g.matrix[k][j]);
				}*/
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
	print();
}
int max(int a, int b) {
	if (a >= MAX) return b;
	else if (b >= MAX) return a;
	else {
		return a > b ? a : b;
	}
}

int min(int a, int b) {
	return a < b ? a : b;
}


int getCenter(Graph g, int& time) {
	int min_maxtime = MAX, min_index = 0, temp = 0;
	g.all_pairs_shortest_path();
	for (int i = 0; i < g.v(); i++) {
		temp = g.getMaxTime(i);
		if (temp < min_maxtime) {
			min_maxtime = temp;
			min_index = i;
		}
	}
	time = min_maxtime;
	return min_index;
}


int main()
{
	int** graph = new int* [5];
	for (int i = 0; i < 5; i++) {
		graph[i] = new int[5];
		for (int j = 0; j < 5; j++) {
			graph[i][j] = MAX;
		}
	}
	graph[0][1] = 2;
	graph[1][0] = 2;
	graph[0][2] = 5;
	graph[2][0] = 5;
	graph[1][2] = 6;
	graph[2][1] = 6;
	graph[1][4] = 10;
	graph[4][1] = 10;
	graph[3][4] = 1;
	graph[4][3] = 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	Graph test(5);
	test.creatAgraph(graph, 5);
	int min_maxtime = 0, center = 0;
	center = getCenter(test, min_maxtime);
	cout << center << " " << min_maxtime << endl;
	for (int i = 0; i < 5; i++) {
		delete[] graph[i];
	}
	delete[] graph;
	return 0;
}



