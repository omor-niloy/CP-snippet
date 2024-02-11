const int mx = 1e5 + 5;
vector<int>g[mx], rg[mx];
int vis[mx];
vector<int> tmp;
stack<int>st;

void dfs2(int node){
    vis[node] = 1;
    for (auto it : rg[node]) {
        if (!vis[it])
            dfs2(it);
    }
    tmp.pb(node);
}

void dfs(int node){
    vis[node] = 1;
    for (auto it : g[node]) {
        if (!vis[it])
            dfs(it);
    }
    st.push(node);
}

vector<vector<int>>get_scc(int n){
    for (int i = 1; i <= n; i++) vis[i] = 0;
    for (int i = 1; i <= n; i++) if (!vis[i])
        dfs(i);
    for (int i = 1; i <= n; i++) vis[i] = 0;
    vector<vector<int>>scc;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (vis[node]) continue;
        tmp.clear();
        dfs2(node);
        scc.pb(tmp);
    }
    return scc;
}
