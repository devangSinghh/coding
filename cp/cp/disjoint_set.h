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
#ifndef _DISJOINT_SET_
#define _DISJOINT_SET_
#endif
using namespace std;
#define all(x) begin(x), end(x);
class __declspec(dllexport) disjoint_set {
	vector<int>v;
	int sz;
public :
	disjoint_set(int n);
	void makeset(int n);
	int find(int i);
	void join(int i, int j);
	int size();
};

