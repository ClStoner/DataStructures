#include <bits/stdc++.h>
using namespace std;


void InsertSort(int* a, int n) {
    for(int i = 1; i < n; ++ i) {
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && key < a[j]) {
            a[j + 1] = a[j];
            -- j;
        }
        a[j + 1] = key;
    }
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
    InsertSort(a, n);
    cout << "After Sort" << endl;
    bool flag = true;
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
        if(i > 0 && a[i] < a[i - 1]) {
            flag = false;
        }
    }
    cout << endl;
    if(flag) {
        cout << "AC" << endl;
    }
    else {
        cout << "Wrong" << endl;
    }
    return 0;
}