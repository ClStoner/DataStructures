#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;


double genDouble(double x) {
    unsigned long seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 mt(seed);
    uniform_real_distribution<double> dist(0, x);
    return dist(mt);
}
int gen(int x) {
    unsigned long seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 mt(seed);
    uniform_int_distribution<int> dist(0, x - 1);
    return dist(mt);
}


struct Cluster
{
    vector<double> center;
    vector<int> id;
};
double cal(const vector<double>&a, const vector<double>& b) {
    double sum = 0;
    for(int i = 0; i < a.size(); ++ i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(sum);
}
vector<Cluster> kmeans(vector<vector<double>>& train, int K, int maxIteration){
    int n = train.size();
    int m = train[0].size();
    vector<Cluster> res(K);
    vector<bool> vis(K, false);
    for(int i = 0; i < K; ++ i) {
        int id;
        while(true) {
            id = gen(n);
            if(!vis[id]) {
                vis[id] = true;
                break;
            }
        }
        cout << "id : " << id <<endl;
        res[i].center = train[id];
    }
    for(int iter = 0; iter < maxIteration; ++ iter) {
        for(int i = 0; i < K; ++ i) {
            res[i].id.clear();
        }
        for(int i = 0; i < n; ++ i) {
            double minDist = cal(train[i], res[0].center);
            int cand = 0;
            // cout << "minD : " << minDist << " ";
            for(int j = 1; j < K; ++ j) {
                double dist = cal(train[i], res[j].center);
                // cout << dist << " "; 
                if(dist < minDist) {
                    minDist = dist; cand = j;
                }
            }
            // cout << "\ncand : " << cand <<endl;
            res[cand].id.push_back(i);
        }

        for(int i = 0; i < K; ++ i) {
            vector<double> avg(m, 0.0);

            for(int j = 0; j < res[i].id.size(); ++ j) {
                int x = res[i].id[j];
                for(int k = 0; k < m; ++ k) {
                    avg[k] += train[x][k];
                }
            }
            for(int j = 0; j < m; ++ j) {
                avg[j] /= res[i].id.size();
            }
            res[i].center = avg;
        }

    }
    return res;
}

int main()
{
    int n, m; cin >> n >> m;
    int k; cin >> k;
    vector<vector<double>> data(n, vector<double>(m));
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            data[i][j] = gen(30);
        }
    }


    for(int i = 0; i < n; ++ i) {
        cout << i <<  " : [ ";
        for(int j = 0; j < m; ++ j) {
            cout << data[i][j] << " ";
        }
        cout << "]" << endl;
    }
    

    vector<Cluster> cluster = kmeans(data, k, 10);

    for(int i = 0; i < cluster.size(); ++ i) {
        cout << "cluster " << i << "  center : [ " ;
        for(int j = 0; j < cluster[i].center.size(); ++ j) {
            cout << cluster[i].center[j] << " ";
        }
        cout << "]" << endl;
        auto id = cluster[i].id;
        cout << " size : " << id.size() <<endl;
        for(int k = 0; k < id.size(); ++ k) {
            for(int j = 0; j < m; ++ j) {
                cout << data[id[k]][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}