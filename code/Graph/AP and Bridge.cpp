#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
vector<int> g[N];
int vis[N], low[N], cut[N], now = 0, n, m;

void dfs(int u, int p) {
  low[u] = vis[u] = ++now; int ch = 0; 
  for(int v : g[u]){
    if(v ^ p) { 
      if(vis[v]) low[u] = min(low[u], vis[v]); 
      else {
        ch++; dfs(v, u); 
        low[u] = min(low[u], low[v]); 
        if(p + 1 && low[v] >= vis[u]) cut[u] = 1;
        if(low[v] > vis[u]) {
          printf("Bridge %d -- %d\n", u, v);
        }
      }
    }
  } if(p == -1 && ch > 1) cut[u] = 1;
}

void fuck() {
  memset(vis, 0, sizeof vis);
  memset(low, 0, sizeof low); 
  memset(cut, 0, sizeof cut); 
  now = 0; 
  for(int i = 0; i < n; i++) {
    if(!vis[i]) dfs(i, -1); 
  }
}