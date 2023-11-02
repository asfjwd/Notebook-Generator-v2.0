/**
 * Author: nirjhor
 * Date: 2021-08-11
 * License: CC0
 * Description: all path problem to paths through root problem with $O(\log n)$ overhead.
 * Time: $O(n \log n)$
 * Status: tested
 */
#pragma once
bool bad[N]; ll ans, h[N];
vector <pair <int, ll>> g[N];
int n, sub[N], flat[N], ptr, in[N], out[N];
void trav (int u, int par = -1) {
  sub[u] = 1;
  for (auto [v, w] : g[u]) if (!bad[v] and v != par) {
    trav(v, u); sub[u] += sub[v];
  }
}
int getCentroid (int u, int tot, int par = -1) {
  for (auto [v, w] : g[u]) if (!bad[v] and v != par and sub[v] > tot / 2) {
    return getCentroid(v, tot, u);
  } return u;
}
void dfs (int u, int par = -1, ll far = 0) {
  flat[++ptr] = u, in[u] = ptr, h[u] = far;
  for (auto [v, w] : g[u]) if (!bad[v] and v != par) {
    dfs(v, u, far + w);
  } out[u] = ptr;
}
void decompose (int u = 1) {
  trav(u);
  int cen = getCentroid(u, sub[u]);
  ptr = 0; dfs(cen);
  for (auto [u, w] : g[cen]) if (!bad[u]) {
    for (int i = in[u]; i <= out[u]; ++i) {
      int v = flat[i];
      // update ans with v
    }
    for (int i = in[u]; i <= out[u]; ++i) {
      int v = flat[i];
      // insert v in data structure
    }
  }
  bad[cen] = 1;
  for (auto [v, w] : g[cen]) if (!bad[v]) decompose(v);
}
int main() {
  // input graph
  decompose();
}
