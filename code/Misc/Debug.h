template<typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) res += ", ";
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
void debug_out() { cerr << endl; }
template<typename Head, typename ... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H) << " |";
  debug_out(T ...);
}
#define debug(...) clog << "Line : " << __LINE__ << " : [" <<#__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)