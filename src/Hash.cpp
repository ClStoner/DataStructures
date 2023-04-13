#include <bits/stdc++.h>
using namespace std;


/*
哈希表：
可以支持快速删除，查找元素，
时间复杂度 O(1)
*/

class HashNode
{
public: 
    HashNode() {}
    HashNode(int _nxt, int _val, int _key) : nxt(_nxt), val(_val), key(_key) {}
    int nxt, val, key;
};

class HashTable
{
public: 
    HashTable() : size(0) {
        memset(head, 0, sizeof(head));
    }
    static const int SIZE = 1e5 + 10;
    static const int M = 99997;
    HashNode data[SIZE << 1];
    int head[SIZE], size;

    int get(int key) {
        for(int p = head[f(key)]; p; p = data[p].nxt) {
            if(data[p].key == key) return data[p].val;
        }
        return -1;
    }
    int modify(int key, int val) {
        for(int p = head[p]; p; p = data[p].nxt) {
            if(data[p].key == key) return data[p].val = val;
        }
    }
    int add(int key, int val) {
        if(get(key) != -1) return -1;
        data[++ size] = HashNode(head[f(key)], val, key);
        head[f(key)] = size;
        return val;
    }
private:
    int f(int key) {return (key % M + M) % M;}
};


/*
哈希表实现 unordered_map
*/
class HashMap
{
public: 
    HashMap() : size(0) {
        memset(head, 0, sizeof(head));
    }
    int find(int key) {
        for(int p = head[f(key)]; p; p = data[p].nxt) {
            if(data[p].key == key) return data[p].val;
        }
        return -1;
    }
    int& operator[](int key) {
        int x = f(key);
        for(int p = head[x]; p; p = data[p].nxt) {
            if(data[p].key == key) return data[p].val;
        }
        data[++ size] = HashNode(head[x], 0, key);
        head[x] = size;
        return data[size].val;
    }
    void erase(int key) {
        int x = f(key);
    }
    

private:
    static const int SIZE = 1e5;
    static const int M = 99997;
    HashNode data[SIZE << 1];
    int head[SIZE], size;

    int f(int key) {return (key % M + M) % M; }

};


int main()
{
    int T; cin >> T; 
    while(T --) {
        // HashTable mp;
        HashMap mp;
        int n; cin >> n;
        vector<int> ans;
        for(int i = 1; i <= n; ++ i) {
            int x; cin >> x;
            if(mp.find(x) == -1) {
                mp[x] = 1;
                ans.push_back(x);
            }
        }
        for(auto it : ans) cout << it << " ";
        cout << endl;
    }

    return 0;
}