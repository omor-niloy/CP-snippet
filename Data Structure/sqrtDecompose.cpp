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

struct SqrtDecomposition{
    int n;
    vector<vector<int>>block;
    vector<vector<int>>sort_block;
    SqrtDecomposition(vector<int>arr) {
        int N = (int)arr.size();
        n = ceil(sqrt(N));
        block = vector<vector<int>>(n);
        sort_block = vector<vector<int>>(n);
        for (int i = 0; i < N; i++) {
            int _i = i/n;
            block[_i].pb(arr[i]);
            sort_block[_i].pb(arr[i]);
        }
        for (int i = 0; i < n; i++) {
            sort(sort_block[i].begin(), sort_block[i].end());
        }
    }
    void update(int ix, int v){
        int _i = ix/n;
        block[_i][ix % n] = v;
        sort_block[_i] = block[_i];
        sort(sort_block[_i].begin(), sort_block[_i].end());
    }
    int query(int l, int r, int c){
        int ans = 0;
        for (int i = l; i <= r;) {
            int _i = i/n;
            if (i%n == 0 && i + n <= r + 1) {
                ans += sort_block[_i].end() - lower_bound(sort_block[_i].begin(), sort_block[_i].end(), c);
                i += n;
            } else {
                ans += block[_i][i % n] >= c;
                i++;
            }
        }
        return ans;
    }
};

void promod(){
    int n; cin >> n;
    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    SqrtDecomposition SD = SqrtDecomposition(arr);
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (!t) {
            int l, r, c; cin >> l >> r >> c;
            cout << SD.query(l-1, r-1, c) << endl;
        } else {
            int i, v; cin >> i >> v;
            SD.update(i-1, v);
        }
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

// https://www.spoj.com/problems/GIVEAWAY/
