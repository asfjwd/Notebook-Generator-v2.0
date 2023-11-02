ll sum(ll n){
  return n * (n - 1) >> 1;
}
// sum [(ai + b) / m] for 0 <= i < n
ll floorSumAP (ll a, ll b, ll m, ll n) {
  ll res = a / m * sum(n) + b / m * n;
  a %= m, b %= m; if (!a) return res;
  ll to = (n * a + b) / m;
  return res + (n - 1) * to - floorSumAP(m, m - 1 - b, a, to);
}
// sum (a + di) % m for 0 <= i < n
ll modSumAP (ll a, ll b, ll m, ll n) {
  b = ((b % m) + m) % m, a = ((a % m) + m) % m;
  return n * b + a * sum(n) - m * floorSumAP(a, b, m, n);
}