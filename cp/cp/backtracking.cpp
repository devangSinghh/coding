#include "allheaders.h"
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
using namespace std;
const int INF = 1e9;

class TrieNode{
public:
	bool word;
	TrieNode* children[26];
	TrieNode() {
		word = false;
		memset(children, NULL, sizeof(children));
	}
};


//https://leetcode.com/problems/unique-paths-iii/
int dfsUniquePathsIII(vector<vector<int>>A, int i, int j, int m, int n, int cs, int steps) {
	if (i < 0 or j < 0 or i >= m or j >= n or A[i][j] == -1) return 0;
	if (A[i][j] == 2) return steps == cs ? 1 : 0; //if we reach the target and the steps taken by us is equal to the number of 0s + initial point...
	//return 1 i.e. 1 path exists else return 0, i.e. no path
	A[i][j] = -1;
	int path = dfsUniquePathsIII(A, i + 1, j, m, n, cs + 1, steps) + dfsUniquePathsIII(A, i, j + 1, m, n, cs + 1, steps)
		+ dfsUniquePathsIII(A, i - 1, j, m, n, cs + 1, steps) + dfsUniquePathsIII(A, i, j - 1, m, n, cs + 1, steps);
	A[i][j] = 0; //backtrack the point
	return path;
}
int uniquePathsIII(vector<vector<int>> A) {
	int m = A.size(), n = A[0].size(), steps = 0, i1 = 0, j1 = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (A[i][j] == 1) i1 = i, j1 = j; //store starting point
			else if (A[i][j] != -1) steps++;  //store all steps that we can take in the grid...it will include all except '-1' cells

	return dfsUniquePathsIII(A, i1, j1, m, n, 0, steps);
}

//https://leetcode.com/problems/letter-case-permutation/submissions/
void letterCasePermutation(vector<string>& res, string& s, int idx) {
	if (idx == s.size()) {
		res.push_back(s);
		return;
	}
	letterCasePermutation(res, s, idx + 1);
	if (isalpha(s[idx]))
		s[idx] ^= (1 << 5), letterCasePermutation(res, s, idx + 1);
}
vector<string> letterCasePermutation(string s) {
	string temp;
	vector<string>res;
	letterCasePermutation(res, s, 0);
	return res;
}

//https://leetcode.com/problems/permutations-ii/
void backtrack_permuteUnique(vector<vector<int>>& res, vector<int>A, int idx) {
	if (idx == A.size() - 1) {
		res.push_back(A);
		return;
	}

	for (int i = idx; i < A.size(); i++) {
		if (idx != i and A[idx] == A[i]) continue;
		swap(A[i], A[idx]);
		backtrack_permuteUnique(res, A, idx + 1);
	}
}
vector<vector<int>> permuteUnique(vector<int>& A) {
	sort(begin(A), end(A));
	vector<vector<int>>res;
	backtrack_permuteUnique(res, A, 0);
	return res;
}

//https://leetcode.com/problems/word-break-ii/
//vector<string> wordBreak(string s, vector<string> wordDict) {
//	unordered_set<string>words(begin(wordDict), end(wordDict));
//	unordered_map<int, vector<string>>memo{ {s.size(), {""}} };
//	function<vector<string>(int)> sentences = [&](int i) {
//		if (!memo.count(i))
//			for (int j = i + 1; j <= s.size(); j++)
//				if (words.count(s.substr(i, j - i)))
//					for (string tail : sentences(j))
//						memo[i].push_back(s.substr(i, j - i) + (tail == "" ? "" : ' ' + tail));
//		return memo[i];
//	};
//	return sentences(0);
//}

//https://leetcode.com/problems/distribute-repeating-integers/
bool canDistribute(vector<int> nums, vector<int> q, vector<int>counts = {}) {
	unordered_map<int, int>u;
	for (auto c : nums) u[c]++;
	for (auto c : u) counts.push_back(c.second);
	sort(rbegin(counts), rend(counts));
	sort(rbegin(q), rend(q));
	while (!counts.empty() and counts.back() < q.back()) counts.pop_back();
	function<bool(int)> bt = [&](int i) {
		int a = q[i];
		for (auto& c : counts) {
			if (c < a) continue;
			if (i == q.size() - 1) return true;
			c -= a;
			if (bt(i + 1)) return true;
			c += a;
		}
		return false;
	};
	return bt(0);
}

//https://leetcode.com/problems/generate-parentheses/
//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses
//vector<string>allValidParenthesis(int n) {
//	vector<string>res;
//	function<void(string, int, int)> generate = [&](string s, int open, int closed) {
//		if (open < 0 or closed < 0) return;
//		if (open == 0 and closed == 0) {
//			res.push_back(s);
//			return;
//		}
//		if (open > closed) return;
//		generate(s + '(', open - 1, closed);
//		if (open < closed)
//			generate(s + ')', open, closed - 1);
//	};
//	generate("", n, n);
//	return res;
//}

//brace expansion => "abc{d,e}f{gh,ij}" => [abcdfgh, abcdfij, abcefgh, abcefij]
//brace can be nested for eg. "abc{d,e}f{gh,ij}gen{a{a{zz,zzz,zzzz}}lasdf,asf}"
vector<string> braceExpansion(string a) {
	vector<string> ans = { "" };
	int i = 0;
	while (i < a.size()) {
		if (a[i] != '{') for (string& s : ans) s += a[i];
		else {
			vector<string> ans2;
			int depth = 0;
			while (a[i] != '}' or depth != 0) {
				int j = i + 1;
				while (depth != 0 or (a[j] != ',' and a[j] != '}')) {
					if (a[j] == '}') depth--;
					if (a[j] == '{') depth++;
					j++;
				}
				auto ret = braceExpansion(a.substr(i + 1, j - i - 1));
				for (string& s : ans) for (string& r : ret) ans2.push_back(s + r);
				i = j;
			}
			swap(ans, ans2);
		}
		i++;
	}
	return ans;
}

//sequential digits
//An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
//Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
//low = 100, high = 300 => output = [123, 234]
vector<int> sequentialDigits(int low, int high) {
	set<int>Set;
	function<void(int, int, int)> dfs = [&](int low, int high, int idx) {
		long long num = 0;
		if (idx > 9) return;
		for (int i = idx; i <= 9; i++) {
			(num *= 10) += i;
			if (num <= high and num >= low)
				Set.insert(num);
		}
		dfs(low, high, idx + 1);
	};
	dfs(low, high, 1);
	vector<int>res(begin(Set), end(Set));
	return res;
}

//https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/

//https://leetcode.com/problems/numbers-with-same-consecutive-differences/
//Return all non-negative integers of length n such that the absolute difference between every two consecutive digits is k
//n = 3 and k = 7 => output = [181,292,707,818,929] 070 is not a vlaid number due to leading zeros
vector<int>numsSameConsecDiff(int n, int k) {
	vector<int>res;
	function<void(int, int, int)> dfs = [&](int sz, int num, int last) {
		if (sz == n) {
			res.push_back(num); return;
		}
		for (int i = 0; i <= 9; i++)
			if (abs(last - i) == k)
				dfs(sz + 1, num * 10 + i, i);
	};
	for (int i = 0; i <= 9; i++)
		dfs(1, i, i);
	return res;
}

//design, add and search data structure
class WordDictionary {
private:
	TrieNode* root;
	bool search(const char* word, TrieNode* node) {
		for (int i = 0; word[i] and node; i++) {
			if (word[i] != '.')
				node = node->children[word[i] - 'a'];
			else {
				TrieNode* temp = node;
				for (int j = 0; j < 26; j++) {
					node = temp->children[j];
					if (search(word + i + 1, node)) return true;
				}
			}
		}
		return node and node->word;
	}
public :
	WordDictionary() : root(new TrieNode()) {};
	bool search(string word) {
		return search(word.c_str(), root);
	}
	void addWord(string word) {
		TrieNode* node = root;
		for (char c : word) {
			if (!node->children[c - 'a'])
				node->children[c - 'a'] = new TrieNode();
			node = node->children[c - 'a'];
		}
		node->word = true;
	}
};

//find word in board
bool findWordInBoard(vector<vector<char>>board, string word) {
	int m = board.size(), n = board[0].size();
	int d[5] = { 0, -1, 0, 1, 0 };
	vector<vector<bool>>visited(m, vector<bool>(n));
	function<bool(int, int, int)> dfs = [&](int i, int j, int sz) {
		if (sz == word.size()) return true;
		if (i >= 0 and j >= 0 and i < m and j < n and board[i][j] == word[sz] and !visited[i][j]) {
			visited[i][j] = true;
			for (int k = 0; k < 4; k++) {
				int ni = i + d[k], nj = j + d[k + 1];
				if (dfs(ni, nj, sz + 1)) return true;
			}
			visited[i][j] = false;
		}
		return false;
	};
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (board[i][j] == word[0] and dfs(i, j, 0))
				return true;
	return false;
}

//https://leetcode.com/problems/word-ladder-ii/
//Given two words, beginWord and endWord, and a dictionary wordList, 
//return all the shortest transformation sequences from beginWord to endWord
vector<vector<string>>findLadders(string beginWord, string endWord, vector<string>wordList) {
	unordered_set<string>set(begin(wordList), end(wordList));
	unordered_set<string>visited;
	vector<vector<string>>ans;
	queue<vector<string>>q;
	q.push({ beginWord });
	while (!q.empty()) {
		int n = q.size();
		while (n--) {
			auto words = q.front(); q.pop();
			string last = words.back();
			for (int i = 0; i < last.size(); i++) {
				string temp = last;
				for (char c = 'a'; c <= 'z'; c++) {
					temp[i] = c;
					if (set.find(temp) != set.end()) {
						visited.insert(temp);
						auto new_path = words;
						new_path.push_back(temp);
						if (temp == endWord) ans.push_back(new_path);
						else q.push(new_path);
					}
				}
			}
		}
		for (auto& s : visited) set.erase(s);
	}
	return ans;
}

//split in fibonacci sequences
vector<int> splitIntoFibonacci(string s) {
	vector<int>res, ans;
	function<bool(vector<int>, int)> isFibonacci = [](vector<int>nums, int num) {
		int n = nums.size();
		return n < 2 or (long)nums[n - 1] + (long)nums[n - 2] == num;
	};
	function<void(int)> dfs = [&](int idx) {
		if (idx == s.size() and res.size() >= 3) {
			ans = res; return;
		}
		for (int i = idx; i < s.size(); i++) {
			if (i > idx and s[idx] == '0') return;
			long long num = stol(s.substr(idx, i - idx + 1));
			if (num > INT_MAX) return;
			if (isFibonacci(res, num))
				res.push_back(num), dfs(i + 1), res.pop_back();
		}
	};
	dfs(0);
	return ans;
}

//https://leetcode.com/problems/minimum-incompatibility/
//array nums​​​ and int k. split array into k subsets of equal size such that there are no two equal elements in the same subset.
//A subset's incompatibility is the difference between the maximum and minimum elements in that array.
//Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally.
int minimumIncompatibility(vector<int>nums, int k) {
	int n = nums.size(), subset_size = n / k;
	sort(begin(nums), end(nums));
	vector<int>range(1 << n, INF);
	for (int mask = 1; mask < (1 << n); mask++) {
		int small = 16, big = 0, vis = 0, dup = 0;
		for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) {
				if (vis & (1 << nums[i])) {
					dup = 1; break;
				}
				vis |= (1 << nums[i]);
				small = min(small, nums[i]), big = max(big, nums[i]);
			}
		}
		if (!dup) range[mask] = big - small;
	}
	vector<int>dp(1 << n, INF);
	for (int mask = 1; mask < (1 << n); mask++) {
		for (int submask = mask; submask; submask = (submask - 1) & mask) {
			if (__builtin_popcount(submask) == subset_size)
				dp[mask] = min(dp[mask], range[submask] + mask ^ submask);
		}
	}
	return dp.back() >= INF ? -1 : dp.back();
}