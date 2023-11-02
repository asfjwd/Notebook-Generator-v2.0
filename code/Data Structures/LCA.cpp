const int N = 1e5 + 5;
const int LOGN = 18;

int h[N], table[LOGN][N];
std::vector<int> g[N];

void dfs(int u = 0, int p = -1, int d = 0){
  table[0][u] = p, h[u] = d;
  for(int i = 1; i < LOGN; i++){
    if(table[i - 1][u] ^ -1) {
      table[i][u] = table[i - 1][table[i - 1][u]];
    }
    else table[i][u] = -1;
  }
  for(auto v : g[u]){
    if(v ^ p) dfs(v, u, d + 1);
  }
}

int get_lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  for (int i = LOGN - 1; i >= 0; i--) {
    if (h[u] - (1 << i) >= h[v]) u = table[i][u];
  }
  if (u == v) return u;
  for (int i = LOGN - 1; i >= 0; i--) {
    if (table[i][u] != table[i][v]) {
      u = table[i][u]; v = table[i][v];
    }
  }
  return table[0][u];
}
 