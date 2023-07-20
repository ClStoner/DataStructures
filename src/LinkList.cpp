#include <bits/stdc++.h>
using namespace std;

typedef struct LinkNode
{
    int val;
    struct LinkNode* nxt;
    LinkNode(int _val = 0) : val(_val), nxt(nullptr) {} 
}*LinkList;
class MyLinkedList {
public:
    MyLinkedList() {
        head = new LinkNode(0);
        size = 0;
    }
    ~MyLinkedList() {
        LinkNode* p = head;
        while(p) {
            LinkNode* q = p->nxt;
            delete p;
            p = q;
        }
    }
    int get(int index) {
        if(index < 0 || index >= size) return -1;
        LinkNode* p = head->nxt;
        while(index --) {
            p = p->nxt;
        }
        return p->val;
    }
    void addAtHead(int val) {
        LinkNode* p = new LinkNode(val);
        p->nxt = head->nxt;
        head->nxt = p;
        ++ size;
    }
    
    void addAtTail(int val) {
        LinkNode* tmp = new LinkNode(val);
        LinkNode* p = head;
        while(p->nxt) { p = p->nxt;}
        tmp->nxt = p->nxt;
        p->nxt = tmp;
        ++ size;
    }
    
    void addAtIndex(int index, int val) {
        if(index > size || index < 0) return;
        if(index == size) {
            addAtTail(val); return;
        }
        LinkNode* pre = head;
        LinkNode* cur = head->nxt;
        while(index --) {
            pre = cur; cur = cur->nxt;
        }
        LinkNode* tmp = new LinkNode(val);
        tmp->nxt = cur; pre->nxt = tmp;
        ++ size;
    }
    void deleteAtIndex(int index) {
        if(index < 0 || index >= size) return;
        LinkNode* pre = head;
        LinkNode* cur = head->nxt;
        while(index --) {
            pre = cur; cur = cur->nxt;  
        }
        pre->nxt = cur->nxt;
        delete cur;
        -- size;
    }
    void deleteLastKNde(int k) {
        int idx = 0;
        LinkNode* fast = head->nxt;
        LinkNode* low = head;
        LinkNode* pre;
        while(fast) {
            idx ++;
            if(idx < k) {
                fast = fast->nxt;
                continue;
            }
            pre = low; low = low->nxt;
            fast = fast->nxt;
        }
        pre->nxt = low->nxt; 
        delete low;
    }
    void reverse(){
        if(head->nxt == nullptr || head->nxt->nxt == nullptr)return;
        LinkNode* pre = head->nxt;
        LinkNode* cur = pre->nxt;
        LinkNode* nxt;
        pre->nxt = nullptr;
        while(cur) {
            nxt = cur->nxt;
            cur->nxt = pre;
            pre = cur; cur = nxt;
        }
        head->nxt = pre;
        // cout << "reverse success" << endl;
    }
    /// 递归完成链表翻转
    void reverse2() {
        if(head->nxt == nullptr)return;
        LinkNode* cur = reve(head->nxt);
        head->nxt->nxt = nullptr; 
        head->nxt = cur;
    }

    void print() {
        LinkNode* p = head->nxt;
        while(p) {
            cout << p->val << " ";
            p = p->nxt;
        }
        cout << endl;
    }
    LinkList head;
    int size = 0; // 不带头结点的链表
private:
    LinkNode* reve(LinkList& L) {
        if(L == nullptr || L->nxt == nullptr) return L;
        LinkNode* newL = reve(L->nxt);
        L->nxt->nxt = L; L->nxt = nullptr;
        return newL;
    }
};




int main()
{

    MyLinkedList L;
    int n = 5;
    for(int i = 1; i <= n; ++ i ) {
        L.addAtHead(i);
    }
    L.print();
    L.reverse();
    L.print();
    L.reverse2();
    L.print();

    while(1) {
        int k; cin >> k;
        L.deleteLastKNde(k);
        L.print();
    }
    // for(int i = 1; i <= n; ++ i) {
    //     L.addAtTail(i);
    // }
    // L.print();
    // for(int i = 0; i <= 2 * n; ++ i) {
    //     cout << "index : " << i << " , val " << L.get(i) << endl;
    // }
    // // while(1) {
    // //     int index, val; 
    // //     // cin >> index >> val;
    // //     cin >> index;
    // //     // L.addAtIndex(index, val);
    // //     L.deleteAtIndex(index);
    // //     L.print();
    // // }
    return 0;
}