#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include "matrix.h"

using namespace std;

void print2dVector(vector<vector<int>> v) {
	for (auto &i : v) {
		for (int j = 0; j < i.size(); j++)
			cout << i[j] << " ";
		cout << "\n";
	}
}

//to rotate a matrix clockwise => first reverse up down => swap the symmetry
//to rotate a matrix anti-clockwise => first reverse left right => swap the symmetry

void rotateClockwise(vector<vector<int>>mat) {
	reverse(mat.begin(), mat.end());
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < i; j++) {
			swap(mat[i][j], mat[j][i]);
		}
	}
	print2dVector(mat);
}

void rotateantiClockwise(vector<vector<int>>mat) {
	for (auto &i : mat) reverse(i.begin(), i.end());

	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < i; j++) {
			swap(mat[i][j], mat[j][i]);
		}
	}
	print2dVector(mat);
}


namespace MAT {
	int main() {

		return 0;
	}
}