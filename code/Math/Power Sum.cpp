ll ncr[N][N], S[N][N], B[N], d[N][N];
ll fact[N], inv[N];

ll powerSum(ll n, ll k) {
  ll ret = 0LL;
  for (int i = 0; i <= k + 1; ++i) {
    ret += d[k][i] * bigMod(n, i);
    ret %= MOD;
  }
  return ret;
}

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; ++i) { fact[i] = (fact[i - 1] * i) % MOD; }

  inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
  }

  S[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    S[i][0] = 0;
    for (int j = 1; j <= i; ++j) {
      S[i][j] = j * S[i - 1][j] + S[i - 1][j - 1];
      S[i][j] %= MOD;
    }
  }
  for (int i = 1; i < N; ++i) {
    ncr[i][0] = ncr[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      ncr[i][j] = ncr[i - 1][j] + ncr[i - 1][j - 1];
      ncr[i][j] %= MOD;
    }
  }
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j <= i; ++j) {
      B[i] += ((j & 1) ? -1 : 1) * ((fact[j] * S[i][j]) % MOD)
              * inv[j + 1];
      B[i] %= MOD;
    }
  }
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j <= i; ++j) {
      d[i][i + 1 - j] = (ncr[i + 1][j] * abs(B[j])) % MOD;
      d[i][i + 1 - j] *= inv[i + 1];
      d[i][i + 1 - j] %= MOD;
    }
  }
  d[0][0] = 1; // 0^0 = 1
}