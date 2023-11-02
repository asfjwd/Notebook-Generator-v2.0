/**
 * Description: RMQ, point updates.
 * Time: O(\log N)
 */
namespace PersistentTree {
  ll t[M];
  int L[M], R[M], root[N], arr[N], ptr = 0;
  void update(int x, int y, int p, int v, int b = 1, int e = n) {
    if (b == e) return void(t[y] = v);
    int mid = b + e >> 1;
    if (p <= mid) R[y] = R[x], L[y] = ++ptr, update(L[x], L[y], p, v, b, mid);
    else L[y] = L[x], R[y] = ++ptr, update(R[x], R[y], p, v, mid + 1, e);
    t[y] = min(t[L[y]], t[R[y]]);
  }
  void init() {
    for (int i = 1; i <= n; ++i) arr[i] = INT_MAX;
    root[0] = 0, t[0] = INF;
    for (int i = 1; i <= n; ++i) {
      root[i] = root[i - 1];
      for (auto & [r, w] : who[i]) if (w < arr[r]) {
          int new_root = ++ptr;
          arr[r] = w, update(root[i], new_root, r, w);
          root[i] = new_root;
        }
    }
  }
  ll query(int u, int l, int r, int b = 1, int e = n) {
    if (!u or b > r or e < l) return INF;
    if (b >= l and e <= r) return t[u];
    int mid = b + e >> 1;
    return min(query(L[u], l, r, b, mid), query(R[u], l, r, mid + 1, e));
  }
  inline ll getMin(int l, int r) {
    return query(root[l], r, n);
  }
}
