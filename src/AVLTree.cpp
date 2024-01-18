#include <bits/stdc++.h>
using namespace std;

/*
平衡二叉树
节点数目为n时，
树高度O(log n)
插入节点复杂度为O(log n)
删除节点复杂度为O(log n)
*/

struct TreeNode
{
    int val{};
    int height = 0;  //叶子节点高度为0，空节点高度为-1
    TreeNode* left{};
    TreeNode* right{};
    TreeNode() = default;
    explicit TreeNode(int x) : val(x) {}
};



class AVLTree 
{
public:
    int getHeight() {return height(root); } //获取树高
    int getSize() {return size;}            //获取节点数目
    bool find(int val) {                    //查询平衡二叉树中是否存在值为 val 的节点
        return findHelper(root, val);   
    }
    void insert(int val) {                  //插入节点
        if(!find(val)) ++ size;
        root = insertHelper(root, val); 
        // cout << "insert success" << endl;
    }
    void remove(int val) {                  // 删除节点
        if(find(val)) -- size;
        root = removeHelper(root, val);
    }
   
    
    void print() {                          //打印平衡二叉树
        // cout << "AVL : ";
        inOrder(root);
        cout << endl;
    }
    
private:
    int height(TreeNode* T) {
        return T == nullptr ? -1 : T->height;
    }
    int updateHeight(TreeNode* T) {
        T->height = max(height(T->left), height(T->right)) + 1;
    }
    int balanceFactor(TreeNode* T) {
        if(T == nullptr) return 0;
        return height(T->left) - height(T->right);
    }
    bool isBalanceTree() {                  //判断是否为平衡二叉树
        return isBalanceTreeHelper(root);
    }
    TreeNode* rightRotate(TreeNode* node) {
        TreeNode* child = node->left;
        TreeNode* grandChild = child->right;
        child->right = node; 
        node->left = grandChild;
        updateHeight(node);
        updateHeight(child);
        return child;
    }
    TreeNode* leftRotate(TreeNode* node) {
        TreeNode* child = node->right;
        TreeNode* grandChild = child->left;
        child->left = node;
        node->right = grandChild;
        updateHeight(node);
        updateHeight(child);
        return child;
    }
    TreeNode* rotate(TreeNode* node) {
        int balanceNode = balanceFactor(node);
        if(balanceNode > 1) {
            if(balanceFactor(node->left) >= 0 ) {
                return rightRotate(node);
            }
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if(balanceNode < -1) {
            if(balanceFactor(node->right) <= 0) {
                return leftRotate(node);
            }
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }
    TreeNode* insertHelper(TreeNode* node, int val) {
        if(node == nullptr) {
            node = new TreeNode(val);
            return node;
        }
        // cout << "tree : " << node->val << endl;
        if(val < node->val) {
            node->left = insertHelper(node->left, val);
        }
        else if(val > node->val) {
            node->right = insertHelper(node->right, val);
        }
        else return node;

        updateHeight(node);
        node = rotate(node);
        // cout << "bal : " << balanceFactor(node) << endl;
        return node;
    }
    TreeNode* removeHelper(TreeNode* node, int val) {
        if(node == nullptr) return node;
        if(val < node->val) {
            node->left = removeHelper(node->left, val);
        }
        else if(val > node->val){//val > node->val 
            node->right = removeHelper(node->right, val);
        }
        else { //val == node->val 
            if(node->left == nullptr || node->right == nullptr) {
                TreeNode* child = node->left == nullptr ? node->right : node->left;
                if(child == nullptr) { // 左右节点均为空，叶子节点，直接删除
                    delete child;
                    return nullptr;
                }
                else {
                    delete node;
                    node = child;
                }
            }
            else { //左右节点均非空，使用当前左子树中最大值替换当前节点
                TreeNode* maxNode = node->left;
                while(maxNode->right) {
                    maxNode = maxNode->right;
                }
                int maxVal = maxNode->val;
                node->left = removeHelper(node->left, maxVal);
                node->val = maxVal;
            }
        }
        updateHeight(node);
        node = rotate(node);
        return node;
    }
    bool findHelper(TreeNode* node, int val) {
        if(node == nullptr) return false;
        if(val < node->val) return findHelper(node->left, val);
        else if(val > node->val) findHelper(node->right, val);
        else return true;
    }
    bool isBalanceTreeHelper(TreeNode* node) {
        if(node == nullptr) return true;
        if(abs(balanceFactor(node)) > 1) return false; 
        return isBalanceTreeHelper(node->left) && isBalanceTreeHelper(node->right);
    }
    void inOrder(TreeNode* node) {
        if(node == nullptr) return ;
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }
    TreeNode* root{};
    int size{};
    int heightTree = {};
};


int main() {
    AVLTree T; 
    int n = 20;
    for(int i = 1; i <= n; ++ i) {
        T.insert(i);
        T.print();
        cout << "insert T sz : " << T.getSize() << " , hei : " << T.getHeight() << endl;
    }
    for(int i = 1; i <= n; ++ i) {
        T.remove(i);
        T.print();
        cout << "remove T sz : " << T.getSize() << " , hei : " << T.getHeight() << endl;
    }
    // while(true) {
    //     int x; cin >>x;
    //     T.insert(x);
    //     cout << "T is bal : " << T.isBalanceTree() << endl;
    //     if(T.isBalanceTree()) {
    //         cout << "YES !!!" << endl;
    //     }
    //     else {
    //         cout << "No" << endl;
    //     }
    //     T.print();
    // }

    return 0;
}