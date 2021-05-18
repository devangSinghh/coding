#pragma once
#include <vector>
#include<algorithm>
#ifndef _ARRAY_
#define _ARRAY_

extern int findOddOccuringNumber(std::vector<int>v);
extern int kadane(std::vector<int>v);
extern std::vector<int> primesBeforeN(int n);
extern std::vector<int> subarrayBitWiseOr(std::vector<int>v);
extern std::pair<int, int>twoSum(std::vector<int>v, int target);
extern std::vector<std::vector<int>>threeSum(std::vector<int>v, int target);
extern void print2DVector(std::vector<std::vector<int>>v);
extern void print(std::vector<int>v);
extern int threeSumClosest(std::vector<int>v, int target);
extern void nextPermutation(std::vector<int>v);
extern void rotateArrayAntiClockwise(std::vector<int>v, int k);
extern void rotateArrayClockwise(std::vector<int>v, int k);
extern void rotateArrayOneLiner(std::vector<int>, int k);

#endif
