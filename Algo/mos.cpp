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

const int mx = 1e6 + 5;
vector<int>arr, cnt(mx);
int N;
map<ii,int>ans;

bool cmp(ii a, ii b){
    if (a.first/N == b.first/N)
        return a.second < b.second;
    return a.first/N < b.first/N;
}

void mo_s_algorithm(vector<ii>p){
    sort(p.begin(), p.end(), cmp);
    int cur_l = 0, cur_r = -1;
    int c = 0;
    for (auto it : p) {
        while (cur_l > it.first) {
            cur_l--;
            cnt[arr[cur_l]]++;
            c += cnt[arr[cur_l]] == 1;
        }
        while (cur_r < it.second) {
            cur_r++;
            cnt[arr[cur_r]]++;
            c += cnt[arr[cur_r]] == 1;
        }
        while(cur_l < it.first) {
            c -= cnt[arr[cur_l]] == 1;
            cnt[arr[cur_l]]--;
            cur_l++;
        }
        while(cur_r > it.second) {
            c -= cnt[arr[cur_r]] == 1;
            cnt[arr[cur_r]]--;
            cur_r--;
        }
        ans[it] = c;
    }
}

void promod(){
    int n;
    cin >> n;
    arr = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int q;
    cin >> q;
    vector<ii>p(q);
    for (int i = 0; i < q; i++) {
        cin >> p[i].first >> p[i].second;
        p[i].first--; p[i].second--;
    }
    N = ceil(sqrt(n));
    mo_s_algorithm(p);
    for (auto it : p)
        cout << ans[it] << endl;
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

// https://www.spoj.com/problems/DQUERY/
