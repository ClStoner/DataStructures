#include <bits/stdc++.h>
using namespace std;


/*
线段树： 支持区间修改，区间查询
空间复杂度 O(n)

建树: O(n log n)
区间修改：O(log n)
区间查询：O(log n)
*/

class SegmentTree
{
public:
    SegmentTree() {}
    static const int maxn = 1e5 + 100;
    struct SegmentNode{
        int l, r;
        int sum, add;
    }tree[maxn << 2];
    int a[maxn];
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define sum(p) tree[p].sum
    #define add(p) tree[p].add
    #define lsn (p << 1)
    #define rsn (p << 1 | 1)
    int len(int p) {
        return r(p) - l(p) + 1;
    }
    void Build(int l, int r, int p){
        l(p) = l; r(p) = r; add(p) = 0;
        if(l == r) {
            sum(p) = a[l]; return;
        }
        int mid = (l + r) >> 1;
        Build(l, mid, lsn); 
        Build(mid + 1, r, rsn);
        pushUp(p);
    }
    void Change(int l, int r, int p, int d){
        if(l <= l(p) && r >= r(p)) {
            pushTag(p, d); return;
        }
        pushDown(p);
        int mid = (l(p) + r(p)) >> 1;
        if(mid >= l) Change(l, r, lsn, d);
        if(mid < r)  Change(l, r, rsn, d);
        pushUp(p);
    }
    int Query(int l, int r, int p) {
        if(l <= l(p) && r >= r(p)) {
            return sum(p);
        }
        pushDown(p);
        int mid = (l(p) + r(p)) >> 1;
        int ans = 0;
        if(mid >= l) ans += Query(l, r, lsn);
        if(mid < r)  ans += Query(l, r, rsn);
        return ans;
    }
private:
    void pushTag(int p, int d){
        add(p) += d; sum(p) += len(p) * d;
    }
    void pushDown(int p) {
        if(!add(p)) return;
        pushTag(lsn, add(p)); pushTag(rsn, add(p));
        add(p) = 0;
    }
    void pushUp(int p) {
        sum(p) = sum(lsn) + sum(rsn);
    }
};
int main()
{
    SegmentTree SgT;    
    int n; cin >> n;
    for(int i = 1; i <= n; ++ i) {
        cin >> SgT.a[i];
    }
    int q; cin >> q;
    SgT.Build(1, n, 1);
    while(q --) {
        int op; cin >> op;
        switch (op)
        {
        case 1:{
            int l, r, d; cin >> l >> r >> d;
            SgT.Change(l, r, 1, d);
            break;
        }
        case 2: {
            int l, r; cin >> l >> r;
            cout << SgT.Query(l, r, 1) << endl;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}