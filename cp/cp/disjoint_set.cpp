#include "disjoint_set.h"
#include "allheaders.h";

disjoint_set::disjoint_set(int n) {
	disjoint_set::makeset(n);
}

void disjoint_set::makeset(int n) {
	v.resize(n);
	iota(begin(v), end(v), 0);
	sz = n;
}

int disjoint_set::find(int i) {
	return v[i] < 0 ? i : v[i] = find(v[i]);
}

void disjoint_set::join(int i, int j) {
	int parentI = find(i), parentJ = find(j);
	if (parentI != parentJ) v[parentI] = parentJ, sz--;
}
int disjoint_set::size() {
	return sz;
}

int disjoint_set::findByCompression(int i) { //using path compression technique
	if (v[i] == i) return i;
	else {
		int res = find(v[i]);
		// after finding the root directly connect i to the root
		v[i] = res;
		return res;
	}
}

void disjoint_set::joinByRank(int i, int j) {
	int root_i = find(i), root_j = find(j);
	if (root_i == root_j) return; // both the roots are in same tree no need to perform join

	int root_i_rank = rank[root_i], root_j_rank = rank[j]; //get ranks of both the roots
	if (root_i_rank < root_j_rank)
		v[root_i] = root_j; //move root_i under root_j
	else if (root_i_rank > root_j_rank)
		v[root_j] = root_i; //move root_j under root_i
	else {
		v[root_i] = root_j; //free to move anyone 
		rank[root_j]++; //increment the result of the parent tree
	}
}

//https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/
int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& swaps) {
	int n = source.size(), diff = 0;
	disjoint_set U(n);
	for (auto s : swaps) {
		U.join(s[0], s[1]);
	}
	unordered_map<int, unordered_map<int, int>>map;
	for (int i = 0; i < n; i++) {
		int pi = U.find(i);
		map[pi][source[i]]++;
	}
	for (int i = 0; i < n; i++) {
		int num = target[i];
		int pi = U.find(i);
		if (map[pi][num] <= 0)
			diff++;
		else
			map[pi][num]--;
	}
	return diff;
}