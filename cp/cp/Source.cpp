#include<iostream>
#define NOMINMAX
#include<algorithm>
#undef NOMINMAX
#include <stdlib.h>
#include <cctype>
#include<vector>
#include<valarray>
#include<string>
#include<sstream>
#include<math.h>
#include<regex>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <numeric>
#include <deque>
#include <list>
#include <set>
#include <iterator>
#include <stack>
#include <queue>
#include <iomanip>
//#include "matrix.h"
//#include "array.h"
//#include "graph.h"
//#include "strings.h"
//#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int>pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<long long> vl;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<int>>vii;
typedef vector<vector<long long>>vll;
typedef unordered_map<int, int> umap;
#define PQ priority_queue
const int inf = INT_MAX;
const int n_inf = INT_MIN;
const int mod = 1e9 + 7;
#pragma GCC optimize("Ofast")
static const auto fast = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	return 0;
} ();
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); };
int d2[8][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
int dir[5] = { 0, -1, 0, 1, 0 };


vector<string>prettyJSON(string s) {
    int n = s.size();
    int indent = 0;
    vector<string>res;
    char pre = 0;
    string temp;
    for (auto c : s) {
        if (c == ' ') continue;
        if (c == ']' or c == '}')
            indent--;
        if (pre == '[' or pre == '{' or pre == ',' or c == '}' or c == ']') {
            temp += '\n';
            for (int i = 0; i < indent; i++)
                temp += " ";
        }
        if (c == '[' or c == '{') {
            temp += '\n', indent++;
        
            for (int i = 0; i < indent; i++)
            temp += " ";
        }
        temp += c;
        pre = c;
    }

    stringstream ss(temp);
    string str;
    while (getline(ss, str, '\n'))
        res.push_back(str);
    return res;
}


int main() {
    

}