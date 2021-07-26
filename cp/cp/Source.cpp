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
#define se second
#define fi first
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


int modPow(int x, int n, int m) {
    if (x == 0 and n == 0) return 0;
    if (n == 0) return 1;
    long long p = (modPow(x, n / 2, m) + m) % m;
    p = (p * p) % m;
    return n % 2 ? (p * x + m) % m : p;
}

ll p[100005];

void pre_compute_product_of_divisors() {
    p[0] = 0; p[1] = 1;
    if (p[2] != 0) return;
    for (ll i = 2; i < 100005; i += 1) {
        if (p[i] == 0) {
            p[i] = 2;
            for (ll j = i + i; j < 100005; j += i) {
                if (p[j] == 0) p[j] = 1;
                ll tmp = j;
                ll cnt = 0;
                while (tmp % i == 0) {
                    cnt += 1;
                    tmp /= i;
                }
                p[j] *= (cnt + 1);
            }
        }
    }
    for (int i = 2; i < 100005; i += 1) {
        p[i] = (modPow(i, p[i] / 2, mod) % mod * (p[i] & 1 ? (ll)sqrt(i) : 1) % mod) % mod;
    }
}

unsigned int divisor_count(unsigned int n) {
    unsigned int total = 1;
    for (; (n & 1) == 0; n >>= 1)
        ++total;
    // Odd prime factors up to the square root
    for (unsigned int p = 3; p * p <= n; p += 2) {
        unsigned int count = 1;
        for (; n % p == 0; n /= p)
            ++count;
        total *= count;
    }
    // If n > 1 then it's prime
    if (n > 1)
        total *= 2;
    return total;
}

unsigned int divisor_product(unsigned int n) {
    return static_cast<unsigned int>(modPow(n, divisor_count(n) / 2.0, mod));
}

int peak(vector<int>A) {
    int n = A.size();
    int l = 0, r = n - 1, idx = 0;
    while (l < r) {
        int m = l + (r - l) / 2, curr = A[m], prev = -1, next = -1;
        if (m > 0) prev = A[m - 1];
        if (m < n - 1) next = A[m + 1];
        if (curr > next and curr > prev) return m;
        else if (curr < next) l = m + 1;
        else r = m;
    }
    return 0;
}

int main() {
    

    string s = "23||34";

    for (int i = 0; i < s.size(); i++) {
        int j = i;
        if (isdigit(s[i])) {
            while (isdigit(s[j])) j++;
        }

        cout << s.substr(i, j - i) << endl;
        i = j;
    }

}