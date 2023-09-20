#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Ransac 拟合直线，剔除外点

*/
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};
struct Line {
    double k, b; // y = kx + b
    Line(double _k = 0, double _b = 0) : k(_k), b(_b) {}
    double GetY(double x) {
        return k * x + b;
    }
};
Line RansacLine(vector<Point>& pts, int iteration, int threshold) {
    Line ans(0, 0);

    int bestCnt = 0;
    int n = pts.size();
    for(int iter = 0; iter < iteration; ++ iter) {
        random_device rd;
        mt19937 mt(rd());
        int idx1, idx2;
        while(true) {
            idx1 = mt() % n, idx2 = mt() % n;
            if(idx1 < idx2) break;
        }
        Point p1 = pts[idx1];
        Point p2 = pts[idx2];
        double k = (p2.y - p1.y) / (p2.x - p1.x);
        double b = p1.y - p1.x * k;
        Line cand(k, b);
        double res = 0;
        int cnt = 0;
        for(int i = 0; i < n; ++ i) {
            double tmpres = fabs(cand.GetY(pts[i].x) - pts[i].y);
            if(tmpres <= threshold) {
                ++ cnt;
            }
        }
        cout << " cnt : " << cnt << endl;
        if(cnt >= bestCnt) {
            bestCnt = cnt;
            ans = cand;
        }
    }
    return ans;
}
int main() 
{
    Line trueline(3.0, 4.0);
    vector<Point> vp;
    int N = 100;
    double sigma = 1.0;
    random_device rd;
    mt19937 mt(rd());
    normal_distribution<double> gen(0.0, sigma);
    for(int i = 0; i < N; ++ i) {
        double x = 10.0 * i / N;
        double y = trueline.GetY(x) + gen(mt);
        vp.push_back(Point(x, y));
    }
    int maxIter = 100;
    Line resline = RansacLine(vp, maxIter, sigma);
    cout << resline.k << " " << resline.b << endl;
    return 0;
}
