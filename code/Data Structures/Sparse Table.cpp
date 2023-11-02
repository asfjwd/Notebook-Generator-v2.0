/**
 * Description: Sparse table for fast RMQ.
 * Time: O(1)
 */
#pragma once
int a[sz], spar[20][sz];
int rmq(int l, int r) {    // 1 - index
  int h = 31 - __builtin_clz(r - l + 1);
  return min(spar[h][l], spar[h][r + 1 - (1 << h)]);
}
int main() {
  for (int i = 1; i <= n; i++) spar[0][i] = a[i];
  for (int h = 0; 2 << h <= n; h++) {
    for (int i = 1, j = i + (1 << h); i <= n; i++, j++) {
      int &w = spar[h + 1][i] = spar[h][i];
      if (j <= n) w = min(w, spar[h][j]);
    }
  }
}
