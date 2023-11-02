/**
 * Author: nirjhor
 * Date: 2021-08-11
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal subtree that contains all the nodes by adding all (at most $|S|-1$) pairwise LCAs and compressing edges. Tree is stored in virt[] with edge costs at cost[].
 * Time: $O(|S| \log |S|)$
 * Status: tested
 */
#pragma once
vector <int> g[N], virt[N], cost[N];
int n, m, ptr, h[N], in[N], stk[N];
void add_edge (int u, int v) {
  if (u == v) return;
  virt[u].emplace_back(v);
  virt[v].emplace_back(u);
  int w = abs(h[u] - h[v]);
  cost[u].emplace_back(w);
  cost[v].emplace_back(w);
}
void buildTree (vector <int> &nodes) {
  if (nodes.size() <= 1) return;
  sort(nodes.begin(), nodes.end(), [] (int x, int y) {return in[x] < in[y];});
  int root = get_lca(nodes[0], nodes.back()), sz = nodes.size();
  ptr = 0, stk[ptr++] = root;
  for (int i = 0; i < sz; ++i) {
    int u = nodes[i], lca = get_lca(u, stk[ptr - 1]);
    if (lca == stk[ptr - 1]) {
      stk[ptr++] = u;
    } else {
      while (ptr > 1 and h[stk[ptr - 2]] >= h[lca]) {
        add_edge(stk[ptr - 2], stk[ptr - 1]), --ptr;
      }
      if (stk[ptr - 1] != lca) {
        add_edge(lca, stk[--ptr]);
        stk[ptr++] = lca, nodes.emplace_back(lca);
      } stk[ptr++] = u;
    }
  }
  if (find(nodes.begin(), nodes.end(), root) == nodes.end()) nodes.emplace_back(root);
  for (int j = 0; j + 1 < ptr; ++j) add_edge(stk[j], stk[j + 1]);
}
int main() {
  cin >> m; vector <int> nodes(m);
  for (int i = 0; i < m; ++i) cin >> nodes[i];
  buildTree(nodes);
}
