#include <bits/stdc++.h>
using namespace std;

/*
并查集： 管理元素所属集合的数据结构

*/

class DSU
{
public:
    DSU() {
        for(int i = 0; i < maxn; ++ i) fa[i] = i;
        memset(sz, 1, sizeof(sz));
    }
    int find(int x) {return fa[x] == x ? x : find(fa[x]); }
    // 启发式合并
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(sz[x] < sz[y]) swap(x, y);
        fa[y] = x; sz[x] += sz[y];
    }
private: 
    static const int maxn = 1e5 + 10;
    int fa[maxn + 10], sz[maxn + 10];
};

int main()
{


    return 0;
}