/**
 * Description:
 *  \begin{itemize}[noitemsep]
 *    \item Number of permutations of n elements with k disjoint cycles = Str1(n,k) = (n-1) * Str1(n-1,k) + Str1(n-1,k-1).
 *    \item n! = Sum(Str1(n,k)) (for all 0 <= k <= n).
 *    \item Ways to partition n labelled objects into k unlabelled subsets = Str2(n,k) = k * Str2(n-1,k) + Str2(n-1,k-1).
 *    \item Parity of Str2(n,k) : ( (n-k) & Floor((k-1)/2) ) == 0).
 *    Ways to partition n labelled objects into k unlabelled subsets, with each subset containing at least r elements: SR(n,k) = k * SR(n-1,k) + C(n-1,r-1) * SR(n-r,k-1).
 *    \item Number of ways to partition n labelled objects 1,2,3, ... n into k non-empty subsets so that for any integers i and j in a given subset |i-j| >= d: Str2(n-d+1, k-d+1), n >= k >= d.
 *  \end{itemize}
 */

NTT ntt(mod);
vector<ll> v[MAX];

//Stirling1 (n,k) = co-eff of x^k in x*(x+1)*(x+2)*....(x+n-1)
int Stirling1(int n, int r) {
  int nn = 1;
  while (nn < n) nn <<= 1;

  for (int i = 0; i < n; ++i) {v[i].push_back(i); v[i].push_back(1);}
  for (int i = n; i < nn; ++i) v[i].push_back(1);

  for (int j = nn; j > 1; j >>= 1) {
    int hn = j >> 1;
    for (int i = 0; i < hn; ++i) ntt.multiply(v[i], v[i + hn], v[i]);
  }
  return v[0][r];
}

NTT ntt(mod);
vector<ll> a, b, res;

//Stirling2 (n,k) = co-eff of x^k in product of polynomials A & B
//where A(i) = (-1)^i / i!  and B(i) = i^n / i!
int Stirling2(int n, int r) {
  a.resize(n + 1); b.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    a[i] = invfct[i];
    if (i % 2 == 1) a[i] = mod - a[i];
  }

  for (int i = 0; i <= n; i++) {
    b[i] = bigMod(i, n, mod);
    b[i] = (b[i] * invfct[i]) % mod;
  }

  NTT ntt(mod);
  ntt.multiply(a, b, res);
  return res[r];
}