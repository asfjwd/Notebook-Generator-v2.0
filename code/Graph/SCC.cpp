// col[u] stores the component number u belongs to

vector<int> adj[N], trans[N]; 
int col[n], vis[n], idx = 0, n, m; 
stack<int> st;

void dfs(int u) {
  vis[u] = 1;
  for(int v : adj[u]) if(!vis[v]) dfs(v);
  st.push(u);
}
void dfs2(int u) {
  col[u] = idx;
  for(int v : trans[u]) if(!col[v]) dfs2(v);
}
void scc() {
  for(int i = 1; i <= n; i++){
    if(!vis[i]) dfs(i);
  }
  while(!st.empty()) {
    int u = st.top(); st.pop();
    if(col[u]) continue; 
    idx++; dfs2(u); 
  } 
}