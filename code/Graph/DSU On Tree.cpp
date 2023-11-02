/**
 * Author: nirjhor
 * Date: 2021-08-11
 * License: CC0
 * Description: DSU on tree. Count number of vertices of color $c$ in a subtree.
 * Time: $O(n \log n)$
 * Status: tested
 */
#pragma once
int cnt[N];
void dfs (int u, int par, bool keep) {
  int mx = -1, bigChild = -1;
  for (auto v : g[u])
    if (v != par and sz[v] > mx)
      mx = sz[v], bigChild = v;
  for (auto v : g[u]) if (v != par and v != bigChild) {
      dfs(v, u, 0); // small child, clear them before exiting
  }
  if (bigChild != -1)
    dfs(bigChild, u, 1); // don't clear big child
  for (auto v : g[u]) if (v != par and v != bigChild) {
    for (int i = in[v]; i <= out[v]; ++i) ++cnt[col[flat[i]]];
  }
  ++cnt[col[u]];
  // now cnt[c] is the number of vertices in subtree of vertex u with color c, answer queries
  if (!keep) { // clear this subtree
    for (int i = in[u]; i <= out[u]; ++i) --cnt[col[flat[i]]];
  }
}
