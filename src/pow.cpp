#include <iostream>
#include <cmath>
using namespace std;


/*
计算1/(a^n)次幂
*/
double pow(double a, int n) { // a^n
    double x = 1.0;
    while(n --) {
        x *= a;
    }
    return x;
}
double cal(double a, int n) {
    double x = 1.0;
    int cnt = 0;
    while(true) {
        ++ cnt;
        double f = pow(x, n) - a;
        double Jf = 1.0 * n * pow(x, n - 1);
        double delta_x = -f / Jf;
        x += delta_x;
        if(fabs(delta_x) < 1e-6) break;
    }
    cout << "cnt : " << cnt << endl;
    return x;
}
double bin_cal(double a, int n) {
    double low = 1, high = 10;
    int cnt = 0;
    while(fabs(high - low) >= 1e-6) {
        ++ cnt;
        double mid = (low + high) / 2.0;
        if(pow(mid, n) - a > 0) high = mid;
        else low = mid;
    }
    cout << "cnt :" << cnt << endl;
    return low;
}
int main()
{
    double a;
    int n; 
    cin >> a >>n;
    cout << cal(a, n) << " , " << bin_cal(a, n) << endl;
    return 0;
}