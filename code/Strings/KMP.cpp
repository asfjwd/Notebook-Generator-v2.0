template<typename T>
vector<int> prefix_function(const T &s) {
  int n = (int)s.size();
  vector<int> p(n, 0);
  int k = 0;
  for (int i = 1; i < n; i++) {
    while (k > 0 && !(s[i] == s[k])) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    p[i] = k;
  }
  return p;
}

// Returns 0-indexed positions of occurrences of s in w
template<typename T>
vector<int> kmp_search(const T &s, const T &w) {
  int n = (int)s.size();
  int m = (int)w.size();
  const vector<int> p = prefix_function(s);
  assert(n >= 1 && (int) p.size() == n);
  vector<int> res;
  int k = 0;
  for (int i = 0; i < m; i++) {
    while (k > 0 && (k == n || !(w[i] == s[k]))) { k = p[k - 1]; }
    if (w[i] == s[k]) { k++; }
    if (k == n) { res.push_back(i - n + 1); }
  }
  return res;
}

template<typename T>
vector<vector<int>> prefix_function_automaton(const T &s, int alphabet_size, int smallest_alphabet) {
  int n = s.size();
  vector<int> pf = prefix_function(s);
  vector<vector<int>> automaton(n + 1, vector<int>(alphabet_size));
  for (int i = 0; i <= n; i++) {
    for (int c = 0; c < alphabet_size; c++) {
      if (i < n and s[i] == smallest_alphabet + c) {
        automaton[i][c] = i + 1;
      }
      else {
        automaton[i][c] = i == 0 ? 0 : automaton[pf[i - 1]][c];
      }
    }
  }
  return automaton;
}