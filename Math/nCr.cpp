//i hate _____
#include<bits/stdc++.h>
#define ll long long int
#define pb push_back
using namespace std;

const int mx = 1e6;
const int mod = 1e9 + 7;
vector<int>f;
 
void fact(){
    int k = 1; f.pb(1);
    for (int i=1;i<=mx;i++){
        k = (1LL * k * i) % mod;
        f.pb(k);
    }
}

int power(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (y & 1) r = (1LL * r * a) % mod;
        b >>= 1;
        a = (1LL * a * a) % mod;
    }
    return r;
}

int modInverse(int n) {
    return power(n, mod - 2);
}
 
int ncr(int n, int r){
    if (n < r) return 0;
    if (r == 0) return 1;
    return (f[n] * modInverse(f[r]) % mod
            * modInverse(f[n - r]) % mod)
           % mod;
}

int main()
{
    fact();
}
