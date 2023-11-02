/**
 * Author: nirjhor
 * Date: 2021-08-11
 * Source: nirjhor library
 * Description: Pattern matching -- call run function. Do DP on DAG for number of different substrings (= different paths) or total length of different substrings. Lexicographically $k$th substring is $k$th path from root. Min rotation is smallest $|S|$ length path on automaton of $S+S$. Number of occurrence for a node -- mark non-clone nodes with $1$ then do $\text{cnt}[\text{link}[u]] += \text{cnt}[u]$. Occurrence position -- maintain firstPos (maybe lastPos too?) for each endpos set. Shortest non-appearing string -- DP on DAG, $\text{DP}[u] = 1$ if there's no transition with a character, $1+\min{\text{DP}[v]}$ otherwise. Longest common substring of two strings $S,T$ -- construct automaton $S$, run through $T$, and climb up the suffix links of automaton until a transition is found through next character of $T$. Do similar stuff for multiple strings.   
 * Time: $O(n \log n)$, linear if array used
 * Status: stress-tested a bit
 */
#pragma once
char s[N], p[N];
map <char, int> to[N << 1]; // use array maybe?
int len[N << 1], link[N << 1], sz, last;
inline void init() {
  len[0] = 0, link[0] = -1, sz = 1, last = 0, to[0].clear();
}
void feed (char c) {
  int cur = sz++, p = last;
  len[cur] = len[last] + 1, link[cur] = 0, to[cur].clear();
  while (~p and !to[p].count(c)) to[p][c] = cur, p = link[p];
  if (~p) {
    int q = to[p][c];
    if (len[q] - len[p] - 1) {
      int r = sz++;
      len[r] = len[p] + 1, to[r] = to[q], link[r] = link[q];
      while (~p and to[p][c] == q) to[p][c] = r, p = link[p];
      link[q] = link[cur] = r; 
    } else link[cur] = q;
  } last = cur;
}
bool run() {
  int m = strlen(p);
  for (int i = 0, u = 0; i < m; ++i) {
    if (!to[u].count(p[i])) return 0;
    u = to[u][p[i]];
  } return 1;
}
int main() {
  init();
  for (int i = 0; i < n; ++i) feed(s[i]);
  run();
}
