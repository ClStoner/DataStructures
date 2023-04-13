#include <bits/stdc++.h>
using namespace std;


/*
大根堆： 根节点权值大于子节点权值，是一颗完全二叉树
插入： 时间复杂度 O(log n)
删除： 时间复杂度 O(log n)
*/
class HeapBig
{
public:
    HeapBig() : sz(0) {
        a.push_back(0);
    }
    ~HeapBig() { a.clear(); }
    void push(int x) {
        a.push_back(x);
        up(++ sz);
    }
    void pop() {
        swap(a[1], a.back());
        a.pop_back();-- sz;
        down(1);
    }
    int top() { return a[1]; }
    bool empty() { return sz == 0; }
    int size() { return sz; }
private:
    vector<int> a;
    int sz;
    void down(int p) {
        while((p << 1) <= sz) {
            int now = p << 1;
            if(now + 1 <= sz && a[now + 1] > a[now]) ++ now;
            if(a[p] >= a[now]) break;
            swap(a[p], a[now]); p = now;
        }
    }
    void up(int p) {
        while(p > 1 && a[p] > a[p >> 1]) {
            swap(a[p], a[p >> 1]);
            p >>= 1;
        }
    }
};
/*
小根堆：根节点权值小于子节点，为完全二叉树
插入： 时间复杂度 O(log n)
删除： 时间复杂度 O(log n)
*/
class HeapSmall
{
public:
    HeapSmall() : sz(0){
        a.push_back(0);
    }
    ~HeapSmall() { a.clear(); }
    void push(int x) {
        a.push_back(x);
        up(++ sz);
    }
    void pop() {
        swap(a[1], a.back());
        a.pop_back();-- sz;
        down(1);
    }
    int top() { return a[1]; }
    bool empty() { return sz == 0; }
    int size() { return sz; }
private:
    vector<int> a;
    int sz;
    void down(int p) {
        while((p << 1) <= sz) {
            int now = p << 1;
            if(now + 1 <= sz && a[now + 1] < a[now]) ++ now;
            if(a[p] <= a[now]) break;
            swap(a[p], a[now]);
            p = now;
        }
    }
    void up(int p) {
        while(p > 1 && a[p] < a[p >> 1]) {
            swap(a[p], a[p >> 1]);
            p >>= 1;
        }
    }
};
/*
对顶堆： 维护前k大的数
一个大根堆维护前k小的数，一个小根堆维护后面的数
*/
class Heap
{
public:
    Heap() : sz(0) {

    }
    ~Heap() {}
    void push(int x) {
        if(big.empty() || x <= big.top()) big.push(x);
        else small.push(x);
        ++ sz;
        maintain();
    }
    void pop(){
        big.pop();
        -- sz;
        maintain();
    }
    int top() {
        return big.top();
    }
    int size(){ return sz; }

private:
    HeapBig big;  // 大根堆维护前 k（包括k） 大的数
    HeapSmall small; // 小根堆维护后 k 小的数
    int sz;
    void maintain() {
        int k = get(sz);
        while(big.size() < k) {
            big.push(small.top()); 
            small.pop();
        }
        while(big.size() > k) {
            small.push(big.top());
            big.pop();
        }
    }
    int get(int n) {
        return (n + 1) >> 1;
    }
};

int main()
{   
    int T; cin >> T;
    while(T --) {
        Heap hp;
        int n;
        while(1) {
            cin >> n;
            if(n == 0) break;
            if(n == -1) {
                cout << hp.top() << endl;
                hp.pop();
            }
            else {
                hp.push(n);
            }
        }
    }

    return 0;
}