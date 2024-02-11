//i hate _____
#include<bits/stdc++.h>
#define ll long long int
#define pb push_back
using namespace std;

const int mx = 1e6;
const ll mod = 1e9 + 7;
vector<ll>f;
 
void fact(){
    ll k = 1; f.pb(1);
    for (int i=1;i<=mx;i++){
        k*=i; k%=mod;
        f.pb(k);
    }
}

ll power(ll x, ll y,ll p) {
    ll res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

ll modInverse(ll n,ll p) {
    return power(n, p - 2, p);
}
 
ll ncr(ll n,ll r){
    if (n < r) return 0;
    if (r == 0) return 1;
    ll p = mod;
    return (f[n] * modInverse(f[r], p) % p
            * modInverse(f[n - r], p) % p)
           % p;
}

int main()
{
    fact();
}