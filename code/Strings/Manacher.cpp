/**
 * Description: For each position in a string, computes p[0][i] = half length of longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Time: O(N)
 */
typedef vector<int> vi;
array<vi, 2> manacher(const string& s) {
  int n = s.length();
  array<vi, 2> p = { vi(n + 1), vi(n)};
  for (int z = 0; z < 2; z++) for (int i = 0, l = 0, r = 0; i < n; i++) {
    int t = r - i + !z;
    if (i < r) p[z][i] = min(t, p[z][l + t]);
    int L = i - p[z][i], R = i + p[z][i] - !z;
    while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
      p[z][i]++, L--, R++;
    if (R > r) l = L, r = R;
  }
  return p;
}