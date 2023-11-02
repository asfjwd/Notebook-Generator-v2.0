// Pragmas
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3,unroll-loops,Ofast,fast-math")
#pragma GCC target("avx,avx2,fma")

// Custom Priority Queue
std::priority_queue<int, std::vector<int>, std::greater<int>> Q;   // increasing

//gp hash table https://codeforces.com/blog/entry/60737
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
  int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<key, int, chash> table;

//bitset
BS._Find_first()
BS._Find_next(x) //Return first set bit after xth bit, x on failure

//Gray Code, G(0) = 000, G(1) = 001, G(2) = 011, G(3) = 010
inline int g(int n) { return n ^ (n >> 1); }

//Inverse Gray Code
int rev_g(int g) {
  int n = 0;
  for ( ; g; g >>= 1) n ^= g;
  return n;
}

// Only for non-negative integers
// Returns the immediate next number with same count of one bits, -1 on failure
long long hakmemItem175(long long n) {
  if (!n) return -1;
  long long x = (n & -n);
  long long left = (x + n);
  long long right = ((n ^ left) / x) >> 2;
  long long res = (left | right);
  return res;
}

// Returns the immediate previous number with same count of one bits, -1 on failure
long long lol(long long n) {
  if (n < 2) return -1;
  long long res = ~hakmemItem175(~n);
  return (!res) ? -1 : res;
}

int __builtin_clz(int x);// number of leading zero
int __builtin_ctz(int x);// number of trailing zero
int __builtin_clzll(long long x);// number of leading zero
int __builtin_ctzll(long long x);// number of trailing zero
int __builtin_popcount(int x);// number of 1-bits in x
int __builtin_popcountll(long long x);// number of 1-bits in x
lsb(n): (n & -n); // last bit (smallest)
floor(log2(n)): 31 - __builtin_clz(n | 1);
floor(log2(n)): 63 - __builtin_clzll(n | 1);

// compute next perm. ex) 00111, 01011, 01101, 01110, 10011, 10101..
long long next_perm(long long v){
  long long t = v | (v-1);
  return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}