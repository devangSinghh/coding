#include "allheaders.h"
using namespace std;
typedef vector<int> vi;

vector<pair<int, int>> activitySelection(vi start, vi duration){
	int n = start.size();
	vi endTime(n);
	vector<pair<int, int>>res;
	for (int i = 0; i < n; i++)
		endTime[i] = start[i] + duration[i];

	vector<vector<int>>p(n, vector<int>(3, 0));
	for (int i = 0; i < n; i++)
		p[i][0] = endTime[i], p[i][1] = start[i], p[i][2] = duration[i];

	sort(begin(p), end(p), [](auto a, auto b) { return a[0] < b[0]; });

	int i = 0, j = 1;
	res.push_back({ start[i], duration[i] });


	for (int j = 1; j < n; j++) {
		if (p[j][1] >= p[i][0])
			res.push_back({ start[j], duration[j] }), i = j;
	}
	return res;
}

void egyptianFraction(int nr, int dr) {
	int frac = ceil((double)dr / (double)nr);
	if (nr == 0 or dr == 0) return;
	cout << "1/" << frac << " \n";

	int newNr = nr * frac - dr, newDr = frac*dr;
	egyptianFraction(newNr, newDr);
}

//Activity selection with K persons
//https://www.geeksforgeeks.org/activity-selection-problem-with-k-persons/?ref=rp
int totalShopsVisited(vector<int>arr, vector<int>endT, int k) {
	vector<pair<int, int>>p;
	multiset<int>m;
	int n = arr.size();
	for (int i = 0; i < n; i++) {
		p[i] = { endT[i], arr[i] };
	}
	int count = 0;
	sort(begin(p), end(p), [](const auto &a, const auto &b) {
		return a.first < b.first;
	});
	for (int i = 0; i < n; i++) {
		bool flag = false;

		if (!m.empty()) {
			auto it = m.upper_bound(p[i].second);
			if (it != m.begin()) {
				it--;
				if (*it <= p[i].first) {
					m.erase(it);
					m.insert(p[i].first);
					count++;
					flag = true;
				}
			}
		}

		if (m.size() < k and flag == false) {
			m.insert(p[i].first);
			count++;
		}
	}

	return count;
}