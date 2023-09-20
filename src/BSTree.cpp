#include <iostream>
using namespace std;


/**
 * 二叉搜索树节点
 * 
*/
template<class K, class E>
class BSTNode {
public:
    BSTNode(K _key, E _val, BSTNode* _left = nullptr, BSTNode* _right = nullptr) 
            : key(_key), val(_val), left(_left), right(_right) {}
    ~BSTNode() {}
    K key;              // 关键字
    E val;              //权值
    BSTNode *left;      //左孩子
    BSTNode* right;     //右孩子
};
/**
 * 二叉搜索树
*/
template<class K, class E>
class BSTree {
public:
    BSTree() : mnSize(0) {}
    ~BSTree();
    void preOrder();                                //先序遍历二叉搜索树
    void inOrder();                                 //中序遍历二叉搜索数
    void postOrder();                               //后序遍历二叉搜索数
    void insert(K key, E val);
    void remove(K key);
    void destory();     //销毁二叉搜索树

private:
    void preOrder(BSTNode<K, E>* &root);
    void inOrder(BSTNode<K, E>* &root);
    void postOrder(BSTNode<K, E>* &root);
    void insert(BSTNode<K, E>* &root, K key, E val);
    void remove(BSTNode<K, E>* &root, K key);
    void destory(BSTNode<K, E>* &root);
    BSTNode<K, E>* mpRoot;
    int mnSize;
};
template<class K, class E>
BSTree<K, E>::~BSTree() {
    cout << "BSTree destory" << endl;
    destory();
}
template<class K, class E>
void BSTree<K, E>::destory() {
    destory(mpRoot);
}
template<class K, class E>
void BSTree<K, E>::destory(BSTNode<K, E>* &root) {
    if(root == nullptr) return;
    cout << "destory  " << root->key << " , " << root->val << endl;
    destory(root->left);
    destory(root->right);
    delete root;
    root = nullptr;
}
template<class K, class E>
void BSTree<K, E>::preOrder(){
    cout << "preOrder BSTree" << endl;
    preOrder(mpRoot);
}
template<class K, class E>
void BSTree<K, E>::inOrder() {
    cout << "inOrder BSTree" << endl;
    inOrder(mpRoot);
}
template<class K, class E>
void BSTree<K, E>::postOrder() {
    cout << "postOrder BSTree" << endl;
    preOrder(mpRoot);
}

template<class K, class E>
void BSTree<K, E>::preOrder(BSTNode<K, E>* &root) {
    if(root == nullptr) return;
    cout << "[ " << root->key <<", " << root->val << "]" << endl;
    preOrder(root->left);
    preOrder(root->right);
}
template<class K, class E>
void BSTree<K, E>::inOrder(BSTNode<K, E>* &root) {
    if(root == nullptr) return;
    inOrder(root->left);
    cout << "[ " << root->key <<", " << root->val << "]" << endl;
    inOrder(root->right);
}
template<class K, class E>
void BSTree<K, E>::postOrder(BSTNode<K, E>* &root) {
    if(root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << "[ " << root->key <<", " << root->val << "]" << endl;
}

template<class K, class E>
void BSTree<K, E>::insert(K key, E val) {
    insert(mpRoot, key, val);
}
template<class K, class E>
void BSTree<K, E>::insert(BSTNode<K, E>* &root, K key, E val) {
    ++ mnSize;
    if(root == nullptr) {
        root = new BSTNode<K, E>(key, val, nullptr, nullptr);
        return;
    }
    BSTNode<K, E>* parent = nullptr;
    BSTNode<K, E>* cur = root;
    while(cur && cur->key != key) {
        parent = cur;
        if(key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    if(cur == nullptr) {    //关键字不存在，插入节点
        cur = new BSTNode<K, E>(key, val, nullptr, nullptr);
        if(key < parent->key) parent->left = cur;
        else parent->right = cur;
    }
    else {
        cur->val = val; //  若关键字已经存在，则更新权值
    }   
}
template<class K, class E>
void BSTree<K, E>::remove(K key) {
    remove(mpRoot, key);
}
template<class K, class E>
void BSTree<K, E>::remove(BSTNode<K, E>* &root, K key) {
    BSTNode<K, E>* parent = nullptr;
    BSTNode<K, E>* cur = root;
    while(cur && cur->key != key) {
        parent = cur;
        if(key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    if(cur == nullptr) return; // 没有关键字为key的节点
    if(cur->left && cur->right) {       //当前节点左右孩子都有,将当前节点由其前驱节点替换（即：左子树中关键字最大的节点）
        BSTNode<K, E>* pre = cur->left;
        BSTNode<K, E>* pre_parent = cur;
        while(pre->right != nullptr) {
            pre_parent = pre;
            pre = pre->right;
        }
        if(pre_parent->key == cur->key) pre_parent->left = pre->left;
        else pre_parent->right = pre->left;
        pre->left = cur->left;
        pre->right = cur->right;
        delete cur;
        cur = pre;
    }
    else if(cur->left) {     
        auto tmp = cur->left;                //当前节点只有左孩子
        delete cur;
        cur = tmp;
    }
    else if(cur->right) {               //当前节点只有有右孩子
        auto tmp = cur->right;
        delete cur;
        cur = tmp;
    }
    else {                              //当前节点为叶子节点
        delete cur;
        cur = nullptr;
    }
    if(parent == nullptr) root = cur;
    else {
        if(key < parent->key) parent->left = cur;
        else parent->right = cur;
    }
}
int main()
{
    BSTree<int, int> *T = new BSTree<int, int>();
    T->insert(30, 1);
    T->insert(20, 8);
    T->insert(40, 0);
    T->insert(25, 10);
    T->inOrder();
    T->insert(30, 10);
    T->inOrder();
    // T->destory();
    T->remove(20);
    T->inOrder();
    delete T;
    return 0;
}