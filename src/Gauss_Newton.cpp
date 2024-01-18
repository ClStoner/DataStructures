// #include <iostream>
// #include <chrono>
// #include <vector>
// #include <random>
// #include <cmath>
// #include <cstring>
// using namespace std;

// /*
// 高斯牛顿法拟合直线
// y = a * x + b 
// */



#include <bits/stdc++.h>
using namespace std;

vector<double> solveGN(const vector<double>& xdata, const vector<double>& ydata) {
    int sz = xdata.size();
    int maxIter = 10;
    int iter = 0;
    double init_a = 1.0, init_b = 1.0;
    double var_a = init_a, var_b = init_b;
    while(iter < maxIter) {
        iter ++;
        double H[2][2], b[2];
        memset(H, 0, sizeof(H)); memset(b, 0, sizeof(b));
        for(int i = 0; i < sz; ++ i) {
            double r = ydata[i] - var_a * xdata[i] - var_b;
            double Ja = -xdata[i], Jb = -1.0;
            H[0][0] += Ja * Ja; H[0][1] += Ja * Jb;
            H[1][0] += Jb * Ja; H[1][1] += Jb * Jb;
            b[0] -= Ja * r; b[1] -= Jb * r;
        }
        double D = (H[0][0] * H[1][1] - H[0][1] * H[1][0]);
        double delta_a = (b[0] * H[1][1] - H[0][1] * b[1]) / D;
        double delta_b = (H[0][0] * b[1] - H[1][0] * b[0]) / D;
        var_a += delta_a; var_b += delta_b;
        if(sqrt(delta_a * delta_a + delta_b * delta_b) < 1e-6) break;
    }
    cout << "GaussNewton Iter : " << iter << " success!" << endl;
    return vector<double>{var_a, var_b};
}
vector<double> solveN(const vector<double>& xdata, const vector<double>& ydata) {
    int sz = xdata.size();
    int maxIter = 10;
    int iter = 0;
    double init_a = 1.0, init_b = 1.0;
    double var_a = init_a, var_b = init_b;
    while(iter < maxIter) {
        iter ++;
        double J[2];
        memset(J, 0, sizeof(J));
        for(int i = 0; i < sz; ++ i) {
            double r = ydata[i] - var_a * xdata[i] - var_b;
            double Ja = -xdata[i], Jb = -1.0;
            J[0] -= Ja; J[1] -= Jb;
        }

        double delta_a = J[0];
        double delta_b = J[1];
        var_a += delta_a; var_b += delta_b;
        if(sqrt(delta_a * delta_a + delta_b * delta_b) < 1e-6) break;
    }
    cout << "Newton Iter : " << iter << " success!" << endl;
    return vector<double>{var_a, var_b};
}
int main()
{
    mt19937 mt_rand(chrono::system_clock::now().time_since_epoch().count());
    normal_distribution<double> nd(0.0, 5.0);
    double a, b;
    cin >> a >> b;
    vector<double>xd, yd;
    int n = 100;
    for(int i = 0; i < n; ++ i) {
        double x =  (1.0 * i) / 10;
        double y = a * x + b + nd(mt_rand);
        xd.push_back(x); yd.push_back(y);
    }
    vector<double> ans = solveGN(xd, yd);
    cout << "GN a : " << ans[0] << " , b : " << ans[1] << endl;
    vector<double> ans1 = solveN(xd, yd);
     cout << "N a : " << ans1[0] << " , b : " << ans1[1] << endl;
    return 0;
}