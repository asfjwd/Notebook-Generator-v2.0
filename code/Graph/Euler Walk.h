/**
 * Author: nirjhor
 * Date: 2021-08-11
 * License: CC0
 * Source: folklore
 * Description: On directed graph, circuit (or edge disjoint directed cycles) exists iff each node satisfies in\_degree = out\_degree and the graph is strongly connected; path exists iff at most one vertex has in\_degree - out\_degree = 1 and at most one vertex has out\_degree - in\_degree = 1 and all other vertices have in\_degree = out\_degree, and graph is weakly connected. Push edge ID in circ if edges needed.
 * Time: O(V + E)
 * Status: tested
 */
#pragma once
bitset <N> bad;
vector <int> g[N], circ;
int n, m, deg[N], U[N], V[N];
void hierholzer (int src) {
  if (!deg[src]) return;
  vector <int> path;
  path.push_back(src);
  int at = src;
  while (!path.empty()) {
    if (deg[at]) {
      path.push_back(at);
      while (bad[g[at].back()]) g[at].pop_back();
      int e = g[at].back(), nxt = U[e] ^ at ^ V[e];
      bad[e] = 1, --deg[at], --deg[nxt], at = nxt;
    } else {
      circ.push_back(at);
      at = path.back(), path.pop_back();
    }
  } reverse(circ.begin(), circ.end());
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", U + i, V + i);
    g[U[i]].push_back(i); 
    g[V[i]].push_back(i);
    ++deg[U[i]], ++deg[V[i]];
  }
  hierholzer(1); // run loop if not connected
  for (int x : circ) printf("%d ", x); puts("");
}
