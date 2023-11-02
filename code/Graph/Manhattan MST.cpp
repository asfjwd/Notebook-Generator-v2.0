#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnionFind {
  vector<int> UF; int cnt; UnionFind(int N) : UF(N, -1), cnt(N) {}
  int find(int v) { return UF[v] < 0 ? v : UF[v] = find(UF[v]); }
  bool join(int v, int w) {
    if ((v = find(v)) == (w = find(w))) return false;
    if (UF[v] > UF[w]) swap(v, w);
    UF[v] += UF[w]; UF[w] = v; cnt--; return true;
  }
  bool connected(int v, int w) { return find(v) == find(w); }
  int getSize(int v) { return -UF[find(v)]; }
};

template <class T> struct KruskalMST {
  using Edge = tuple<int, int, T>;
  T mstWeight; vector<Edge> mstEdges; UnionFind uf;
  KruskalMST(int V, vector<Edge> edges) : mstWeight(), uf(V) {
    sort(edges.begin(), edges.end(), [&] (const Edge &a, const Edge &b) {
      return get<2>(a) < get<2>(b);
    });
    for (auto &&e : edges) {
      if (int(mstEdges.size()) >= V - 1) break;
      if (uf.join(get<0>(e), get<1>(e))) {
        mstEdges.push_back(e); mstWeight += get<2>(e);
      }
    }
  }
};

template <class T> struct ManhattanMST : public KruskalMST<T> {
  using Edge = typename KruskalMST<T>::Edge;
  static vector<Edge> generateCandidates(vector<pair<T, T>> P) {
    vector<int> id(P.size()); iota(id.begin(), id.end(), 0); vector<Edge> ret;
    ret.reserve(P.size() * 4); for (int h = 0; h < 4; h++) {
      sort(id.begin(), id.end(), [&] (int i, int j) {
        return P[i].first - P[j].first < P[j].second - P[i].second;
      });
      map<T, int> M; for (int i : id) {
        auto it = M.lower_bound(-P[i].second);
        for (; it != M.end(); it = M.erase(it)) {
          int j = it->second;
          T dx = P[i].first - P[j].first, dy = P[i].second - P[j].second;
          if (dy > dx) break;
          ret.emplace_back(i, j, dx + dy);
        }
        M[-P[i].second] = i;
      }
      for (auto &&p : P) {
        if (h % 2) p.first = -p.first;
        else swap(p.first, p.second);
      }
    }
    return ret;
  }
  ManhattanMST(const vector<pair<T, T>> &P)
      : KruskalMST<T>(P.size(), generateCandidates(P)) {}
};

int main() {
  int N; cin >> N;
  vector<pair<ll, ll>> P(N);
  for (auto &&p : P) cin >> p.first >> p.second;
  ManhattanMST mst(P);
  cout << mst.mstWeight << '\n';
  for (auto &&[v, w, weight] : mst.mstEdges) cout << v << ' ' << w << '\n';
  return 0;
}