#include <bits/stdc++.h>
using namespace std;


/*
字符串 哈希
双哈希 减少碰撞概率
空间复杂度 O(n)
查询时间 O(1)


*/
class StringHash
{
    #define ull unsigned long long
public:
    StringHash(string _s) : s(_s) {
        n = s.size();
        xp = vector<ull>(n + 2);
        H = vector<ull>(n + 2);
        xp2 = vector<ull>(n + 2);
        H2 = vector<ull>(n + 2);
        initHash(H, xp, seed);
        initHash(H2, xp2, seed2);
    } 
    pair<ull, ull> Hash(int pos, int len) {
        return make_pair(H[pos] - H[pos + len] * xp[len], H2[pos] - H2[pos + len] * xp2[len] );
    }
    ~StringHash() {
        xp.clear(); H.clear();
        xp2.clear(); H2.clear();
    }
private:
    string s;
    int n;
    /*
    备选种子
    131，233，2333， 13331，19260817 
    */
    static const ull seed = 137;
    static const ull seed2 = 19260817;
    vector<ull> xp, xp2, H, H2;
    void initHash(vector<ull>& H, vector<ull>& xp, ull seed) {
        H[n] = 0; xp[0] = 1;
        for(int i = n - 1; i >= 0; -- i)  H[i] = H[i + 1] * seed + (s[i] - 'a' + 1);
        for(int i = 1; i <= n; ++ i) xp[i] = xp[i - 1] * seed;
    }
};
class Solution {
public:
    int longestDecomposition(string text) {
        int ans = 0;
        int n = text.size();
        StringHash s(text);
        int st = 0, ed = n - 1;
        for(int l = st, r = ed; l < r; ++ l, -- r) {
            int len = l - st + 1;
            if(s.Hash(st, len) == s.Hash(r, len)) {
                st = l + 1; ed = r - 1;
                ans += 2;
            }
        }
        ans += (st <= ed);
        return ans;
    }
};
int main()
{
    string s; cin >> s;
    Solution sol;
    cout << sol.longestDecomposition(s) << endl;
    return 0;
}


/*

ghiabcdefhelloadamhelloabcdefghi
elvtoelvto
*/