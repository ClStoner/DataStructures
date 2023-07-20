#include <bits/stdc++.h>
using namespace std;



void mergeSort(int *a, int n) {
    if(n <= 1) return;
    int mid = n >> 1;
    mergeSort(a, mid);
    mergeSort(a + mid, n - mid);

    int i = 0, j = mid, k = 0;
    int* b = new int[n];
    while(i < mid && j < n) {
        if(a[i] <= a[j]) {
            b[k ++] = a[i ++];
        }
        else b[k ++] = a[j ++];
    }
    while(i < mid) {
        b[k ++] = a[i ++];
    }
    while(j < n) {
        b[k ++] = a[j ++];
    }
    memcpy(a, b, sizeof(int) * n);
    delete b;
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
    mergeSort(a, n);
    cout << "After Sort" << endl;
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
    }
    cout << endl;
}