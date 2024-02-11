mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rng(x,y) uniform_int_distribution<int>(x,y)(rng)
 
typedef uint64_t ull;
struct H {
    ull x; H(ull _x=0) : x(_x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)rng(1e10,1e12); // (order ~ 3e9; random also ok)
 
struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(str.size()+1), pw(ha) {
        pw[0] = 1;
        for (int i = 0; i < str.size(); i++)
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
    void insert(char a){
        ha.pb(ha.back()*C + a);
        pw.pb(pw.back()*C);
    }
};  
 
vector<H> getHashes(string& str, int length) {
    if (str.size() < length) return {};
    H h = 0, pw = 1;
    for (int i = 0; i < length; i++)
        h = h * C + str[i], pw = pw * C;
    vector<H> ret = {h};
    for (int i = length; i < str.size(); i++) {
        ret.push_back(h = h * C + str[i] - pw * str[i-length]);
    }
    return ret;
}
 
H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}

void solve(){
    string s;
    HashInterval h(s);
    H val = h.hashInterval(i, i+len); // query
}
