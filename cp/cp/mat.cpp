#include "allheaders.h"
using namespace std;

void print2dVector(vector<vector<int>> v) {
	for (auto &i : v) {
		for (int j = 0; j < i.size(); j++)
			cout << i[j] << " ";
		cout << "\n";
	}
}

//to rotate a matrix clockwise => first reverse up down => swap the symmetry

void rotateClockwise(vector<vector<int>>mat) {
	reverse(mat.begin(), mat.end());
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < i; j++) {
			swap(mat[i][j], mat[j][i]);
		}
	}
	print2dVector(mat);
}

//to rotate a matrix anti-clockwise => first reverse left right => swap the symmetry
void rotateantiClockwise(vector<vector<int>>mat) {
	for (auto &i : mat) reverse(i.begin(), i.end());

	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < i; j++) {
			swap(mat[i][j], mat[j][i]);
		}
	}
	print2dVector(mat);
}

//Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
int countSquareSubMatrix(vector<vector<int>>mat) {
	int r = mat.size(), c = mat[0].size(), ans = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			if(mat[i][j] == 1)
				if (i == 0 || j == 0) ans += 1;
				else mat[i][j] = min({ mat[i - 1][j], mat[i][j - 1], mat[i - 1][j - 1] }) + 1, ans += mat[i][j];
	}
	return ans;
}


//Fibonacci number calculation using matrix exponentiation (fastest method) 
void multiply(int F[2][2], int M[2][2]) {
	int a = F[0][0] * M[0][0] + F[0][1] * M[1][0];
	int b = F[0][0] * M[0][1] + F[0][1] * M[1][1];
	int c = F[1][0] * M[0][0] + F[1][1] * M[1][0];
	int d = F[1][0] * M[0][1] + F[1][1] * M[1][1];
	F[0][0] = a;
	F[0][1] = b;
	F[1][0] = c;
	F[1][1] = d;
}
void power(int F[2][2], int n) {
	if (n == 0 || n == 1)
		return;
	int M[2][2] = { {1,1},{1,0} };
	power(F, n / 2);
	multiply(F, F);
	if (n % 2 != 0)
		multiply(F, M);
}

int fibonacci_using_MatrixExponentiation(int n) { // number of instructions executed 100log2(n - 1) + 1000 , even for very large n
	int F[2][2] = { {1,1},{1,0} };
	if (n == 0)
		return 0;
	power(F, n - 1);
	return F[0][0];
}

namespace MAT {
	int main() {

		return 0;
	}
}