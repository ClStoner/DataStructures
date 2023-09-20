#include <bits/stdc++.h>
using namespace std;


class SparseMatrix{
public:
    SparseMatrix(int row, int col) : numRows(row), numCols(col), num(0) {}
    SparseMatrix(const SparseMatrix& rhs) {
        num = rhs.num;
        numRows = rhs.numRows;
        numCols = rhs.numCols;
        values = rhs.values;
        rowIdx = rhs.rowIdx;
        colIdx = rhs.colIdx;
    }
    SparseMatrix operator = (const SparseMatrix& rhs) {
        SparseMatrix res(rhs.numRows, rhs.numCols);
        res.num = rhs.num;
        res.values = rhs.values;
        res.rowIdx = rhs.rowIdx;
        res.colIdx = rhs.colIdx;
    }
    void Insert(int row, int col, double val) {
        rowIdx.push_back(row);
        colIdx.push_back(col);
        values.push_back(val);
        ++ num;
    }
    void print() {
        for(int i = 0; i < numRows; ++ i) {
            for(int j = 0; j < numCols; ++ j) {
                bool flag = false;
                for(int k = 0; k < num; ++ k) {
                    if(rowIdx[k] == i && colIdx[k] == j) {
                        flag = true;
                        cout << values[k] << " ";
                    }
                }
                if(!flag) cout << "0 " ;
            }
            cout << endl;
        }
    }
    
    // SparseMatrix operator * (const SparseMatrix& rhs) {
    //     int row = numRows, col = rhs.numCols;
    //     SparseMatrix res(row, col);
    //     unordered_map<int, int> m;
    //     for(int i = 0; i < num; ++ i) {
    //         for(int j = 0; j < rhs.num; ++ j) {
    //             if(colIdx[i] != rhs.rowIdx[j]) continue;
    //             int r = rowIdx[i], c = rhs.colIdx[j];
    //             double x = values[i] * rhs.values[j];
    //             m[r * col + c] += x;
    //         }
    //     }
    //     for(auto it : m) {
    //         int r = it.first / col, c = it.first % col;
    //         res.Insert(r, c, it.second);
    //     }
    //     return res;
    // }
    SparseMatrix operator * (const SparseMatrix& rhs) {
        int row = numRows, col = rhs.numCols;
        SparseMatrix res(row, col);
        map<pair<int, int>, double> m;
        for(int i = 0; i < num; ++ i) {
            for(int j = 0; j < rhs.num; ++ j) {
                if(colIdx[i] != rhs.rowIdx[j]) continue;
                m[make_pair(rowIdx[i], rhs.colIdx[j])] += values[i] * rhs.values[j];
            }
        }
        for(auto it : m) {
            int r = it.first.first, c = it.first.second;
            double x = it.second;
            res.Insert(r, c, x);
        }
        return res;
    }
private:
    int numRows, numCols, num;
    vector<double> values;
    vector<int> rowIdx;
    vector<int> colIdx;
};

int main()
{   
    SparseMatrix A(3, 3);
    A.Insert(0, 0, 1);
    A.Insert(1, 1, 2);
    A.Insert(1, 2, 4);
    A.Insert(2, 2, 3);

    SparseMatrix B(3, 4);
    B.Insert(0, 1, 2);
    B.Insert(0, 2, 3);
    B.Insert(0, 3, 4);
    B.Insert(1, 2, 5);
    A.print();
    cout <<endl;
    B.print();
    cout <<endl;
    SparseMatrix C = A * B;
    C.print();
    return 0;
}