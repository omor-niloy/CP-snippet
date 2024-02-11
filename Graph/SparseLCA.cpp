//i hate _____
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int mx = 1e5 + 5;
const int k = 18;
vector<int>g[mx];
int parrent[mx][k];
vector<int>height(mx);

void dfs(int node, int h){
    height[node] = h;
    for (auto it : g[node]) {
        if (!height[it]) {
            dfs(it,h+1);
            parrent[it][0] = node;
        }
    }
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

int main()
{
    int root, h = 0;
    dfs(root,h);
}