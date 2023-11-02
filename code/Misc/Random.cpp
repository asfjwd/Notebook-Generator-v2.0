// mt19937_64 in case of 64 bit
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
shuffle(v.begin(), v.end(), rng);
ll rnd(ll l, ll r) {
  return uniform_int_distribution<ll>(l, r) (rng);
}



