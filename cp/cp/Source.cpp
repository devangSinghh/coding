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

//struct Edge {
//	int u, v, w;
//	bool operator < (Edge const &other) {
//		return w < other.w;
//	}
//};
//void solve() {
//	int a;
//}
void changesign(int n){
	//Changes sign without multiplying -1
	n=(~n+1);//~n makes the number n of opposite sign adn also have to add one to the number 
	//eg->  ~321=320
}

int findSet(vector<int>parent, int v) {
	if (v == parent[v])
		return v;
	return parent[v] = findSet(parent, parent[v]);
}

// bool detectLoop(Node* head)//find loop in linked list
//     {
//         Node* p1=head;
//         Node* p2=head;
//         while(p1->next!=NULL && p2->next->next!=NULL){
//             p1=p1->next;
//             p2=p2->next->next;
//             if(p1==p2){
//                 p1=head;
//                 while(p1!=p2 && p1->next!=NULL && p2->next!=NULL){
//                     p1=p1->next;
//                     p2=p2->next;
//                 }
//                 return true;
//             }
//         }
//         return false;
//     }

int kadanealgo(int a[], int n){
        int res=INT_MIN,tmp=0;
        for(int i=0;i<n;i++){
            tmp+=a[i];
            if(res<tmp)res=tmp;
            if(tmp<0)tmp=0;
        }
        return res;
    }

void merge(long long arr1[], long long arr2[], int n, int m) //merge 2 array without extra space O((n+m)log(n+m))
        { 
            int i=0,j=0,k=n-1;
            while(i<=k && j<m){
                if(arr1[i]<arr2[j])i++;
                else{
                    swap(arr1[k--],arr2[j++]);
                }
            }
            sort(arr1,arr1+n);
            sort(arr2,arr2+m);
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

int getFileNum(string s) {
	string num;
	int i = s.size() - 2;
	while (i >= 0 and s[i] != '(') num += s[i--];
	reverse(begin(num), end(num));
	return stoi(num);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cout << (1 << 10);

	return 0;
}
