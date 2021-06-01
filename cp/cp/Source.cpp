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
#include "graph.h"
#include "strings.h"
#include <bitset>
#include <unordered_map>
#include <map>
#include <numeric>
#include <deque>
#include <list>
#include <set>
#include <iterator>
#include <queue>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int, int>pii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<int>>vii;
typedef unordered_map<int, int> umap;

//#include<bits/stdc++.h>


//https://stackoverflow.com/a/31165481/10814894


//void solve() {
//	int a;
//}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	graph g(9);
	g.addWeightedEdge(0, 1, 4);
	g.addWeightedEdge(0, 7, 8);
	g.addWeightedEdge(1, 2, 8);
	g.addWeightedEdge(1, 7, 11);
	g.addWeightedEdge(2, 3, 7);
	g.addWeightedEdge(2, 8, 2);
	g.addWeightedEdge(2, 5, 4);
	g.addWeightedEdge(3, 4, 9);
	g.addWeightedEdge(3, 5, 14);
	g.addWeightedEdge(4, 5, 10);
	g.addWeightedEdge(5, 6, 2);
	g.addWeightedEdge(6, 7, 1);
	g.addWeightedEdge(6, 8, 6);
	g.addWeightedEdge(7, 8, 7);
	
	g.dijkstra(0);

	return 0;
}