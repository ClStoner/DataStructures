#include <bits/stdc++.h>
using namespace std;

/*
平衡二叉树
节点数目为n时，
树高度O(log n)
插入节点复杂度为O(log n)
删除节点复杂度为O(log n)
*/

struct TreeNode //二叉树节点
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
    AVLTree() {}
    ~AVLTree() {
        heightTree = -1;
        size = 0;
        destory(root);
    }
    int getHeight() {return height(root); } //获取当前AVL树高的高度
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
    /// @brief 获取节点的树高，空节点为-1，叶节点为0
    int height(TreeNode* T) {
        return T == nullptr ? -1 : T->height;
    }
    /// @brief 更新节点的高度 
    int updateHeight(TreeNode* T) {
        T->height = max(height(T->left), height(T->right)) + 1;
    }
    /// @brief 获取节点的平衡因子，即左子树高度减去右子树高度 
    int balanceFactor(TreeNode* T) {
        if(T == nullptr) return 0;
        return height(T->left) - height(T->right);
    }
    /// @brief 判断当前二叉搜索树是否为平衡二叉树 
    bool isBalanceTree() {                  //判断是否为平衡二叉树
        return isBalanceTreeHelper(root);
    }
    /// @brief 对当前节点进行右旋转 
    TreeNode* rightRotate(TreeNode* node) {
        TreeNode* child = node->left;
        TreeNode* grandChild = child->right;
        child->right = node; 
        node->left = grandChild;
        updateHeight(node);
        updateHeight(child);
        return child;
    }
    /// @brief 对当前节点进行左旋转 
    TreeNode* leftRotate(TreeNode* node) {
        TreeNode* child = node->right;
        TreeNode* grandChild = child->left;
        child->left = node;
        node->right = grandChild;
        updateHeight(node);
        updateHeight(child);
        return child;
    }
    /// @brief 对当前AVL树进行旋转，维护平衡 
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
    TreeNode* findMinNode(TreeNode* node) {
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    TreeNode* findMaxNode(TreeNode* node) {
        while(node->right != nullptr) {
            node = node->right;
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
                // TreeNode* maxNode = node->left;
                // while(maxNode->right) {
                //     maxNode = maxNode->right;
                // }
                TreeNode* maxNode = findMaxNode(node->left);
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
    void destory(TreeNode* node) {
        if(node == nullptr) return;
        destory(node->left);
        destory(node->right);
        delete node;
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

    return 0;
}