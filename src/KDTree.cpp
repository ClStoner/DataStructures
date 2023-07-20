#include <bits/stdc++.h>
using namespace std;

#define POINTER_TYPEDEFS(TypeName)                                                                                                                   \
    typedef std::shared_ptr<TypeName> Ptr;                                                                                                           \
    typedef std::shared_ptr<const TypeName> ConstPtr;                                                                                                \
    typedef std::unique_ptr<TypeName> UniquePtr;                                                                                                     \
    typedef std::weak_ptr<TypeName> WeakPrt;                                                                                                         \
    typedef std::weak_ptr<const TypeName> WeakConstPtr;                                                                                              \
    void definePointerTypedefs##__FILE__##__LINE__(void)

/*
KD 
*/
template<class T>
class KDNode
{
public:
    POINTER_TYPEDEFS(KDNode<T>);
    KDNode(vector<T>_val, int _axis) : val(_val) , axis(_axis) , parent(nullptr), leftChild(nullptr), rightChild(nullptr) {} 
    ~KDNode() {}
    KDNode* parent;
    KDNode* leftChild;
    KDNode* rightChild;
    vector<T> val;
    int axis;
};
/*
重载输出流
*/
template<class T>
ostream & operator << (ostream& os, vector<T>& a) {
    os << "( ";
    for(int i = 0; i < a.size(); ++ i) {
        os << a[i];
        if(i < a.size() - 1) os << ", ";
    }
    os << " )";
    return os;
}

template<class T>
class KDTree
{
public:
    POINTER_TYPEDEFS(KDTree);
    KDTree(vector<vector<T>> _data, int _dim) : data(_data) , dimension(_dim) {
        sz = data.size();
    }
    ~KDTree() {}
    void Build() {
        int split = splitDim(0, sz - 1);
        root = buildTree(0, sz - 1, split);
    }
    KDNode<T>* Search(vector<T>& vec) {

    }
    void Print() {
        dfsTree(root);
    }

private:
    /// @brief 选取方差最大的维度作为分割轴
    /// @param left 
    /// @param right 
    /// @return 
    int splitDim(int left, int right) {
        vector<double> avg(dimension, 0);
        for(int i = left; i <= right; ++ i) {
            for(int j = 0; j < dimension; ++ j) {
                avg[j] += data[i][j];
            }
        }
        int len = (right - left + 1);
        for(int i = 0; i < dimension; ++ i) avg[i] /= len;
        vector<double> var(dimension, 0);
        for(int i = left; i <= right; ++ i) {
            for(int j = 0; j < dimension; ++ j) {
                var[j] += ((data[i][j] - avg[j]) * (data[i][j] - avg[j]));
            }
        }
        int mx = -1, split = -1;
        for(int i = 0; i < dimension; ++ i) {
            if(var[i] > mx) {
                mx = var[i]; split = i;
            }
        }
        return split;
    }
    KDNode<T>* buildTree(int left, int right, int dim) {
        if(left > right) return nullptr;
        // int dim = splitDim(left, right);
        sort(data.begin() + left, data.begin() + right + 1, [dim](vector<T>&a, vector<T>& b) -> bool {
            return a[dim] < b[dim];
        });
        int mid = (left + right + 1) >> 1;
        KDNode<T>* node = new KDNode<T>(data[mid], dim);
        node->leftChild = buildTree(left, mid - 1, (dim + 1) % dimension);
        if(node->leftChild) node->leftChild->parent = node;
        node->rightChild = buildTree(mid + 1, right, (dim + 1) % dimension);
        if(node->rightChild) node->rightChild->parent = node;
        return node;
    }   
    void dfsTree(KDNode<T>* node) {
        if(node == nullptr) return;
        cout << node->val << endl;
        dfsTree(node->leftChild);
        dfsTree(node->rightChild);
    }  
    double disVector(vector<T>& a, vector<T> &b) {
        double sum = 0;
        for(int i = 0; i < dimension; ++ i) sum += ((a[i] - b[i]) * (a[i] - b[i]));
        return sqrt(sum);
    }
    int dimension, sz;
    vector<vector<T>> data;
    KDNode<T>* root;
};
int main()
{
    int n, k; cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(k));
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < k; ++ j) {
            cin >> a[i][j];
        }
    }
    KDTree<int>::Ptr kd = make_shared<KDTree<int>> (a, k);
    kd->Build();
    kd->Print();

    return 0;
}
/*
(2,3），（5,4），（9,6），（4,7），（8,1），（7,2)
Input
6 2
2 3
5 4
9 6
4 7
8 1
7 2

Output
( 7, 2 )
( 5, 4 )
( 2, 3 )
( 4, 7 )
( 9, 6 )
( 8, 1 )




(2,3),(3,4),(4,6),(8,6),(12,8),(13,10)
Input
6 2
2 3
3 4
4 6
8 6
12 8
13 10
Output
( 8, 6 )
( 3, 4 )
( 2, 3 )
( 4, 6 )
( 13, 10 )
( 12, 8 )
*/