const ll is_query = -LLONG_MAX;
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line&rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line * s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    //may need to use __int128 instead of ld if supported
    return ld(x->b - y->b) * (z->m - y->m) >= ld(y->b - z->b) * (y->m - x->m);
  }
  void insert_line(ll m, ll b) {
    auto y = insert({ -m, -b }); //change here for max
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    y->succ = [ = ] { return next(y) == end() ? 0 : &*next(y); };
    while (y != begin() && bad(prev(y))) erase(prev(y));
    if (y != begin()) prev(y)->succ = [ = ] { return &*y; };
  }
  ll eval(ll x) {
    auto l = *lower_bound((Line) { x, is_query });
    return -(l.m * x + l.b); //change here for max
  }
} hull;