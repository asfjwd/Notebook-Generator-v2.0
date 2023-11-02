/**
 * Author: ayon
 * Date: 2021-08-11
 * License: CC0
 * Source: Folklore
 * Description: A node $u$ is ancestor of node $v$ in the dominator tree if all the the paths from source to node $v$ contain node $u$. If a problem asks for edge disjoint paths, for every edge, take a new node $w$ and turn the  edge $(u \rightarrow v)$ to $(u \rightarrow w \rightarrow v)$ and find node disjoint path now. 1-based directed graph input. dtree is the edge list of the dominator tree. Clear everything at the start of each test case. Only the nodes reachable from source will be in the dominator tree. 
 * Time: construction $O(V+E)$
 * Status: tested
 */
#pragma once
vector <int> g[sz], rg[sz], dtree[sz], bucket[sz];
int sdom[sz], par[sz], dom[sz], dsu[sz], label[sz];
int arr[sz], rev[sz], ts, source;
void dfs(int u) {
   ts++; arr[u] = ts; rev[ts] = u;
   label[ts] = sdom[ts] = dsu[ts] = ts;
   for(int &v : g[u]) {
      if(!arr[v]) { dfs(v); par[arr[v]] = arr[u]; }
      rg[arr[v]].push_back(arr[u]);
   }
}
inline int root(int u, int x = 0) {
   if(u == dsu[u]) return x ? -1 : u;
   int v = root(dsu[u], x + 1);
   if(v < 0) return u;
   if(sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
   dsu[u] = v; return x ? v : label[u];
}
void build(int n) {
   dfs(source);
   for(int i=n; i; i--) {
      for(int j : rg[i]) sdom[i] = min(sdom[i],sdom[root(j)]);
      if(i > 1) bucket[sdom[i]].push_back(i);
      for(int w : bucket[i]) {
         int v = root(w);
         if(sdom[v] == sdom[w]) dom[w] = sdom[w];
         else dom[w] = v;
      } if(i > 1) dsu[i] = par[i];
   }
   for(int i=2; i<=n; i++) {
      int &dm = dom[i];
      if(dm ^ sdom[i]) dm = dom[dm];
      dtree[rev[i]].push_back(rev[dm]);
      dtree[rev[dm]].push_back(rev[i]);
   }
}
int main() {
  // input graph of n nodes in g[], assign "source" vertex
  ts = 0; build(n); // clear stuff before calling
}
