#include <bits/stdc++.h>
using namespace std;

unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 mt(seed);

// 随机生成[n, m)区间的数
int gen(int n, int m) {
    uniform_int_distribution<int> dist(n, m - 1);
    return dist(mt);
}



void quickSort(int *a, int len) {
    if(len <= 1) return;
    int pivot = a[rand() % len];
    int i = 0, j = 0, k = len;
    while(i < k) {
        if(a[i] < pivot) swap(a[i ++], a[j ++]);
        else if(a[i] > pivot) swap(a[i], a[-- k]);
        else ++ i;
    }
    quickSort(a, j);
    quickSort(a + k, len - k);
}

int findK(int *a, int low, int high, int K) {
    if(low == high && low == K) return a[low];
    int idx = gen(0, 100);
    // cout << "low : " << low << " high : " << high << " , idx : " << idx << endl;
    int pivot = a[idx];
    int i = low, j = low, k = high;
    while(i < k) {
        if(a[i] < pivot) swap(a[i ++], a[j ++]);
        else if(a[i] > pivot) swap(a[i], a[-- k]);
        else ++ i;
    }
    if(K < j) return findK(a, low, j, K);
    if(K >= k) return findK(a, k, high, K);
    return a[j];
}

int main() 
{
    srand(unsigned(time(0)));
    int n; cin >> n;
    int a[100]; 
    for(int i = 0; i < n; ++ i) {
        a[i] = gen(0, 6);
    }
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
    }
    cout << endl;
    int k; cin >> k;
    auto lamfindK = [](int* a, int low, int high, int K) ->int {
        function<int(int*, int, int, int)> f;
        f = [&](int* a, int low, int high, int K) {
            if(low == high && low == K) return a[low];
            int pivot = a[gen(low, high)];
            int i = low, j = low, k = high;
            while(i < k) {
                if(a[i] < pivot) swap(a[i ++], a[j ++]);
                else if(a[i] > pivot) swap(a[i], a[-- k]);
                else ++ i;
            }
            if(K < j) return f(a, low, j, K);
            if(K >= k) return f(a, k, high, K);
            else return a[j];
        };
        return f(a, low, high, K);
    };
    cout << "The lambda Kth : " << lamfindK(a, 0, n, n - k) << endl;
    cout << "The Kth : " << findK(a, 0, n, n - k) << endl;
    quickSort(a, n);
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0; 
}