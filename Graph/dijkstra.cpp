//i hate _____
#include<bits/stdc++.h>
using namespace std;

const int mx = 2e5;

struct graph{
    int node;
    int cost;
};

vector<graph>g[mx];
bool vis[mx];
int dis[mx];

class cmp{
    public:
        bool operator() (graph &A, graph &B) {
            if (A.cost > B.cost) return true;
            return false;
        }
};

void dijkstra(int source){
    priority_queue<graph, vector<graph>, cmp>pq;
    pq.push({source,0});
    while (!pq.empty()) {
        graph cur = pq.top();
        pq.pop();
        int node = cur.node; 
        int cost = cur.cost;
        if (vis[node]) continue;
        dis[node] = cost;
        vis[node] = true;
        for(int i=0;i<g[node].size();i++) {
            int nxt = g[node][i].node;
            int nxtc = g[node][i].cost;
            if (!vis[nxt]) {
                pq.push({nxt,nxtc+cost});
            }
        }
    }
}

int main()
{
    
}