/**
 * Description:
 * \begin{itemize}[noitemsep]
 *   \item If m is decreasing:
 *     \begin{itemize}
 *       \item[--] for min : bad(s-3, s-2, s-1), x increasing
 *       \item[--] for max : bad(s-1, s-2, s-3), x decreasing
 *     \end{itemize}
 *   \item If m is increasing:
 *     \begin{itemize}
 *       \item[--] for max : bad(s-3, s-2, s-1), x increasing
 *       \item[--] for min : bad(s-1, s-2, s-3), x decreasing
 *     \end{itemize}
 *   \item If x isn't monotonic, then do Ternary Search or keep intersections and do binary search
 * \end{itemize}
 */
struct CHT {
  vector<ll> m, b;
  int ptr = 0;
  bool bad(int l1, int l2, int l3) { // returns intersect(l1, l3) <= intersect(l1, l2)
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2]) <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]);
  }

  void insert_line(ll _m, ll _b) {
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while (s >= 3 && bad(s - 1, s - 2, s - 3)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
    }
  }
  ll f(int i, ll x) { return m[i] * x + b[i]; }

  ll eval(ll x) {
    if (ptr >= m.size()) ptr = m.size() - 1;
    while (ptr < m.size() - 1 && f(ptr + 1, x) > f(ptr, x)) ptr++;
    return f(ptr, x);
  }
};