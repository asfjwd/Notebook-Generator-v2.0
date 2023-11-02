/**
 * Author: ayon
 * Date: 2022-05-10
 * License: CC0
 * Description: Find hashes of a tree when rooted at each possible node (unrooted tree isomorphism test). 
 * Time: $O(n)$
 * Status: tested
 */
#pragma once
const int sz = 2e5+5, mod = 1e9+7;
ll hval[sz], h[sz], dp[sz], rans[sz];
void dfs(vector <vector<int>> &g, int u = 0, int p = -1, int val = 0, int up = 0) {
   vector <int> cv, cht;       // current child values & heights
   if(u > 0) {    
      /// !!! 0 AS ROOT, CHANGE TO u > 1 IF NEEDED !!! ///
      cv.push_back(val);
      cht.push_back(up);
   }
   for(int v : g[u]) if(v - p) {
      cv.push_back(dp[v]);
      cht.push_back(1 + h[v]);
   }
   sort(cht.begin(), cht.end(), greater<int>());
   if(cv.size() > 1) {
      ll ret[] = {1, 1};     // for biggest & 2nd-biggest heights
      for(int i=0; i<2; i++)
         for(int value : cv)
            ret[i] = ret[i] * (hval[cht[i]] + value) % mod;

      rans[u] = ret[0];   // biggest is hash for this root
      for(int v : g[u]) if(v - p) {
         int id = 1;
         if(cht[0] - 1 - h[v]) id = 0;   // v is not on the biggest height path
         val = ret[id] * invmod((hval[cht[id]] + dp[v]) % mod) % mod;
         /* division of v subtree hash value */
         dfs(g, v, u, val, cht[id] + 1);
      }
   }
   else if(cv.size()) {  // Leaf node u OR vertex - 1 has only one child
      if(!up) val = 1;
      else val = (val + hval[up]) % mod;
      rans[u] = val;
      for(int v : g[u]) if(v - p) dfs(g, v, u, val, up + 1);
   }
}
ll get(vector <vector<int>> &g, int u = 0, int p = -1) {
   h[u] = 0;
   vector <ll> childs;
   for(int v : g[u]) if(v - p) {
      childs.push_back(get(g, v, u));
      h[u] = max(h[u], 1 + h[v]);
   }
   ll ret = 1;
   for(int value : childs) ret = ret * (hval[h[u]] + value) % mod;
   return dp[u] = ret;
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() { // can remove the g as param, can change to 1-index, multi-test works, no further change 
      get(g); dfs(g);
      tree[k] = rans[0] = dp[0];
      // rans[i] = tree hash with i as root
}

