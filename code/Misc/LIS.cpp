const int inf = 1e9;
vector<int> LIS(vector<int> a, int n){
  vector<int> d(n + 1, inf);
	for (int i = 0; i < n; i++) {
		*lower_bound(d.begin(), d.end(), a[i]) = a[i];
	}
  d.resize(lower_bound(d.begin(), d.end(), inf) - d.begin());
  return d;
}