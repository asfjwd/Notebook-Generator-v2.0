/**
 * Author: nirjhor
 * Date: 2021-08-11
 * License: CC0
 * Source: folklore
 * Description: Computes $P^{-1},\exp(P),\log(P)$ fast. $P^k=\exp(k\log P)$. Log is in-place. Value of $n$ should be power of $2$ larger than polynomial size.
 * Time: $O(n \log n)$
 * Status: somewhat-tested
 */
#pragma once
void prepare (int n);
void ntt (int *a, int n, int dir = 0);
// TAKE THE ABOVE PARTS FROM NumberTheoreticTransform.h
void multiply (int *a, int *b, int n) {
  prepare(n << 1), ntt(a, n << 1), ntt(b, n << 1);
  for (int i = 0; i < n << 1; ++i) a[i] = (ll) a[i] * b[i] % MOD;
  ntt(a, n << 1, 1); for (int i = n; i < n << 1; ++i) a[i] = 0;
}
static int f[N], g[N], h[N]; int inv[N]; // 1/i modulo MOD
void inverse (int *a, int n, int *b) {
  b[0] = inv[a[0]], b[1] = 0;
  for (int m = 2; m <= n; m <<= 1) {
    for (int i = 0; i < m; ++i) f[i] = a[i], f[i + m] = b[i + m] = 0;
    prepare(m << 1), ntt(f, m << 1), ntt(b, m << 1);
    for (int i = 0; i < m << 1; ++i) b[i] = (ll) b[i] * (MOD + 2 - (ll) b[i] * f[i] % MOD) % MOD;
    ntt(b, m << 1, 1); for (int i = m; i < m << 1; ++i) b[i] = 0;
  }
}
void log (int *a, int n) {
  inverse(a, n, g);
  for (int i = 0; i + 1 < n; ++i) a[i] = (i + 1LL) * a[i + 1] % MOD;
  multiply(a, g, n); 
  for (int i = n - 1; i; --i) a[i] = (ll) a[i - 1] * inv[i] % MOD;
  a[0] = 0;
}
void exp (int *a, int n, int *b) {
  b[0] = 1, b[1] = 0;
  for (int m = 2; m <= n; m <<= 1) {
    for (int i = 0; i < m; ++i) h[i] = b[i];
    log(h, m);
    for (int i = 0; i < m; ++i) h[i] = (a[i] - h[i] + MOD) % MOD;
    ++h[0], h[0] %= MOD;
    for (int i = m; i < m << 1; ++i) b[i] = h[i] = 0;
    multiply(b, h, m); for (int i = m; i < m << 1; ++i) b[i] = 0;
  }
}
