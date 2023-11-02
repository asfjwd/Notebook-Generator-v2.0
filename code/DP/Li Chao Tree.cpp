/**
 * Author: internet
 * Date: 2021-08-10
 * License: CC0
 * Source: yosupo judge
 * Description: Add line segment, query minimum $y$ at some $x$. Provide list of all query $x$ points to constructor (offline solution). Use add\_segment(line, $l, r$) to add a line segment $y=ax+b$ defined by $x\in [l,r)$. Use query($x$) to get min at $x$. 
 * Time: O(\log n)
 * Status: not-tested
 */
#pragma once
struct LiChaoTree {
  using Line = pair <ll, ll>;
  const ll linf = numeric_limits<ll>::max();
  int n; vector<ll> xl; vector<Line> dat;
  LiChaoTree(const vector<ll>& _xl) : xl(_xl) {
    n = 1; while(n < xl.size())n <<= 1;
    xl.resize(n,xl.back());
    dat = vector<Line>(2 * n - 1,Line(0,linf));
  }
  ll eval(Line f,ll x){return f.first * x + f.second;}
  void _add_line(Line f,int k,int l,int r){
    while (l != r) {
      int m = (l + r) / 2;
      ll lx = xl[l],mx = xl[m],rx = xl[r - 1];
      Line &g = dat[k];
      if(eval(f,lx) < eval(g,lx) && eval(f,rx) < eval(g,rx)){
        g = f; return;
      }
      if(eval(f,lx) >= eval(g,lx) && eval(f,rx) >= eval(g,rx))return;
      if(eval(f,mx) < eval(g,mx))swap(f,g);
      if(eval(f,lx) < eval(g,lx)) k = k * 2 + 1, r = m;
      else k = k * 2 + 2, l = m;
    }
  }
  void add_line(Line f){_add_line(f,0,0,n);}
  void add_segment(Line f,ll lx,ll rx){
    int l = lower_bound(xl.begin(), xl.end(),lx) - xl.begin();
    int r = lower_bound(xl.begin(), xl.end(),rx) - xl.begin();
    int a0 = l, b0 = r, sz = 1; l += n;r += n;
    while(l < r){
      if(r & 1) r--, b0 -= sz, _add_line(f,r - 1,b0,b0 + sz);
      if(l & 1) _add_line(f,l - 1,a0,a0 + sz), l++, a0 += sz;
      l >>= 1, r >>= 1, sz <<= 1;
    }
  }
  ll query(ll x) {
    int i = lower_bound(xl.begin(), xl.end(),x) - xl.begin();
    i += n - 1; ll res = eval(dat[i],x);
    while (i) i = (i - 1) / 2, res = min(res, eval(dat[i], x));
    return res;
  }
};
