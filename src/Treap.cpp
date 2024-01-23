#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <random>
using namespace std;

mt19937 mt;

const int mx = 1e5;
/*
Treap 树堆
一种“弱平衡”的二叉搜索树
维护权值和优先级两个信息

对于权值val,满足二叉搜索树的性质，左子树左右节点小于更节点权值，右子树节点大于根节点权值

对于优先级rank，满足小根堆的性质，所有子树节点的优先级大于更节点的优先级

*/

int randGen() {
    unsigned long seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 mt(seed);
    return mt() % mx;
}
struct TreeNode{
    int val, rank;  // val 表示权值，rank 表示优先级
    int cnt;        // 表示当前权值节点出现个数
    int sz;         // 以当前节点为根的节点个数
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val) : val(_val), cnt(1), sz(1), height(0) {
        left = nullptr; right = nullptr;
        rank = randGen();
    }
    void updateSz() { //更新当前节点个数
        sz = cnt;
        if(left != nullptr) sz += left->sz;
        if(right != nullptr) sz += right->sz;
    }
};


class Treap
{
public:
    Treap() {
        
    }
    ~Treap() {
        destory(root);
    }
    int getSize() {
        return root == nullptr ? 0 : root->sz;
    }
    int getHeight() {
        return height(root);
    }
    void insert(int val) {
        root = insertHelper(root, val);
    }
    void remove(int val) {
        root = removeHelper(root, val);
    }
    bool isTreap() {
        return isTreapHelper(root);
    }
    void print(){
        cout << "Treap : ";
        inOrder(root);
        cout << endl;
    }
private:
    int height(TreeNode* node) {
        return node == nullptr ? -1 : node->height;
    }
    void updateHeight(TreeNode* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
    bool isTreapHelper(TreeNode* node) {
        if(node == nullptr) return true;
        if(node->left == nullptr && node->right == nullptr) return true;
        bool judge = true;
        if(node->left != nullptr) {
            if(node->left->val < node->val && node->left->rank >= node->rank) {
                judge = isTreapHelper(node->left);
            }
            else {
                return false;
            }
        }
        if(node->right != nullptr) {
            if(node->right->val > node->val && node->right->rank >= node->rank) {
                judge = isTreapHelper(node->right);
            }
            else {
                return false;
            }
        }
        return judge; 
    }
    // int updateHeight()
    /// @brief 右旋Zig  
    TreeNode* rightRotate(TreeNode* node) { 
        TreeNode* child = node->left;
        TreeNode* grandChild = child->right;
        child->right = node;
        node->left = grandChild;
        node->updateSz();
        child->updateSz();
        updateHeight(node);
        updateHeight(child);
        return child;
    }
    /// @brief 左旋Zag 
    TreeNode* leftRotate(TreeNode* node) {
        TreeNode* child = node->right;
        TreeNode* grandChild = child->left;
        node->right = grandChild;
        child->left = node;
        node->updateSz(); 
        child->updateSz();
        updateHeight(node);
        updateHeight(child);
        return child;
    }
    TreeNode* insertHelper(TreeNode* node, int val) {
        if(node == nullptr) {
            node = new TreeNode(val);
            return node;
        }
        if(val == node->val) {
            node->cnt ++;
            node->sz ++;
            return node;
        }
        // cout << "val : " << val << " , node : " << node->val << endl;
        if(val < node->val) {
            node->left = insertHelper(node->left, val);
            if(node->left->rank < node->rank) {
                node = rightRotate(node);
            }
        }
        else {
            node->right = insertHelper(node->right, val);
            if(node->right->rank < node->rank) {
                node = leftRotate(node);
            }
        }
        node->updateSz();
        updateHeight(node);
        return node;
    }
    TreeNode* removeHelper(TreeNode* node, int val) {
        if(node == nullptr) return node;
        if(val < node->val) {
            node->left = removeHelper(node->left, val);
        }
        else if(val > node->val) {
            node->right = removeHelper(node->right, val);
        }
        else { // val == node->val 
            if(node->cnt > 1) { //若权值个数大于1
                node->cnt --;
                node->sz --;
                return node;
            }
            else {
                if(node->left == nullptr && node->right == nullptr) {
                    delete node;
                    return nullptr;
                }
                if(node->left == nullptr || node->right == nullptr) {
                    TreeNode* child = node->left == nullptr ? node->right : node->left;
                    delete node;
                    node = child;
                }
                else {
                    TreeNode* maxNode = findMaxNode(node->left);
                    int maxVal = maxNode->val;
                    node->val = maxVal; 
                    node->left = removeHelper(node->left, maxVal);
                }
            }
        }
        node->updateSz();
        updateHeight(node);
        return node;
    }
    TreeNode* findMaxNode(TreeNode* node) {
        while(node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    TreeNode* findMinNode(TreeNode* node) {
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    void inOrder(TreeNode* node) {
        if(node == nullptr) return;
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }
    void destory(TreeNode* node) {
        if(node == nullptr) return;
        destory(node->left);
        destory(node->right);
        delete node;
    }
    
    TreeNode* root{};
};

int main()
{
    cout << "Hello Treap" << endl;
    int n = 100;
    Treap T;
    for(int i = 1; i <= n; ++ i) {
        int x = randGen() % 100;
        T.insert(i);
        if(T.isTreap()) {
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
        cout << " i : " << i << " , sz : " << T.getSize() << ", height : " << T.getHeight() << endl;
        // T.print();
    }
    for(int i = n; i >= 1; -- i) {
        T.remove(i);
        cout << " i : " << i << " , sz : " << T.getSize() << ", height : " << T.getHeight() << endl;
        if(T.isTreap()) {
            cout << "Re YES" << endl;
        }
        else {
            cout << "RE NO" << endl;
        }
    }
    return 0;
}
