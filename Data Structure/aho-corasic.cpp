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

struct node{
    node* nxt[26];
    node* suffix_link;
    node* output_link;
    int cnt[26];
    int ends;
    node(){
        for (int i = 0; i < 26; i++) {
            nxt[i] = nullptr;
            cnt[i] = 0;
        }
        suffix_link = nullptr;
        output_link = nullptr;
        ends = -1;
    }
};

struct AhoCorasic{
    node* root;
    char ch;
    int k;
    AhoCorasic(){
        root = new node();
        ch = 'a';
        k = 26;
    }

    void build_suffix_output_links(){
        root->suffix_link = root;
        queue<node*> q;
        for (int i = 0; i < k; i++) if (root->nxt[i]) {
            q.push(root->nxt[i]);
            root->nxt[i]->suffix_link = root;
        }
        while (!q.empty()) {
            node* cur = q.front();
            q.pop();
            for (int i = 0; i < k; i++) if (cur->nxt[i]) {
                node* tmp = cur->suffix_link;
                while ((!tmp->nxt[i]) && tmp != root) tmp = tmp->suffix_link;

                if (tmp->nxt[i]) cur->nxt[i]->suffix_link = tmp->nxt[i];
                else cur->nxt[i]->suffix_link = root;
                q.push(cur->nxt[i]);
            }
            if (cur->suffix_link->ends >= 0) cur->output_link = cur->suffix_link;
            else cur->output_link = cur->suffix_link->output_link;
        }
    }

    void insert(string &words, int index){
        node* cur = root;
        for (int i = 0; i < words.size(); i++) {
            if (!cur->nxt[words[i] - ch]) {
                cur->nxt[words[i] - ch] = new node();
            }
            cur->cnt[words[i] - ch]++;
            cur = cur->nxt[words[i] - ch];
        }
        cur->ends = index;
    }

    void build(vector<string>&s){
        for (int i = 0; i < s.size(); i++)
            insert(s[i], i);
        build_suffix_output_links();
    }

    void search_end_indexs(string &text, vector<vector<int>>&arr){
        node* cur = root;
        int i = 0;
        while (i < text.size()) {
            if (cur->nxt[text[i] - ch]) {
                cur = cur->nxt[text[i] - ch];
                if (cur->ends >= 0) arr[cur->ends].pb(i);
                node* mol = cur->output_link;
                while (mol) {
                    arr[mol->ends].pb(i);
                    mol = mol->output_link;
                }
            } else {
                while (cur != root && (!cur->nxt[text[i] - ch]))
                    cur = cur->suffix_link;
                if (cur->nxt[text[i] - ch]) i--;
            }
            i++;
        }
    }

    void dfs(node* cur){
        if (cur -> nxt[0]) dfs(cur -> nxt[0]);
        if (cur -> nxt[1]) dfs(cur -> nxt[1]);
    }

    void call_dfs(){
        dfs(root);
    }

    void selfDestruct(node* cur) {
        for(int i = 0; i < k; i++){
            if(cur->nxt[i]) selfDestruct(cur->nxt[i]);
        }
        delete cur;
    }
    ~AhoCorasic() {
        selfDestruct(root);
    }
};

void promod(){
    string text;
    cin >> text;

    int n;
    cin >> n;
    vector<int>freq(n);
    vector<string>s(n);
    for (int i = 0; i < n; i++) {
        cin >> freq[i] >> s[i];
    }

    AhoCorasic T;
    T.build(s);
    vector<vector<int>>arr(n);
    T.search_end_indexs(text, arr);

    for (int i = 0; i < n; i++) {
        int ans = 1e9;
        int sz = arr[i].size();
        for (int j = freq[i] - 1; j < sz; j++) {
            int tmp = arr[i][j] - arr[i][j - freq[i] + 1] + s[i].size();
            ans = min(ans, tmp);
        }
        if (ans == 1e9) ans = -1;
        cout << ans << endl;
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

// https://codeforces.com/contest/963/problem/D
