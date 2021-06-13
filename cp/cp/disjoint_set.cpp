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
	return i == v[i] ? i : find(v[i]);
}

void disjoint_set::join(int i, int j) {
	int parentI = find(i), parentJ = find(j);
	if (parentI != parentJ) v[parentI] = parentJ, sz--;
}