/**
 * Description: RMQ. Iterative, 0-indexed, point update, query $[l, r)$.
 * Time: O(\log N)
 */
const int N = 500010;
int n, a[N], tree[N << 1];
void init() {
  for (int i = 0; i < n; ++i) tree[n + i] = a[i];
  for (int i = n - 1; i >= 0; --i) {
    tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
  }
}
void update(int p, int v) {
  for (tree[p += n] = v; p > 1; p >>= 1) {
    tree[p >> 1] = min(tree[p], tree[p ^ 1]);
  }
}
int query(int l, int r) {
  int ret = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = min(ret, tree[l++]);
    if (r & 1) ret = min(ret, tree[--r]);
  } return ret;
}
