/**
 * Description: Solves for $x \equiv a_i \pmod{m_i}$.
*/

ll normalize(ll x, ll mod) { 
  x %= mod;
  return (x < 0) ? x + mod : x;
}

pair<ll, ll> CRT(vector<ll> a, vector<ll> m) {
  int n = a.size();
  for(int i = 0; i < n; i++) normalize(a[i], m[i]);
  ll ans = a[0], lcm = m[0];
  for(int i = 1; i < n; i++) {
    auto [d, x1, y1] = exgcd(lcm, m[i]);
    if((a[i] - ans) % d) return {-1, -1};
    ans = normalize(ans + x1 * (a[i] - ans) / d % (m[i] / d) * lcm, lcm * m[i] / d);
    lcm = lcm * m[i] / d;
  }
  return {ans, lcm};
}