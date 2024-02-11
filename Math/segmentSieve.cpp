//i hate _____
#include<bits/stdc++.h>
#define ll long long int
#define pb push_back
using namespace std;

vector<int>primes,ans;
 
void sieve(int n){
    vector<char>isprime(n,true);
    for (int i = 2; i < n; i++) {
        if (isprime[i]) {
            primes.pb(i); ans.pb(i);
            for (int j = i*i; j < n; j += i)
                isprime[j] = false;
        }
    }
}
 
void seg_sieve(int l, int r){
    vector<char>block(10000,true);
    for (auto p : primes) {
        int x = (l+p-1)/p;
        int j = (x*p) - l;
        for (;j < 10000; j += p)
            block[j] = false;
    }
    for (int i = 0; i < 10000; i++) {
        if (block[i])
            ans.pb(l+i);
    }
}
 
void gen1e8(){
    sieve(10000);
    for (int i = 10000; i < 100000000; i += 10000){
        seg_sieve(i,i+10000-1);
    }
    cout << ans.size() << endl;
}

int main()
{
    gen1e8();
}