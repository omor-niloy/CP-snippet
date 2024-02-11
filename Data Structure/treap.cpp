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

const int mx = 4e5 + 5;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct node{
    int key, prior, cnt;
    node *l, *r;
    node(int id){
        l = r = nullptr;
        key = id;
        prior = rnd();
        cnt = 1;
    }
};

struct treap{
    node *root;
    treap() {
        root = nullptr;
    }
    void split(node *t, int pos, node *&l, node *&r){
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (t->key <= pos) {
            if (t->r) t->cnt -= t->r->cnt;
            split(t->r, pos, l, r);
            if (l) t->cnt += l->cnt;
            t->r = l; l = t;
        } else {
            if (t->l) t->cnt -= t->l->cnt;
            split(t->l, pos, l, r);
            if (r) t->cnt += r->cnt;
            t->l = r; r = t;
        }
    }

    node* merge(node *l, node *r){
        if ((!l) || (!r)) return l ? l : r;
        if (l->prior < r->prior) {
            if(l->r) l->cnt -= l->r->cnt;
            l->r = merge(l->r, r);
            if (l->r) l->cnt += l->r->cnt;
            return l;
        }
        if (r->l) r->cnt -= r->l->cnt;
        r->l = merge(l, r->l);
        r->cnt += r->l->cnt;
        return r;
    }

    void insert(int id){
        node *l, *r;
        split(root, id, l, r);
        root = merge(merge(l, new node(id)), r);
    }

    node* merge_treap(node *l, node *r) {
        if ((!l) || (!r)) return l ? l : r;
        if(l->prior < r->prior) swap(l, r);
        node *L, *R;
        split(r, l->key, L, R);
        if (l->r) l->cnt -= l->r->cnt;
        if (l->l) l->cnt -= l->l->cnt;
        l->r = merge_treap(l->r, R);
        l->l = merge_treap(L, l->l);
        if (l->r) l->cnt += l->r->cnt;
        if (l->l) l->cnt += l->l->cnt;
        return l;
    }

    void combine(node *x) { //combine with another treap
        root = merge_treap(root, x);
    }

    node* erase(int L, int R) {
        node *l, *r, *mid, *mr;
        split(root, L - 1, l, r);
        split(r, R, mid, mr);
        root = merge(l, mr);
        return mid;
    }

    int dfs(node *t, int val){
        if (!t) return 0;
        if (t->key >= val)
            return dfs(t->l, val);
        int r = 1;
        if (t->l) r += t->l->cnt;
        r += dfs(t->r, val);
        return r;
    }
    int query(int val){
        return dfs(root, val);
    }
};

void solve(){
    int n, q;
    cin >> n >> q;
    vector<int>arr(n);
    map<int,int>mp; int id = 1;
    treap T[mx];
    for (int i = 0; i < n; i++) {
        int in; cin >> in;
        if (!mp[in]) mp[in] = id++;
        T[mp[in]].insert(i);
        arr[i] = mp[in];
    }
    while (q--) {
        int i, v;
        cin >> i >> v;
        node *p = T[arr[i]].erase(i, i);
        if (!mp[v]) mp[v] = id++;
        int ni = mp[v];
        arr[i] = ni;
        T[ni].combine(p);
        int ans = T[ni].query(i);
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
        solve();
        //printf("Case %d: %.10lf\n",tc,ans);

    }

    return 0;
}
/*
    problems are the sign of life
*/
// https://www.spoj.com/problems/ADACROP/
