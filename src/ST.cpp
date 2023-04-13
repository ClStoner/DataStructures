#include <bits/stdc++.h>
using namespace std;

/*
ST 表查询区间最值问题
空间复杂度 O(n log n)
时间复杂度： 建表 O(n log n)， 查询 O(1)
*/


class ST_MAX
{
public:
    ST_MAX(vector<int>& a) {
        int n = a.size();
        Logn[1] = 0;
        for(int i = 2; i <= n; ++ i) {
            Logn[i] = Logn[i>>1] + 1;
        }
        for(int i = 0; i < n; ++ i) st[i][0] = a[i];
        for(int j = 1; j <= logn; ++ j) {
            for(int i = 0; i + (1 << j) - 1 < n; ++ i) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    /*
        查询闭区间[l, r]中的最大值
    */
    int Query(int l, int r) {
        int k = Logn[r - l + 1];
        return max(st[l][k], st[r - (1 << k) + 1][k]);
    }
    static const int maxn = 1e4 + 10;
    static const int logn = 21;
    int Logn[maxn];
    int st[maxn][logn];

};
int gcd(int n, int m) {
    return m == 0 ? n : gcd(m, n % m);
}
class ST_GCD
{
public:
    ST_GCD(vector<int>& a) {
        int n = a.size();
        Logn[1] = 0;
        for(int i = 2; i <= n; ++ i) {
            Logn[i] = Logn[i >> 1] + 1;
        }
        for(int i = 0; i < n; ++ i) st[i][0] = a[i];
        for(int j = 1; j <= logn; ++ j) {
            for(int i = 0; i + (1 << j) - 1 < n; ++ i) {
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int Query(int l, int r) {
        int k = Logn[r - l + 1];
        return gcd(st[l][k], st[r - (1 << k) + 1][k]);
    }
    static const int maxn = 1e4 + 10;
    static const int logn = 21;
    int Logn[maxn];
    int st[maxn][logn];
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; ++ i) cin >> a[i];
    ST_GCD st_max(a);
    int q; cin >> q;
    // while(q --) {
    //     int a, b; cin >> a >> b;
    //     cout << gcd(a, b) << endl;
    // }
    while(q --) {
        int l, r; cin >> l >> r;
        cout << st_max.Query(l, r) << endl;
    }
    return 0;
}
/*
8 3
1 3 -1 -3 5 3 6 7
*/