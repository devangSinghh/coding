#include "graph.h"
#include "disjoint_set.h"
#include "allheaders.h"
constexpr auto INF = 0x3f3f3f3f;
typedef unordered_map<string, unordered_map<string, double>> umapSUSd;
graph::graph(int v) : v(v), adj(new vector<int>[v]), graphRepW(new vector<pair<int, int>>[v]) {};
graph::graph(int v, int e) : v(v), e(e), edge(new Edge[e]), adj(new vector<int>[v]), graphRepW(new vector<pair<int, int>>[v]) {};

graph* graph::createGraph(int v, int e) {
	graph* g = new graph(v, e);
	return g;
}

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
	vector<int>visited(v, false);
	queue<int>q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		start = q.front();
		if (visited[start]) continue;
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
		while (parent[n1]) n1 = parent[n1]; //find
		while (parent[n2]) n2 = parent[n2];
		if (n1 == n2) res = e; //if we found 2 elements within same tree then we've found a closing edge
		else parent[n1] = n2;  //keep merging both the trees
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
	vector<int>dist(v, INF);   //initialize all distances to infx	
	Set.insert({ 0, s });      // insert starting point with current distance as 0 (distance of starting point from itseltf will be 0)
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
	for (auto c : dist) cout << c << " ";
	cout << "\n";
}

//minimum moves for knight to move from point (a, b) to point (x, y) in a matrix of row * col
int knight(int row, int col, int a, int b, int x, int y) {
	priority_queue<vector<int>, vector<vector<int>>, greater<>>pq; //(moves, x, y)
	vector<vector<bool>>visited(row + 1, vector<bool>(col + 1, false));
	vector<vector<int>>d = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2} };
	pq.push({ 0, a, b });
	while (!pq.empty()) {
		auto u = pq.top();
		pq.pop();
		visited[u[1]][u[2]] = true;
		if (u[1] == x and u[2] == y) return u[0]; //if found the point then return
		for (int i = 0; i < 8; i++) {             //search in every direction
			int nr = u[1] + d[i][0], nc = u[2] + d[i][1];
			if (nr >= 1 and nr <= row and nc >= 1 and nc <= col and !visited[nr][nc]) //sanity check
				visited[nr][nc] = true, pq.push({ u[0] + 1, nr, nc });
		}
	}
	return -1;
}

int dfsForTranspositions(vector<int>goesTo, vector<int>visited, int s) {
	if (visited[s]) return 0;
	visited[s] = 1;
	int x = dfsForTranspositions(goesTo, visited, goesTo[s]);
	return x + 1;
}

int numberOfTranspositions(vector<int>permutations) {
	int n = permutations.size(), transpositions = 0, ans = 0;
	vector<int>visited(n + 1, 0);
	vector<int>goesTo(n + 1); 
	for (int i = 1; i <= n; i++)
		goesTo[permutations[i]] = i + 1;

	for (int i = 1; i <= n; i++)
		if (visited[i] == 0)
			ans = dfsForTranspositions(goesTo, visited, i), transpositions += ans - 1;
	return transpositions;
}

//https://leetcode.com/problems/evaluate-division/
double dfsForDivisonInGraph(string s, string e, umapSUSd g, unordered_set<string>visited) {
	if (g.find(s) == g.end()) return -1;
	if (g[s].find(e) != g[s].end()) return g[s][e];
	for (auto c : g[s]) {
		if (find(begin(visited), end(visited), c.first) != visited.end())
			continue;
		visited.insert(c.first);
		double res;
		if ((res = dfsForDivisonInGraph(c.first, e, g, visited)) != -1) {
			return g[s][e] = g[s][c.first] * res;
		}
	}
	return -1;
}

vector<double>divisionUsingGraph(vector<vector<string>> eq, vector<double> values, vector<vector<string>> queries){
	umapSUSd g;
	int n = eq.size();
	vector<double>res;
	for (int i = 0; i < n; i++) {
		auto e = eq[i];
		g[e[0]][e[1]] = values[i];
		g[e[1]][e[0]] = 1.0/values[i];
		g[e[0]][e[0]] = 1.0;
		g[e[1]][e[1]] = 1.0;
	}
	unordered_set<string>visited;
	for (auto c : queries) {
		visited = { c[0] };
		res.push_back(dfsForDivisonInGraph(c[0], c[1], g, visited));
	}
	return res;
}


//https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/
//A* search
int dist(int x, int x1, int y, int y1) {
	return abs(x1 - x) + abs(y1 - y);
}
bool isValid(vector<vector<char>>&A, int i, int j, int m, int n) {
	if (i < 0 or j < 0 or i > m - 1 or j > n - 1 or A[i][j] == '#') return false;
	return true;
}
int minPushBox(vector<vector<char>>& A) {
	int m = A.size(), n = A[0].size();
	vector<int>target, box, start;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (A[i][j] == 'T') target = vector<int>({ i, j });
			else if (A[i][j] == 'B') box = vector<int>({ i, j });
			else if (A[i][j] == 'S') start = vector<int>({ i, j });
	vector<int>d = { 0, 1, 0, -1, 0 };
	auto comp = [](const vector<int>&a, const vector<int>&b) { return a[0] > b[0]; };
	priority_queue<vector<int>, vector<vector<int>>, decltype(comp)>pq(comp);
	set<string>Set;
	vector<int>init = { dist(box[0], box[1], target[0], target[1]), 0, start[0], start[1], box[0], box[1] };
	pq.push(init);
	while (!pq.empty()) {
		auto p = pq.top(); pq.pop();
		int moves = p[1], sx = p[2], sy = p[3], bx = p[4], by = p[5];
		if (bx == target[0] and by == target[1]) return moves;
		string s = to_string(sx) + ":" + to_string(sy) + "|" + to_string(bx) + ":" + to_string(by);
		if (Set.count(s)) continue;
		Set.insert(s);
		for (int i = 0; i < 4; i++) {
			int nx = sx + d[i], ny = sy + d[i + 1];
			if (!isValid(A, nx, ny, m, n)) continue;
			vector<int>next;
			if (nx == bx and ny == by) {
				int nbx = nx + d[i], nby = ny + d[i + 1];
				if (!isValid(A, nbx, nby, m, n)) continue;
				next = { dist(nbx, nby, target[0], target[1]) + moves + 1, moves + 1, nx, ny, nbx, nby };
			}
			else {
				next = { p[1], moves, nx, ny, bx, by };
			}
			pq.push(next);
		}
	}
	return -1;
}


//https://leetcode.com/problems/min-cost-to-connect-all-points/
int find(vector<int>v, int i) {
	return v[i] < 0 ? i : v[i] = find(v, v[i]);
}
int minCostConnectPoints(vector<vector<int>>& A) {
        int n = A.size(), res = 0, k = 0;
        vector<int>v(n, -1);
        vector<vector<int>>arr;
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                arr.push_back({abs(A[i][0] - A[j][0]) + abs(A[i][1] - A[j][1]), i, j });
        make_heap(begin(arr), end(arr), greater<vector<int>>());
        while(!arr.empty()) {
            pop_heap(begin(arr), end(arr), greater<vector<int>>());
			auto e = arr.back();
			int dist = e[0], i = e[1], j = e[2];
            arr.pop_back();
            i = find(v, i), j = find(v, j);
            if(i != j) {
                res += dist;
                v[i] += v[j];
                v[j] = i;
                if(v[i] == -n) break;
            }
        }
        return res;
 }

//int countRestrictedPaths(int n, vector<vector<int>>& edges) {
//	vector<vector<pair<int, int>>>g(n + 1);
//	for (auto c : edges) {
//		g[c[0]].push_back({ c[1], c[2] });
//		g[c[1]].push_back({ c[0], c[2] });
//	}
//	int* dist = new int[n + 1];
//	for (int i = 0; i <= n; i++) dist[i] = INT_MAX;
//	set<pair<int, int>>Set;
//	Set.insert({ 0, n });
//	dist[n] = 0;
//	while (!Set.empty()) {
//		auto [d, u] = *begin(Set);
//		Set.erase(begin(Set));
//		for (auto c : g[u]) {
//			int v = c.first, w = c.second;
//			if (dist[v] > dist[u] + w) {
//				dist[v] = dist[u] + w;
//				Set.insert({ dist[v], v });
//			}
//		}
//	}
//	int dp[20001] = {};
//	for (int i = 1; i <= n; i++) dp[i] = -1;
//	function<int(int)> dfs = [&](int s) {
//		if (s == 1) return 1;
//		if (dp[s] != -1) return dp[s];
//		int count = 0;
//		for (auto& [v, w] : g[s]) {
//			int d_v = dist[v], d_s = dist[s];
//			if (d_v > d_s)
//				count = (count % mod + dfs(v) % mod) % mod;
//		}
//		return dp[s] = count;
//	};
//	return dfs(n);
//}

//https://leetcode.com/problems/shortest-path-visiting-all-nodes/
int shortestPathLength(vector<vector<int>>& graph) {
	int n = graph.size(), mask = (1 << n) - 1, steps = 0;
	vector<vector<bool>>visited(n, vector<bool>((1 << n) - 1));
	queue<pair<int, int>>q;
	for (int i = 0; i < n; i++) {
		q.push({ i,  1 << i });
		visited[i][1 << i] = true;
	}
	while (!q.empty()) {
		int n = q.size();
		while (n--) {
			auto p = q.front(); q.pop();
			int id = p.first, thisMask = p.second;
			for (auto i : graph[id]) {
				auto next = make_pair(i, thisMask | 1 << i);
				if (next.second == mask) return steps + 1;
				if (visited[next.first][next.second]) continue;
				q.push(next);
				visited[next.first][next.second] = true;
			}
		}
		steps++;
	}
	return 0;
}

//find cycle in directed graph
int findCycleInDirectedgraph(int n, vector<vector<int> >& B) {
	vector<vector<int>>g(n + 1);
	vector<int>color(n + 1);

	for (auto p : B)
		g[p[0]].push_back(p[1]);

	function<bool(int)> dfs = [&](int v) {
		if (color[v] == 1) return true;
		if (color[v] == 2) return false;
		color[v] = 1;

		for (auto w : g[v]) {
			if (dfs(w)) return true;
		}

		color[v] = 2;
		return false;
	};

	for (int i = 1; i <= n; i++) {
		if (color[i] == 0) {
			if (dfs(i)) return 1;
		}
	}
	return 0;
}