//i hate _____
#include<bits/stdc++.h>

using namespace std;

#define int long long int
#define lll __int128_t
#define ld long double
#define pb push_back
#define ii pair<int,int>
#define endl "\n"
double pi = 2 * acos(0.0) ;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rng(x,y) uniform_int_distribution<int>(x,y)(rng)

void print_array_randomly(vector<int>a){
    vector<int>res;
    while(a.size()) {
        int x = rng(0, a.size()-1);
        cout << a[x] << " ";
        // res.pb(a[x]);
        a.erase(a.begin()+x);
    }
    cout << endl;
    // return res;
}

void _permutation(int n){
    vector<int>a;
    for (int i = 1; i <= n; i++) a.pb(i);
    print_array_randomly(a);
}

void promod(){
    
}

int32_t main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "w", stdout);
    #endif

    int test_cases = 1;
    // cout << test_cases << endl;
    // cin >> test_cases;

    for (int tc = 1 ; tc <= test_cases ; tc++){

        //cout << "Case " << tc << ": ";
        // cout << tc << endl;
        promod();
        //printf("Case %d: %.10lf\n",tc,ans);

    }

    return 0;
}
/*
    problems are the sign of life
*/


// ./slow.sh t ex2 ex1 100
// chmod +x slow.sh