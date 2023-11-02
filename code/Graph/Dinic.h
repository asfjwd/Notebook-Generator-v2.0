/**
 * Author: internet
 * Date: 2021-08-11
 * License: CC0
 * Source: nirjhor library
 * Description: Lower bound on capacity -- create a supersource, a supersink. If $u\rightarrow v$ has a lower bound of $L$, give an edge from supersource to $v$ with capacity $L$. Give an edge from $u$ to supersink with capacity $L$. Give an edge from normal sink to normal source with capacity infinity. If max flow here is equal to $L$, then the lower bound can be satisfied. For minimum flow satisfying lower bounds, binary search on the capacity from normal sink to normal source (instead of assigning inf). For maximum flow satisfying bounds, just add another source to normal source and binary search on capacity.
 * Time: $O(V^2 E)$, (on unit graphs $O(E\sqrt V)$)
 * Status: stress-tested
 */
#pragma once
struct edge {
  int u, v; ll cap, flow;
  edge () {}
  edge (int u, int v, ll cap) : u(u), v(v), cap(cap), flow(0) {}
};
struct Dinic {
  int N; vector <edge> E;
  vector <vector <int>> g;
  vector <int> d, pt;
  Dinic (int N) : N(N), E(0), g(N), d(N), pt(N) {}
  void AddEdge (int u, int v, ll cap) {
    if (u ^ v) {
      E.emplace_back(u, v, cap);
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(v, u, 0);
      g[v].emplace_back(E.size() - 1);
    }
  }
  bool BFS (int S, int T) {
    queue <int> q({S});
    fill(d.begin(), d.end(), N + 1); d[S] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) break;
      for (int k : g[u]) {
        edge &e = E[k];
        if (e.flow < e.cap and d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1; q.emplace(e.v);
        }
      }
    } return d[T] != N + 1;
  }
  ll DFS (int u, int T, ll flow = -1) {
    if (u == T or flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      edge &e = E[g[u][i]];
      edge &oe = E[g[u][i] ^ 1];
      if (d[e.v] == d[e.u] + 1) {
        ll amt = e.cap - e.flow;
        if (flow != -1 and amt > flow) amt = flow;
        if (ll pushed = DFS(e.v, T, amt)) {
          e.flow += pushed; oe.flow -= pushed;
          return pushed;
        }
      }
    } return 0;
  }
  ll MaxFlow (int S, int T) {
    ll total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (ll flow = DFS(S, T)) total += flow;
    } return total;
  }
};
