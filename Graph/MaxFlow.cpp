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
 
using F = long long;
F infFlow = 1LL << 61;
struct MaxFlow{
    struct edge{
        int u, v;
        F cap, flow;
        edge(int _u = 0, int _v = 0, F _c = 0){
            u = _u; v = _v, cap = _c; flow = 0;
        }
 
        F flowfrom(int node) {return (node == u) ? flow : -flow;}
        int other(int node) {return (node == u) ? v : u;}
        F rescap(int node) {return (node == u) ? cap - flow : flow;}
        void sendflow(int node, F f) {flow += (node == u) ? f : -f;}
    };
 
    vector<edge> E;
    vector<vector<int>> adj;
    vector<int>level, vis, ptr;
    int clk;
 
    MaxFlow(int n){
        adj.resize(n + 1);
        level.resize(n + 1);
        vis.resize(n + 1);
        ptr.resize(n + 1);
        clk = 0;
    }
 
    void addEdge(int u, int v, F c){
        adj[u].push_back(E.size());
        adj[v].push_back(E.size());
        E.push_back({u, v, c});
    }
 
    bool bfs(int s, int t){
        clk++;
        queue<int>q;
        q.push(s);
        level[s] = 0;
        vis[s] = clk;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            if (node == t) break;
            ptr[node] = 0;
            for (auto it : adj[node]) {
                int nxt = E[it].other(node);
                if (vis[nxt] == clk || (!E[it].rescap(node))) continue;
                vis[nxt] = clk;
                level[nxt] = level[node] + 1;
                q.push(nxt);
            }
        }
        return vis[t] == clk;
    }
 
    F augment(int node, F flow, int t){
        if (node == t || flow == 0) return flow;
        for (int &i = ptr[node]; i < adj[node].size(); i++) {
            edge &e = E[adj[node][i]];
            int v = e.other(node);
            if (vis[v] != clk) continue;
            if (level[v] != level[node] + 1 || (!e.rescap(node))) continue;
 
            F sentflow = augment(v, min(flow, e.rescap(node)), t);
            if (sentflow) {
                e.sendflow(node, sentflow);
                return sentflow;
            }
        }
        level[node] = -1;
        return 0;
    }
 
    F maxflow(int s, int t){
        F res = 0, tmp;
        while (bfs(s, t))
            while (tmp = augment(s, infFlow, t))
                res += tmp;
        return res;
    }
    /*
    bool dfs(int node, int t, vector<vector<int>>&ans, vector<int>&tmp) {
        tmp.pb(node);
        // cout << tmp << endl;
        if (node == t) {
            ans.pb(tmp);
            tmp.pop_back();
            return true;
        }
        bool now = false;
        for (int &i = ptr[node]; i < adj[node].size() && (!now);) {
            edge e = E[adj[node][i++]];
            int v = e.other(node);
            if (e.flowfrom(node) > 0) {
                now |= dfs(v, t, ans, tmp);
            }
        }
        tmp.pop_back();
        return now;
    }
    */
};
 
void promod(){
    int n, m;
    cin >> n >> m;
    MaxFlow mf(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        mf.addEdge(u, v, 1);
        mf.addEdge(v, u, 1);
    }
    long long ans = mf.maxflow(1, n);
    cout << ans << endl;
    /*
    // mincut edges
    mf.bfs(1, n);
    for (int i = 0; i < mf.E.size(); i++) {
        int u = mf.E[i].u, v = mf.E[i].v;
        if (mf.vis[u] == mf.clk && mf.vis[v] != mf.clk) {
            cout << u << " " << v << endl;
        }
    }
    */

    /*
    // matching
    // source 0 -> sink (n + m + 1)
    for (int i = 0; i < mf.E.size(); i++) {
        if (mf.E[i].u >= 1 && mf.E[i].u <= n && (!mf.E[i].rescap(mf.E[i].u)))
            cout << mf.E[i].u << " " << mf.E[i].v - n << endl;
    }
    */

    /*
    // disjoint node
    vector<vector<int>> path;
    vector<int> tmp;
    for (int i = 1; i <= n; i++)
        mf.ptr[i] = 0;
    for (int i = 0; i < ans; i++)
        mf.dfs(1, n, path, tmp);
    */
}
 
int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);
 
    int test_cases = 1;
    // cin >> test_cases;
 
    for (int tc = 1 ; tc <= test_cases ; tc++){
 
        //cout << "Case " << tc << ": ";
        promod();
        //printf("Case %d: %.10lf\n",tc,ans);
 
    }
 
    return 0;
}
/*
    problems are the sign of life
*/
 
// mincut edges
// disjoint edge/node
// matching
// min vertex cover
// mincost flow
// fesiable flow
// min no path cover