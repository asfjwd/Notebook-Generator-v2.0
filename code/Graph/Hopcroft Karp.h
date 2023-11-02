/**
 * Author: internet
 * Date: 2021-08-11
 * License: CC0
 * Source: nirjhor library
 * Description: Fast bipartite matching. Clear match[] first. Graph is normal, undirected.
 * Time: O(E\sqrt{V})
 * Status: stress-tested by MinimumVertexCover, and tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 */
#pragma once
bool bfs() {
  queue <int> q; 
  for (int i = 1; i <= n; ++i) {
    if (!match[i]) dist[i] = 0, q.emplace(i);
    else dist[i] = INF;
  } 
  dist[0] = INF;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (!u) continue; 
    for (int v : g[u]) {
      if (dist[match[v]] == INF) {
        dist[match[v]] = dist[u] + 1, q.emplace(match[v]);
      }
    }
  } return dist[0] != INF;    
}
bool dfs (int u) {
  if (!u) return 1; 
  for (int v : g[u]) {
    if (dist[match[v]] == dist[u] + 1 and dfs(match[v])) {
      match[u] = v, match[v] = u; return 1; 
    } 
  } dist[u] = INF; return 0;
}
int hopcroftKarp() {
  int ret = 0; 
  while (bfs()) {
    for (int i = 1; i <= n; ++i) {
      ret += !match[i] and dfs(i);
    }
  } return ret;
}
