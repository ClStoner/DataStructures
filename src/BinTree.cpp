#include <bits/stdc++.h>
using namespace std;

class BinNode{
public:
    BinNode(int _data = 0) : data(_data), lchild(nullptr), rchild(nullptr) {}
    int data;
    BinNode* lchild;
    BinNode* rchild;
};
using BinTree = BinNode*;
/// 先序创建二叉树
void CreateTree(BinTree &T) {
    int x; cin >> x;
    if(x == 0) return;
    T = new BinNode(x);
    CreateTree(T->lchild);
    CreateTree(T->rchild);
}
/// 先序遍历二叉树
void PreTraversal(const BinTree &T) {
    if(T == nullptr) return;
    cout << T->data << " ";
    PreTraversal(T->lchild);
    PreTraversal(T->rchild);
}
/// 中序遍历二叉树
void InTraversal(const BinTree& T) {
    if(T == nullptr) return;
    InTraversal(T->lchild);
    cout << T->data << " ";
    InTraversal(T->rchild);
}
/// 后续遍历二叉树
void PostTraversal(const BinTree& T) {
    if(T == nullptr) return;
    PostTraversal(T->lchild);
    PostTraversal(T->rchild);
    cout << T->data << " ";
}
/// 先序遍历二叉树非递归写法
void IterPreTraversal(const BinTree& T) {
    stack<BinTree> s;
    s.push(T);
    while(!s.empty()) {
        BinTree node = s.top(); s.pop();
        if(node == nullptr) continue;
        cout << node->data << " ";
        if(node->rchild) s.push(node->rchild);
        if(node->lchild) s.push(node->lchild);
    }
    cout << endl;
}
/// 中序遍历二叉树非递归写法
void IterInTraversal(const BinTree& T) {
    stack<BinTree> s;
    BinTree node = T;
    while(node || !s.empty()) {
        while(node) {
            s.push(node);
            node = node->lchild;
        }
        node = s.top(); s.pop();
        cout << node->data << " ";
        node = node->rchild;
    }
    cout <<endl;
}
/// 后续遍历二叉树非递归写法
void IterPostTraversal(const BinTree& T) {
    // 用两个栈实现
    // stack<BinTree> s1, s2;
    // s2.push(T);
    // BinTree node;
    // while(!s2.empty()) {
    //     node = s2.top(); s2.pop();
    //     if(node == nullptr) continue;
    //     s1.push(node);
    //     if(node->lchild) s2.push(node->lchild);
    //     if(node->rchild) s2.push(node->rchild);
    // }
    // while(!s1.empty()) {
    //     node = s1.top(); s1.pop();
    //     cout << node->data << " ";
    // }
    // cout << endl; 

    ///也可以用一个栈实现   
    stack<BinTree> s;
    BinTree node = T;
    BinTree pre = nullptr;
    while(node) {
        s.push(node);
        node = node->lchild;
    }
    while(!s.empty()) {
        node = s.top();
        if(node->rchild == nullptr || node->rchild == pre) {
            cout << node->data << " ";
            pre = node;
            s.pop();
        }
        else {
            node = node->rchild;
            while(node) {
                s.push(node);
                node = node->lchild;
            }
        }
     }
     cout << endl;
}
/// 层次遍历二叉树
void LevelTraversal(const BinTree& T) {
    queue<BinTree> q;
    q.push(T);
    BinTree node;
    while(!q.empty()) {
        node = q.front(); q.pop();
        if(node == nullptr) continue;
        cout << node->data << " ";
        if(node->lchild) q.push(node->lchild);
        if(node->rchild) q.push(node->rchild);
    }
    cout << endl;
}
/// 判断二叉树是否是完全二叉树数
bool IsCompleteBinTree(const BinTree& T) {
    queue<BinTree> q;
    q.push(T);
    bool noChild = false;
    BinTree node;
    while(!q.empty()) {
        node = q.front(); q.pop();
        if(noChild) {
            if(node->lchild || node->rchild) return false;
        }
        if(node->lchild && node->rchild) {
            q.push(node->lchild);
            q.push(node->rchild);
        }
        else if(node->lchild && node->rchild == nullptr) {
            q.push(node->lchild);
            noChild = true;
        }
        else if(node->lchild == nullptr && node->rchild) {
            return false;
        }
        else {
            noChild = true;
        }
    }
    return true;
}
/// 判断二叉树是否是平衡二叉树，即每个节点其左右子树的深度只差不超过1
bool IsBalancedBinTree(const BinTree& T) {
    // auto DepthBinTree = [](const BinTree& T)->int {
        function<int(const BinTree&)> f;
        f = [&](const BinTree& T) {
            if(T == nullptr) return 0;
            int ldep = f(T->lchild);
            if(ldep == -1) return -1;
            int rdep = f(T->rchild);
            if(rdep == -1) return -1;
            if(abs(ldep - rdep) > 1) return -1;
            return max(ldep, rdep) + 1;
        };
        return f(T) != -1;
    // // };
    // return DepthBinTree(T) != -1;
}
/// 将二叉树进行翻转
void ReverseBinTree(BinTree& T) {
    if(T == nullptr) return;
    ReverseBinTree(T->lchild);
    ReverseBinTree(T->rchild);
    swap(T->lchild, T->rchild);
}
/// 二叉树T寻找节点p、q的最近公共祖先
BinNode* FindLeastCommonAncestor(const BinTree& T, const BinNode* p, const BinNode* q) {
    if(T == nullptr) return nullptr;
    if(T->data == p->data || T->data == q->data) return T;
    BinNode* lnode = FindLeastCommonAncestor(T->lchild, p, q);
    BinNode* rnode = FindLeastCommonAncestor(T->rchild, p, q);
    if(lnode && rnode) return T;
    if(lnode && rnode == nullptr) return lnode;
    if(lnode == nullptr && rnode) return rnode;
    return nullptr;
}
/// 依据先序中序遍历顺序构建二叉树， a 先序， b 后序
void CreatePreInOrder(BinTree& T, int* a, int * b, int n) {
    if(n == 0) return;
    T = new BinNode(a[0]);
    // cout << "a0 : " << a[0] << endl;
    if(n == 1) return;
    int mid = 0;
    for(int i = 0; i < n; ++ i) {
        if(b[i] == a[0]) {
            mid = i; break;
        }
    }
    if(mid) CreatePreInOrder(T->lchild, a + 1, b, mid);
    if(mid < n - 1) CreatePreInOrder(T->rchild, a + mid + 1, b + mid + 1, n - mid - 1);
}
/// 依据后续中序遍历的顺序构建二叉树, a 后序， b 中序
void CreatePostInOrder(BinTree& T, int* a, int *b, int n) {
    if(n == 0) return;
    T = new BinNode(a[n - 1]);
    if(n == 1) return;
    int mid = 0;
    for(int i = 0; i < n; ++ i) {
        if(b[i] == a[n - 1]) {
            mid = i; break;
        }
    }
    if(mid) CreatePostInOrder(T->lchild, a, b, mid);
    if(mid < n - 1) CreatePostInOrder(T->rchild, a + mid, b + mid + 1, n - mid - 1);
}



int main()
{
    BinTree T = nullptr;
    int a[100], b[100];
    int n;
    cin >> n;
    for(int i = 0; i < n; ++ i) cin >> a[i];
    for(int i = 0; i < n; ++ i) cin >> b[i];
    CreatePostInOrder(T, a, b, n);
    // CreatePreInOrder(T, a, b, n);
    cout << endl;
    cout << "PreOrder Binary Tree " << endl;
    PreTraversal(T);
    cout << endl;
    IterPreTraversal(T);
    cout << endl << endl;

    cout << "InOrder Binary Tree " << endl;
    InTraversal(T);
    cout << endl;
    IterInTraversal(T);
    cout << endl << endl;

    cout << "PostOrder Binary Tree " << endl;
    PostTraversal(T);
    cout << endl;
    IterPostTraversal(T);
    cout << endl << endl;

    cout << "LevelOrder Binary Tree" << endl;
    LevelTraversal(T);
    cout << endl << endl;


    if(IsCompleteBinTree(T)) {
        cout << "YES, is a Complete Binary Tree !!" << endl << endl;
    }
    else {
        cout << "NO, don't a Complete Binary Tree!!" << endl << endl;
    }

    if(IsBalancedBinTree(T)) {
        cout << "YES, This is a Balanced Binary Tree !!" << endl << endl;
    }
    else {
        cout << "NO, This isn't a Balanced Binary Tree !!" << endl << endl;
    }

    // ReverseBinTree(T);
    // PreTraversal(T);
    // cout <<endl << endl;
    while(true) {
        int x, y; cin >> x >> y;
        BinNode* p = new BinNode(x);
        BinNode* q = new BinNode(y);
        auto lca = FindLeastCommonAncestor(T, p, q);
        if(lca) {
            cout << "lca : " << lca->data << endl;
        }
    }
    return 0;
}
/*

1 2 4 0 0 0 3 0 5 0 0 

1 2 4 7 0  0 0 5 10 0 0 11 0 0 6 8 0 0 9 12 0 0 0 


1 2 3 0 0 4 0 0 5 0 0 

1 2 3 0 0 0 5 4 0 0 0
1 2 3 6 0 0 0 4 0 0 5 0 0 

11
前序:
1 2 4 7 5 10 11 6 8 9 12
中序
7 4 2 10 5 11 1 8 6 12 9
后续
7 4 10 11 5 2 8 12 9 6 1
*/