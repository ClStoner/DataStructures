// #include <bits/stdc++.h>
#include <iostream>
#include <deque>
#include <vector>
using namespace std;


/*
单调队列：解决滑动窗口中最值问题
复杂度： O(n)
*/
class Monotonic_Queue
{
public:
    vector<int> SlideWindowMin(vector<int>& a, int k){
        head = 0; tail = 0;
        int n = a.size();
        vector<int> ans;
        for(int i = 0; i < k; ++ i) {
            while(head < tail && a[i] <= a[q[tail - 1]]) -- tail;
            q[tail ++] = i;
        }
        ans.push_back(a[q[head]]);
        for(int i = k; i < n; ++ i) {
            while(head < tail && a[i] <= a[q[tail - 1]]) -- tail;
            q[tail ++] = i;
            while(q[head] <= i - k) ++ head;
            ans.push_back(a[q[head]]);
        }
        return ans;
    }
    vector<int> SlideWindowMax(vector<int>& a, int k) {
        head = 0; tail = 0;
        int n = a.size();
        vector<int> ans;
        for(int i = 0; i < k; ++ i) {
            while(head < tail && a[i] >= a[q[tail - 1]]) -- tail;
            q[tail ++] = i;
        }
        ans.push_back(a[q[head]]);
        for(int i = k; i < n; ++ i) {
            while(head < tail && a[i] >= a[q[tail - 1]]) -- tail;
            q[tail ++] = i;
            while(q[head] <= i - k) ++ head;
            ans.push_back(a[q[head]]);
        }
        return ans;
    }

    static const int maxn = 1e6 + 10;
    int q[maxn];
    int head, tail;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; ++ i) cin >> a[i];
    vector<int> a_min, a_max;
    Monotonic_Queue MQ;
    a_min = MQ.SlideWindowMin(a, k);
    a_max = MQ.SlideWindowMax(a, k);

    for(int i = 0; i < a_min.size(); ++ i) {
        cout << a_min[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < a_max.size(); ++ i) {
        cout << a_max[i] << " ";
    }
    cout << endl;

    return 0;
}

/*
8 3
1 3 -1 -3 5 3 6 7


-1 -3 -3 -3 3 3
3 3 5 5 6 7

*/