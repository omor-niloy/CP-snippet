//i hate _____
#include<bits/stdc++.h>
using namespace std;

vector<int>arr;
const int N = 1e5;
const int k = log2(N) + 1;
int table[N + 1][k + 1], lg[N + 1];

void build(int n){
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i>>1] + 1;

    for (int i = 0; i < n; i++) {
        table[i][0] = arr[i];
    }
    for (int j = 1; j <= k; j++) {
        for (int i = 0; i + (1<<j) <= n; i++) {
            table[i][j] = min(table[i][j-1], table[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int l, int r){
    int j = lg[r-l+1];
    int ans = min(table[l][j], table[r-(1<<j)+1][j]);
    return ans;
}


int main()
{
    int n;
    cin >> n;
    arr = vector<int> (n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    build(n);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
}

// https://www.spoj.com/problems/RMQSQ/