//i hate _____
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int k = log2(n) + 1;
    int table[n+1][k+1];
    for (int j = 1; j <= k; j++) {
        for (int i = 0; i + (1<<j) <= n; i++) {
            table[i][j] = max(table[i][j-1],table[i+(1<<(j-1))][j-1]);
        }
    }
}