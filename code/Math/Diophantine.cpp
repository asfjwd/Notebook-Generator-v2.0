/**
 * Description: For any solution $(x_0, y_0)$, all solutions are of the form $x = x_0 + k \frac{b}{g}, y = y_0 + k \frac{a}{g}$
*/

// (d, x, y) s.t ax + by = gcd(a, b) = d
tuple<int, int, int> exgcd(int a, int b) {
  if(b == 0) return {a, 1, 0};
  auto [d, _x, _y] = exgcd(b, a % b);
  int x = _y, y = _x - (a / b) * _y;
  return {d, x, y};
}

// returns (true, x, y) if solution exists
// returns (false, 0, 0) otherwise
tuple<bool, int, int> diophantine(int a, int b, int c) {
  auto [d, _x, _y] = exgcd(a, b);
 
  if(c % d) return {false, 0, 0};
  else {
    int x = (c / d) * _x, y = (c / d) * _y;
    return {true, x, y};
  }
}