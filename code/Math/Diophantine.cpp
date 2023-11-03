/**
 * Description: For any solution $(x_0, y_0)$, all solutions are of the form $x = x_0 + k \frac{b}{g}, y = y_0 + k \frac{a}{g}$
*/

// (d, x, y) s.t ax + by = gcd(a, b) = d
tuple<ll, ll, ll> exgcd(ll a, ll b) {
  if(b == 0) return {a, 1, 0};
  auto [d, _x, _y] = exgcd(b, a % b);
  ll x = _y, y = _x - (a / b) * _y;
  return {d, x, y};
}

tuple<bool, ll, ll> diophantine(ll a, ll b, ll c) {
  auto [d, _x, _y] = exgcd(a, b);
  if(c % d) return {false, 0, 0};
  else {
    ll x = (c / d) * _x, y = (c / d) * _y;
    return {true, x, y};
  }
}

void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt) {
  x += cnt * b;
  y -= cnt * a;
}

// returns the number of solutions where x is in the range[minx, maxx] and y is in the range[miny, maxy]
ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny,ll maxy) {

  ll g = __gcd(a, b);
  auto [res, x, y] = diophantine(a, b, c);

  if (res == false) return 0;
  if (a == 0 and b == 0) {
    assert(c == 0);
    return 1LL * (maxx - minx + 1) * (maxy - miny + 1);
  }
  if (a == 0) {
    return (maxx - minx + 1) * (miny <= c / b and c / b <= maxy);
  }  
  if (b == 0) {
    return (maxy - miny + 1) * (minx <= c / a and c / a <= maxx);
  }
  a /= g, b /= g;
  ll sign_a = a > 0 ? +1 : -1;
  ll sign_b = b > 0 ? +1 : -1;
  shift_solution(x, y, a, b, (minx - x) / b);
  if (x < minx) shift_solution(x, y, a, b, sign_b);
  if (x > maxx) return 0;
  ll lx1 = x;
  shift_solution(x, y, a, b, (maxx - x) / b);
  if (x > maxx) shift_solution (x, y, a, b, -sign_b);
  ll rx1 = x;
  shift_solution(x, y, a, b, -(miny - y) / a);
  if (y < miny) shift_solution (x, y, a, b, -sign_a);
  if (y > maxy) return 0;
  ll lx2 = x;
  shift_solution(x, y, a, b, -(maxy - y) / a);
  if (y > maxy) shift_solution(x, y, a, b, sign_a);
  ll rx2 = x;
  if (lx2 > rx2) swap (lx2, rx2);
  ll lx = max(lx1, lx2);
  ll rx = min(rx1, rx2);
  if (lx > rx) return 0;
  return (rx - lx) / abs(b) + 1;
}