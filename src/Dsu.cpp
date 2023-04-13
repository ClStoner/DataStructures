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
        memset(size, 1, sizeof(size));
    }
    int find(int x) {return fa[x] == x ? x : find(fa[x]); }
    // 启发式合并
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(size[x] < size[y]) swap(x, y);
        fa[y] = x; size[x] += size[y];
    }
private: 
    static const int maxn = 1e5 + 10;
    int fa[maxn + 10], size[maxn + 10];
};

int main()
{


    return 0;
}