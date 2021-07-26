#include "allheaders.h"
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
using namespace std;
const int INF = 1e9;


//time complexity => O(32)
int divideIntegers(int A, int B) {
    if (A == INT_MIN and B == -1) return INT_MAX;
    if (A == INT_MIN and B == 1) return INT_MIN;
    unsigned a = abs(A), b = abs(B);
    int res = 0;
    for (int x = 31; x >= 0; x--) {
        if (a >> x >= b) {
            a = a - (b << x);
            res += (1 << x);
        }
    }
    return (A > 0) == (B > 0) ? res : -res;
}
