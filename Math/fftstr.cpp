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

// using cd = complex<double>;

// 
#define cd complex<double>

void fft(vector<cd> &a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * pi / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<cd> multiply(vector<cd> &a, vector<cd> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    return fa;
    // vector<int> result(n);
    // for (int i = 0; i < n; i++)
    //     result[i] = round(fa[i].real());
    // return result;
}

vector<cd> process_(string &s, string &t){
    int n = s.size();
    vector<cd> a, b;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') a.pb(0);
        else {
            double ang = 2.00 * pi * (s[i] - 'a') / 26.00;
            a.pb({cos(ang), sin(ang)});
        }
        if (t[i] == '?' || t[i] == '0') b.pb(0);
        else {
            double ang = 2.00 * pi * (t[i] - 'a') / 26.00;
            b.pb({cos(-ang), sin(-ang)});
        }
    }
    reverse(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        a.pb(a[i]);
        b.pb(0);
    }
    return multiply(a, b);
}

void promod(){
    int n, m;
    cin >> n >> m;
    vector<string>Pattern(n);
    for (int i = 0; i < n; i++)
        cin >> Pattern[i];
    int c, r;
    cin >> r >> c;
    vector<string>Text(r);
    for (int i = 0; i < r; i ++)
        cin >> Text[i];

    // make row
    string a, b;
    int sz = ceil((double)c/(double)m) + 1;
    for (int i = 0; i < max(n, r); i++) {
        int _i = i%n;
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < m; k++)
                a.pb(Pattern[_i][k]);
        }
    }
    for (int i = 0; i < max(n, r); i++) {
        for (int j = 0; j < sz*m; j++) {
            if (i < r && j < c) b.pb(Text[i][j]);
            else b.pb('0');
        }
    }
    //
    // cout << a << endl << b << endl;
    vector<cd>ans = process_(a, b);
    int jog = sz*m, suru = a.size() - 1;
    double no_question = 0;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
        if (Text[i][j] != '?')
            no_question++;
    }
    // cout << no_question << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0, _j = suru; j < m; j++, _j++) {
            if (abs(no_question - ans[_j].real()) < 0.001) cout << 1;
            else cout << 0;
        }
        cout << endl;
        suru += jog;
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
 
 // https://codeforces.com/contest/754/problem/E