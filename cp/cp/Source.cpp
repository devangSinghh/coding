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
#include <unordered_set>
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


string multiple(int n) {
	if (n == 1) return "1";
	vector<int>p(n, -1);
	vector<int>state(n, -1);
	queue<int>q;
	int steps[2] = { 0, 1 };
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == 0) break;
		for (auto step : steps) {
			int curr = (u * 10 + step) % n; //this becomes new state
			if (p[curr] == -1) {
				p[curr] = u;
				state[curr] = step;
				q.push(curr);
			}
		}
	}
	print(state);
	string s = "";
	//for (auto c : state)
	//	s += to_string(c);
	return s;
}

struct Edge {
	int u, v, w;
	bool operator < (Edge const &other) {
		return w < other.w;
	}
};

int findSet(vector<int>parent, int v) {
	if (v == parent[v])
		return v;
	return parent[v] = findSet(parent, parent[v]);
}

void Union(vector<int>parent, vector<int>rank, int x, int y) {
	x = findSet(parent, x);
	y = findSet(parent, y);
	if (x != y) {
		if (rank[x] < rank[y])
			swap(x, y);
		parent[y] = x;
		if (rank[x] == rank[y])
			rank[x]++;
	}
}

int longestConsecutive(vector<int> &num) {
	unordered_map<int, int> m;
	int r = 0;
	for (int i : num) {
		if (m[i]) continue;
		r = max(r, m[i] = m[i + m[i + 1]] = m[i - m[i - 1]] = m[i + 1] + m[i - 1] + 1);
	}
	return r;
}

auto max_element_less_than_k(vector<int>::reverse_iterator s, vector<int>::reverse_iterator e, int k) {
	auto mx = prev(e);
	for (auto it = s; it != e; it++)
		if (*it > *mx and *it < k) mx = it;
	return mx;
}

vector<int>spath;
void path(vector<int>&parent, int j) {
	if (parent[j] == -1)
		return;
	path(parent, parent[j]);
	spath.push_back(j);
}

int dijkstra(int A, const vector<vector<int>>B, int src, int dest) {
	vector<vector<pair<int, int>>>g(A + 1);
	vector<vector<int>>weights(A + 1, vector<int>(A + 1, INT_MAX));
	int shortestWeight = INT_MAX;
	for (auto& c : B) {
		g[c[0]].push_back({ c[1], c[2] });
		g[c[1]].push_back({ c[0], c[2] });
		weights[c[0]][c[1]] = c[2];
	}
	set<pair<int, int>>Set;
	vector<int>dist(A + 1, INT_MAX);
	vector<bool>visited(A + 1, false);
	vector<int>parent(A + 1, -1);
	Set.insert({ 0, src });
	dist[src] = 0;

	while (!Set.empty()) {
		auto p = *begin(Set);
		int d = p.first, u = p.second;
		Set.erase(begin(Set));
		//if (u == dest) break;
		if (visited[u])continue;
		visited[u] = true;
		for (auto p : g[u]) {
			int  v = p.first, w = p.second;
			if (!visited[v] and dist[v] > d + w) {
				parent[v] = u;
				dist[v] = d + w;
				Set.insert({ dist[v], v });
			}
		}
	}

	spath.push_back(src);
	path(parent, dest);
	//print2DVector(weights);
	print(spath);
	for (int i = 0; i < spath.size() - 1; i++) {
		shortestWeight = min(shortestWeight, weights[spath[i]][spath[i + 1]]);
	}

	return shortestWeight;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	vector<int> v(10);
	iota(v.begin(), v.end(), 1);
	double x = accumulate(v.begin(), v.end(), 0.0, [&](double x, double y) {return x + y / v.size(); });
	cout << x << endl;
	return 0;
}