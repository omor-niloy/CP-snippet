//i hate _____
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long int
#define lll __int128_t
#define ld long double
#define pb push_back
#define ii pair<int,int>
#define endl "\n"
double pi = 2 * acos(0.0) ;

template<typename T>
ostream& operator<<(ostream &os, const vector<T> &v) {
    os << '{';
    for (const auto &x : v) os << " " << x;
        return os << '}';
}

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

struct graph{
    int node, cost;
};

const int mx = 1e5 + 5;
const int k = 18;
vector<graph>g[mx];
vector<int>under(mx), height(mx), pw(mx), arr;
int parrent[mx][k];
int chainparrent[mx], chainhead[mx], chainno[mx], position[mx];
int pos, nchain;

void HLD(int node, int pa){
    // arr[pos] = node;
    arr.pb(node);
    position[node] = pos++;
    chainno[node] = nchain;
    int sc = -1, m = 0;
    for (auto it : g[node]) {
        if (it.node == pa) continue;
        if (under[it.node] > m) {
            m = under[it.node];
            sc = it.node;
        }
    }
    if (sc == -1) return;
    HLD(sc, node);
    for (auto it : g[node]) {
        if (it.node == sc || it.node == pa) continue;
        nchain++;
        chainparrent[nchain] = node;
        chainhead[nchain] = it.node;
        HLD(it.node, node);
    }
}

void dfs(int node, int h){
    height[node] = h;
    int z = 1;
    for (auto it : g[node]) {
        if (!height[it.node]) {
            dfs(it.node,h+1);
            parrent[it.node][0] = node;
            pw[it.node] = it.cost; arr.pb(pw[node]);
            z += under[it.node];
        }
    }
    under[node] = z;
}

void buildSparseTable(int n){
    for (int j = 1; j < k; j++) for (int i = 1; i <= n; i++) 
        if (parrent[i][j-1] != -1) {
            parrent[i][j] = parrent[parrent[i][j-1]][j-1];
            //ma[i][j] = max(ma[i][j-1], ma[parrent[i][j-1]][j-1]);
        }
}

int LCA(int u, int v){
    if (height[u] > height[v]) swap(u,v);
    int dif = height[v] - height[u];
    for (int i = k-1; i >= 0; i--)
        if (dif&(1<<i)) {
            v = parrent[v][i];
        }
    if (u == v) return u;
    for (int i = k-1; i >= 0; i--) {
        if (parrent[u][i] != parrent[v][i]) {
            u = parrent[u][i];
            v = parrent[v][i];
        }
    }
    return parrent[u][0];
}

void init(int n){
    dfs(1, 1);
    buildSparseTable(n);
    nchain = 1; pos = 0;
    chainparrent[nchain] = -1;
    chainhead[nchain] = 1;
    arr.clear();
    pw[1] = 0;
    HLD(1, -1);
}

vector<int>st;
vector<int>stnode(mx);
int sz;

int build(int node, int l, int r){
    if (l == r) {
        stnode[arr[l]] = node;
        return st[node] = arr[l];
    }
    int mid = (l+r)>>1;
    int s1 = build((node<<1)+1,l,mid);
    int s2 = build((node<<1)+2,mid+1,r);
    return st[node] = (pw[s1] > pw[s2]) ? s1 : s2;
}

int update(int node, int l, int r, int x){
    if (l > x || r < x || l == r) return st[node];
    int mid = (l+r) >> 1;
    int s1 = update((node<<1)+1, l, mid, x);
    int s2 = update((node<<1)+2,mid+1,r,x);
    return st[node] = (pw[s1] > pw[s2]) ? s1 : s2;
}

int query(int node, int l, int r, int l1, int r1){
    if (l > r1 || r < l1) return -1;
    if (l >= l1 && r <= r1) return st[node];
    int mid = (l+r)>>1;
    int s1 = query((node<<1)+1, l , mid, l1, r1);
    int s2 = query((node<<1)+2, mid+1, r, l1, r1);
    if (s1 == -1) return s2;
    if (s2 == -1) return s1;
    return (pw[s1] > pw[s2]) ? s1 : s2;
}

int treequery(int u, int v){
    int res = -1e9;
    while (chainno[u] != chainno[v]) {
        int t = chainhead[chainno[u]];
        res = max(res, pw[query(0,0,sz-1, position[t], position[u])]);
        u = parrent[t][0];
    }
    if (u == v) return res;
    res = max(res, pw[query(0,0,sz-1, position[v]+1,position[u])]);
    return res;
}

void solve(){
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        for (int j = 0; j < k; j++)
            parrent[i][j] = -1;
        height[i] = 0;
    }
    vector<ii>p;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].pb({v,w}); g[v].pb({u,w});
        p.pb({u, v});
    }
    init(n);
    sz = arr.size();
    st.resize(4*sz);
    build(0,0,sz-1);
    // cout << arr << endl;

    string s;
    while (cin >> s) {
        if (s == "DONE") break;
        int x, y; cin >> x >> y;
        if (s == "CHANGE") {
            int u = p[x-1].first, v = p[x-1].second;
            if (height[u] > height[v]) swap(u, v);
            pw[v] = y;
            update(0,0,sz-1,position[v]);
            continue;
        }
        int lca = LCA(x, y);
        int ans = max(treequery(x, lca), treequery(y, lca));
        cout << ans << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int test_cases = 1;
    cin >> test_cases;

    for (int tc = 1 ; tc <= test_cases ; tc++){

        //cout << "Case " << tc << ": ";
        solve();
        //printf("Case %d: %.10lf\n",tc,ans);

    }

    return 0;
}
/*
    problems are the sign of life
*/

// https://www.spoj.com/problems/QTREE/
