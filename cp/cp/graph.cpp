#include "graph.h"
#include "allheaders.h"
constexpr auto INF = 0x3f3f3f3f;
graph::graph(int v) : v(v), adj(new list<int>[v]), graphRepW(new vector<pair<int, int>>[v]) {}
void graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}
void graph::addEdgeForDfs(int v, int w) {
	adjDFS[v].push_back(w);
}

void graph::addWeightedEdge(int u, int v, int w) {
	graphRepW[u].push_back({ v, w });
	graphRepW[v].push_back({ u, w });
}

void graph::BFS(int start) {
	bool *visited = new bool[v];
	for (int i = 0; i < v; i++)
		visited[i] = false;

	queue<int>q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		start = q.front();
		q.pop();
		result.push_back(start);
		for (auto vertex : adj[start]) {
			if (!visited[vertex])
				visited[vertex] = true, q.push(vertex);
		}
	}
}
void graph::DFS(int s) {
	//if (visited[s]) return;
	visited[s] = true;
	result.push_back(s);
	for (auto c : adjDFS[s]) {
		if (!visited[c])
			DFS(c);
	}
}
void graph::traverseGraph() {
	for (auto c : result) cout << c << " ";
	cout << "\n";
}

// https://leetcode.com/problems/redundant-connection/
//theory included : union find
//start with all elements as their own tree...
//keep building the tree as until you find the closing edge(edge which will close the loop)...this edge will be the answer 
vector<int> graph::findRedundantConnection(vector<vector<int>> edges) {
	vi parent(edges.size() + 1);
	vi res;
	for (auto e : edges) {
		int n1 = e[0], n2 = e[1];
		while (parent[n1]) n1 = parent[n1];
		while (parent[n2]) n2 = parent[n2];
		if (n1 == n2) res = e;
		else parent[n1] = n2;
	}
	return res;
}


void graph::topologicalSortUtil(int v, stack<int>Stack) {
	visited[v] = true;
	for (auto i : adj[v]) {
		if (!visited[i])
			topologicalSortUtil(i, Stack);
	}
	Stack.push(v);
}


void graph::topologicalSort() {
	stack<int>Stack;
	for (int i = 0; i < v; i++) {
		if (!visited[i])
			topologicalSortUtil(i, Stack);
	}
	cout << "Topological sorting : ";
	while (!Stack.empty())
		cout << Stack.top() << " ", Stack.pop();
	cout << "\n";
}

//time complexity : O((|V| + |E|)logV)
//space complexity : O(|V| + |E|)
void graph::dijkstra(int s) {
	set<pair<int, int>>Set;    //(distance, vertex)
	vector<int>dist(v, INF);   //initialize all distances to inf
	Set.insert({ s, 0 });      // insert starting point with current distance as 0 (distance of starting point from itseltf will be 0)
	dist[s] = 0;               //update the dist vector with starting point distance as 0
	while (!Set.empty()) {     //start iterting over Set...until it becomes empty
		auto minVertex = *(Set.begin()); //Set keeps elements in sorted order so first element will be minimum
		Set.erase(begin(Set));           //erase first element
		int u = minVertex.second;
		for (auto it : graphRepW[u]) {   //start iterating over its(the vertex which we pulled out of Set) neighbours
			int v = it.first, weight = it.second; //in graphRepW...graph representation is stored in form of pair (val of vertex, weight of edge)
			if (dist[v] > dist[u] + weight) {     //update distance for vertex v
				if (dist[v] != INF)               // if vertex v is already present in Set...
					Set.erase(Set.find({ dist[v], v })); //then first remove it from Set
				dist[v] = dist[u] + weight;
				Set.insert({ dist[v], v });      //then insert updated distance
			}

		}
	}

	for (auto c : dist)
		cout << c << " ";
	cout << "\n";
}