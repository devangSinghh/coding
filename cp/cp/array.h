#pragma once
#include <vector>
#include<algorithm>
#ifndef _ARRAY_
#define _ARRAY_

typedef std::vector<int> vi;
//typedef std::vector<vector<int>> vii;
typedef std::pair<int, int>  pi;
typedef std::string string;

extern int gcd(int a, int b);
extern bool getParity(unsigned int n, bool parity = 0);
extern int findOddOccuringNumber(vi v);
extern int kadane(vi v);
extern vi  primesBeforeN(int n);
extern vi  subarrayBitWiseOr(vi v);
extern std::pair<int, int>twoSum(vi v, int target);
extern std::vector<vi >threeSum(vi v, int target);
extern void print2DVector(std::vector<vi>v);
extern void printPair(std::vector<pi>v);
extern void print(vi v);
extern int threeSumClosest(vi v, int target);
extern void nextPermutation(vi v);
extern void rotateArrayAntiClockwise(vi v, int k);
extern void rotateArrayClockwise(vi v, int k);
extern void rotateArrayOneLiner(vi v, int k);
extern int combinationsInArrayAddingToTarget(vi v, int target);
extern vi kthRowOfPascalTraingle(int k);
extern int numberOfPathsInMatrix(int row, int col);
extern int lenLongestFibSubseq(vi A);
extern int numMatchingSubseq(string, vi words);
extern int knapsackRecursive(vi profit, vi weights, int capacity, int index);
extern int knapsackBottomUp(vi profit, vi weights, int capacity);
extern int knapsackTopDown(vi profit, vi weights, int capacity);
extern int fractionalKnapSack(vi profit, vi weights, int capacity);
extern bool canMakeEqualSubSets(vi A, int sum , int index);
extern bool canMakeEqualSubSetsTopDown(std::vector<vi> dp, vi A, int sum, int index);
extern bool canPartition(vi v);
extern bool canPartitionBottomUp(vi A);
extern bool canFindSubSetWithSumS(vi A, int s);
extern int arithmaticSlices(vi A);
extern std::vector<pi>activitySelection(vi start, vi duration);
extern void egyptianFraction(int nr, int dr);
extern int totalShopsVisited(vi arr, vi endT, int k);
extern int shortestPathinMatrix(std::vector<std::vector<int>> mat);
#endif
