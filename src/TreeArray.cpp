#include <bits/stdc++.h>
using namespace std;


#define lowbit(x) ((x) & (-x))


/*
树状数组查询区间和，支持单点修改，与区间查询
时间复杂度： 单点修改 O(log n), 区间查询 O(log n)
空间复杂度： O(n)
*/

class TreeArray
{
public:
    TreeArray() {
        memset(c, 0, sizeof(c));
    }
    void Add(int x, int d) {
        while(x <= maxn) {
            c[x] += d;
            x += lowbit(x);
        }
    }
    int Query(int x) {
        int ans = 0;
        while(x) {
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
    static const int maxn = 1e5 + 10;
    int c[maxn + 10];
};

int main()
{
    int n; cin >> n;
    // vector<int> a(n);
    TreeArray ta;
    for(int i = 1; i <= n; ++ i) {
        ta.Add(i, i);
    }
    while(1) {
        int l, r; cin >> l >> r;
        int ans = ta.Query(r) - ta.Query(l - 1);
        cout << ans << endl;
    }


    return 0;
}