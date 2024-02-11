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

ll ans = 0;

struct node{
    node* nxt[26];
    // int cnt[26], len[26];
    int cnt, len;
    int ends = 0;
    node(){
        for (int i = 0; i < 26; i++) {
            nxt[i] = nullptr;
            // cnt[i] = 0;
            // len[i] = 0;
        }
        cnt = 0; len = 0;
        ends = 0;
    }
};

struct Trie{
    node* root;
    char ch;
    Trie(){
        root = new node();
        ch = 'a';
    }

    void insert(string &words){
        node* cur = root;
        for (int i = 0; i < words.size(); i++) {
            if (!cur->nxt[words[i] - ch]) {
                cur->nxt[words[i] - ch] = new node();
            }
            // cur->cnt[words[i] - ch]++;
            // cur->len[words[i] - ch] += (words.size() - i) ;
            cur = cur->nxt[words[i] - ch];
            cur->cnt++;
            cur->len += (words.size() - i);
        }
        cur->ends++;
    }

    void call_dfs(string &s){
        node* cur = root;
        int ix = 0, n = s.size();
        while (true) {
            ans += 1LL * (n - ix) * cur->ends;
            if (ix >= n) {
                for (int i = 0; i < 26; i++) if(cur->nxt[i]) {
                    ans += (ll)cur->nxt[i]->len;
                }
                return;
            }
            for (int i = 0; i < 26; i++) {
                if (cur->nxt[i] && (s[ix] - 'a') != i){
                    ans += (ll)cur->nxt[i]->len;
                    ans += 1LL * cur->nxt[i]->cnt*(n - ix);
                }
            }
            if (cur->nxt[s[ix] - ch]) {
                cur = cur->nxt[s[ix] - ch];
                ix ++;
            } else {
                break;
            }
        }
    }
    
    void selfDestruct(node* cur) {
        for(int i = 0; i < 26; i++){
            if(cur->nxt[i]) selfDestruct(cur->nxt[i]);
        }
        delete cur;
    }
    ~Trie() {
        selfDestruct(root);
    }
}T;

void promod(){
    int n;
    cin >> n;
    vector<string>s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        T.insert(s[i]);
        reverse(s[i].begin(), s[i].end());
    }
    for (int i = 0; i < n; i++) {
        T.call_dfs(s[i]);
    }
    cout << ans << endl;
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
 
 // https://codeforces.com/contest/1902/problem/E
