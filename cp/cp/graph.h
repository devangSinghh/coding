#include<iostream>
#define NOMINMAX
#include<algorithm>
#undef NOMINMAX
#include <stdlib.h>
#include<vector>
#include<string>
#include<sstream>
#include<math.h>
#include "matrix.h"
#include "array.h"
#include "strings.h"
#include <bitset>
#include <unordered_map>
#include <map>
#include <numeric>
#include <deque>
#include <list>
#include <iterator>
#include <stack>
#include <queue>
#pragma once
using namespace std;
class __declspec(dllexport) graph {
private :
	int v;
	list <int> *adj;
	vector<int>result;
	map<int, bool> visited;
	map<int, list<int>> adjDFS;
	vector<vector<int>>edges;
	vector<pair<int, int>> *graphRepW; //for dijkstra
public:
	graph(int v);
	void addEdge(int v, int w);
	void addEdgeForDfs(int v, int w);
	void addWeightedEdge(int u, int v, int w);
	void BFS(int s);
	void DFS(int s);
	void traverseGraph();
	void printGraph();
	void topologicalSort();
	void topologicalSortUtil(int v, stack<int>Stack);
	vector<int>findRedundantConnection(vector<vector<int>>edges);
	void dijkstra(int s);
};
