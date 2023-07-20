#include <bits/stdc++.h>
using namespace std;

// const int maxn = 10000;



void countingSort(int *a, int n) {
    int mx = a[0];
    for(int i = 0; i < n; ++ i) {
        mx = max(mx, a[i]);
    }
    int* cnt = new int[mx + 1];
    int* b = new int[n];
    memset(cnt, 0, sizeof(int) * n);
    for(int i = 0; i < n; ++ i) ++ cnt[a[i]];
    for(int i = 1; i <= mx; ++ i) cnt[i] += cnt[i - 1];
    for(int i = n - 1; i >= 0; -- i) {
        b[cnt[a[i] --] - 1] = a[i];
    }
    memcpy(a, b, sizeof(int) * n);
    delete b;
    delete cnt;
}


int main()
{
    int n; cin >> n;
    int a[100]; 
    for(int i = 0; i < n; ++ i) {
        a[i] = rand() % 100;
    }
    cout << "Before Sort" << endl;
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
    }
    cout <<endl;
    countingSort(a, n);
    cout << "After Sort" << endl;
    bool flag = true;
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
        if(i > 0 && a[i] < a[i - 1]) {
            flag = false;
        }
    }
    cout << endl;
    return 0;
}