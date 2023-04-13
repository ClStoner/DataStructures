#include <bits/stdc++.h>
using namespace std;

/*
队列： 双栈实现队列
*/

class Queue
{
public:
    Queue() : f_tp(0), s_tp(0) {}
    bool Empty() {
        return f_tp == 0 && s_tp == 0;
    }
    void Push(int x) {
        F[f_tp ++] = x;
    }
    void Pop() {
        if(s_tp == 0) Move();
        -- s_tp;
    }
    int Front() {
        if(s_tp == 0) Move();
        return S[s_tp - 1];
    }

    static const int maxn = 1e5 + 10;
    int F[maxn], S[maxn];
    int f_tp, s_tp;
private:
    void Move() {
        while(f_tp) {
            S[s_tp ++] = F[-- f_tp];
        }
    }
};




int main()
{
    int n = 10;
    Queue q;
    while(1) {
        int op; cin >> op;
        if(op == 1) {
            int x; cin >> x;
            q.Push(x);
        }
        else {
            cout << q.Front() << endl;
            q.Pop();
        }
    }

    return 0;
}