/**
 * Author: internet
 * Date: 2021-08-11
 * License: CC0
 * Source: dunno
 * Description: Modulo $M$ should be of form $c\cdot 2^n+1$ where $2^n$ is bigger than maximum polynomial size under computation (or as a result). $G$ should be a primitive root of $M$. To find $G$, factor $M-1$ and get the distinct primes $p_i$. If $G^{(M-1)/p_i}\neq 1\pmod M$ for each $p_i$ then $G$ is a valid root. Try all $G$ until a hit is found (usually found very quick). 
 * Time: O(N \log N)
 * Status: somewhat tested
 */
#pragma once
const int G = 3;
const int MOD = 998244353;
const int N = (1 << 20) + 5;
int rev[N], w[N], inv_n;

// G = primitive_root(MOD)
int primitive_root (int p) {
  vector <int> factor;
  int tmp = p - 1;
  for (int i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) {
      factor.emplace_back(i);
      while (tmp % i == 0) tmp /= i;  
    }
  }
  if (tmp != 1) factor.emplace_back(tmp);
  for (int root = 1; ; ++root) {
    bool flag = true;
    for (int i = 0; i < (int) factor.size(); ++i) {
      if (bigMod(root, (p - 1) / factor[i], p) == 1) {
        flag = false; break;
      }
    }
    if (flag) return root;
  }
}
void prepare (int n) { 
  int sz = abs(31 - __builtin_clz(n));
  int r = bigMod(G, (MOD - 1) / n, MOD); 
  inv_n = bigMod(n, MOD - 2, MOD), w[0] = w[n] = 1; 
  for (int i = 1; i < n; ++i) w[i] = (ll) w[i - 1] * r % MOD;
  for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
}
void ntt (int *a, int n, int dir) { 
  for (int i = 1; i < n - 1; ++i) { 
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int m = 2; m <= n; m <<= 1) {
    for (int i = 0; i < n; i += m) {
      for (int j = 0; j < (m >> 1); ++j) {
        int &u = a[i + j], &v = a[i + j + (m >> 1)]; 
        int t = (ll) v * w[dir ? n - n / m * j : n / m * j] % MOD;
        v = u - t < 0 ? u - t + MOD : u - t;
        u = u + t >= MOD ? u + t - MOD : u + t;
      }
    }
  } if (dir) for (int i = 0; i < n; ++i) a[i] = (ll) a[i] * inv_n % MOD;
}
int f_a[N], f_b[N];
vector <int> multiply (vector <int> a, vector <int> b) {
  int sz = 1, n = a.size(), m = b.size();
  while (sz < n + m - 1) sz <<= 1; prepare(sz);
  for (int i = 0; i < sz; ++i) f_a[i] = i < n ? a[i] : 0;
  for (int i = 0; i < sz; ++i) f_b[i] = i < m ? b[i] : 0;
  ntt(f_a, sz, 0); ntt(f_b, sz, 0);
  for (int i = 0; i < sz; ++i) f_a[i] = (ll) f_a[i] * f_b[i] % MOD;
  ntt(f_a, sz, 1); return vector <int> (f_a, f_a + n + m - 1);
}
