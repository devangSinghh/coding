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
#include <unordered_set>
#include <map>
#include <numeric>
#include <deque>
#include <list>
#include <iterator>
#include <stack>
#include <queue>
#pragma once
#include <vector>
#include<algorithm>
#ifndef _MATRIX_
#define _MATRIX_
#endif
using namespace std;

class __declspec(dllexport) graph {
private :
	int v; //vertices
	vector <int> *adj;
	vector<int>result;
	map<int, bool> visited;
	unordered_map<int, vector<int>> adjDFS;
	vector<pair<int, int>> *graphRepW; //for dijkstra
public:
	graph(int v);
	graph(int v, int e);
	void addEdge(int v, int w);
	void addEdgeForDfs(int v, int w);
	void addWeightedEdge(int u, int v, int w);
	void BFS(int s);
	void DFS(int s);
	void traverseGraph();
	void topologicalSort();
	void topologicalSortUtil(int v, stack<int>Stack);
	vector<int>findRedundantConnection(vector<vector<int>>edges);
	void dijkstra(int s);
	vector<double> divisionUsingGraph(vector<vector<string>> eq, vector<double> values, vector<vector<string>> queries);
	double dfsForDivisonInGraph(string s, string e, unordered_map<string, unordered_map<string, int>>g, unordered_set<string>visited);
};
