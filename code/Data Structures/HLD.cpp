/**
 * Description: Transforms tree paths into ranges with $O(\log N)$ overhead. Subtree of v corresponds to segment [in[v], out[v]) and the path from v to the last vertex in ascending heavy path from v (which is nxt[v]) will be [in[nxt[v]], in[v]]. Use appropriate DS to handle stuff.
 * Time: O(\log^2 N)
 */
const int N = 1e5 + 5;
const int LOGN = 18;

int par[N], nxt[N], in[N], out[N], sz[N], h[N];
int n, timer;
vector<int> g[N];

void dfs_sz(int u = 0, int p = -1, int d = 0) {
  par[u] = p, sz[u] = 1, h[u] = d;
  for (auto &v : g[u]) {
    if (v ^ p) {
      dfs_sz(v, u, d + 1);
      sz[u] += sz[v];
      if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
  }
}

void dfs_hld(int u = 0, int p = -1) {
  update(1, 0, n - 1, timer, val[u]);
  in[u] = timer++;
  for (auto v : g[u]) {
    if (v ^ p) {
      nxt[v] = (v == g[u][0]) ? nxt[u] : v;
      dfs_hld(v, u);
    }
  }
  out[u] = timer;
}

int hld_query(int u, int v) {
  int ret = 0;
  while (nxt[u] != nxt[v]) {
    if (h[nxt[u]] > h[nxt[v]]) swap(u, v);
    ret = merge(ret, query(1, 0, n - 1, in[nxt[v]], in[v]));
    v = par[nxt[v]];
  }
  if (h[u] > h[v]) swap(u, v);
  //in[u] -> in[u] + 1 in case of edge values
  ret = merge(ret, query(1, 0, n - 1, in[u], in[v]));
  return ret;
}