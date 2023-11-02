// Returns minimum non-negative  st a^x = b (mod m) or -1 if doesn't exist
int discreteLog(int a, int b, int M) {
  a %= M, b %= M;
  int k = 1, add = 0, g;
  while ((g = gcd(a, M)) > 1) {
    if (b == k) return add;
    if (b % g) return -1;
    b /= g, M /= g, ++add;
    k = (1LL * k * a / g) % M;
  }

  int RT = sqrt(M) + 1, aRT = 1;
  for (int i = 0; i < RT; i++) aRT = (aRT * 1LL * a) % M;

  gp_hash_table<int, int> vals;
  for (int i = 0, cur = b; i <= RT; i++) {
    vals[cur] = i;
    cur = (cur * 1LL * a)%M;
  }

  for (int i = 1, cur = k; i <= M / RT + 1; i++) {
    cur = (cur * 1LL * aRT) % M;
    if (vals.find(cur) != vals.end())
      return RT * i - vals[cur] + add;
  }
  return -1;
}