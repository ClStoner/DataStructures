#include <iostream>
#include <chrono>
#include <vector>
#include <random>
using namespace std;


double rng(double sigma) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 mt(seed);
    normal_distribution<double> dist(0.0, sigma);
    return dist(mt);
}
vector<double> solve(vector<vector<double>>H, vector<double> b)
{

} 

// y = exp(ax + b) 
int main()
{
    double at = 1.0, bt = 2.0;
    double ar = 3.0, br = 4.0;
    double sigma = 1.0;
    int N = 100;
    vector<int> x_data, y_data;
    for(int i = 0; i < 100; ++ i) {
        double x = 1.0 * i / 100;
        x_data.push_back(x);
        double y = exp(at * x * x + bt * x) + rng(sigma);
        y_data.push_back(y);
    }
    int maxIter = 100;
    double cost = 0, lastCost = 0;
    
    for(int iter = 0; iter < maxIter; ++ iter) {
        vector<vector<double>> H(2, vector<double>(2, 0));
        vector<double> b(2, 0.0);

        cost = 0;
        for(int i = 0; i < N; ++ i) {
            double xi = x_data[i];
            double yi = y_data[i];
            double obs = exp(ar * xi + br);
            double error = yi - obs;
            double J[2];
            J[0] = -xi * obs;
            J[1] = -obs;
            H[0][0] += J[0] * J[0];
            H[0][1] += J[0] * J[1];
            H[1][0] += J[1] * J[0];
            H[1][1] += J[1] * J[1];
            b[0] += error * J[0];
            b[1] += error * J[1];
            cost += error * error;
        }
        vector<double> dx(2);
        dx = solve(H, b);
        ar += dx[0];
        br += dx[1];
    }
    
    return 0;
}