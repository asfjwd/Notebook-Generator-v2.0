struct Trie {
  const int L = 26; int N;
  vector< vector<int> > next;
  vector<int> cnt;

  Trie() : N(0) {node(); }

  int node() {
    next.emplace_back(L, 0);
    cnt.emplace_back();
    return N++;
  }
  //insert or delete
  void insert(const string &s, int a = 1){
    int u = 0, c;
    for (int i = 0; i < s.length(); i++) {
      c = s[i] - 'a';
      if(!next[u][c]) next[u][c] = node();
      cnt[u = next[u][c]] += a;
    }
  }
};