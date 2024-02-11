vector<int> suffixArray(string s){
    s.pb(''); // put a lowest character which won't appear in s
    int n = s.size();
    vector<int>sa(n), uc(n);
    {
        vector<ii>ta(n); // tmp array for sorting
        for (int i = 0; i < n; i++) ta[i] = {s[i],i};
        sort(ta.begin(),ta.end());
        for (int i = 0; i < n; i++) sa[i] = ta[i].second;
        uc[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (ta[i].first == ta[i-1].first) uc[sa[i]] = uc[sa[i-1]];
            else uc[sa[i]] = uc[sa[i-1]] + 1;
        }
    }
    int k = 0;
    while ((1<<k) < n) {
        vector< pair<pair<int, int>, int>> ta(n);
        for (int i = 0; i < n; i++)
            ta[i] = {{uc[i], uc[(i + (1<<k)) % n]}, i};
        sort(ta.begin(),ta.end());
        for (int i = 0; i < n; i++) sa[i] = ta[i].second;
        uc[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (ta[i].first == ta[i-1].first) uc[sa[i]] = uc[sa[i-1]];
            else uc[sa[i]] = uc[sa[i-1]] + 1;
        }
        k++;
    }
    return sa;
}
