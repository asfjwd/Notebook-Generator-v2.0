struct OnlineConvolution {
  vector<int> a, b, c;
  int k;
  OnlineConvolution(int n): a(n), b(n), c(n), k(0) {}
  // poly c = poly a * poly b
  // add a[i] = x and b[i] = y and it will return c[i]
  int extend(int i, int x, int y) {
  	assert(i == k);
    a[k] = x; b[k] = y;
    int s = k + 2;
    for (int w = 1; s % w == 0 && w < s; w <<= 1) {
      for (int ri = 0; ri < 2; ri++) {
        if (ri == 0 || w * 2 != s) {
          vector<int> f(w), g(w);
          for (int i = 0; i < w; i++) f[i] = a[w - 1 + i], g[i] = b[k - w + 1 + i];
          f = multiply(f, g);
          for (int i = 0, j = k; i < f.size() && j < c.size(); i++, j++) {
            c[j] += f[i];
            if (c[j] >= MOD) c[j] -= MOD;
          }
        }
        swap(a, b);
      }
    }
    return c[k++];
  }
};

int main() {
  int n = 5;
  OnlineConvolution oc(n);
  vector<int> f(n + 1), g(n);
  for(int i = 0; i < n; i++) g[i] = n - i;

  // f[0] = 1
  // f[i] = f[j] * g[k] s.t j + k = i - 1

  f[0] = 1;
  for(int i = 1; i <= n; i++) {
    oc.extend(i - 1, f[i - 1], g[i - 1]);
    f[i] = oc.c[i - 1];
  }
}