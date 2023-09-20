#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    Node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    int x, y;
};

template<typename T>
class SharedPtr{
public:
    SharedPtr(T * _ptr = nullptr) : ptr(_ptr) {
        if(ptr) cnt = new int(1);
    }
    SharedPtr(const SharedPtr<T>& rhs) : ptr(rhs.ptr), cnt(rhs.cnt) {
        (*cnt) ++;
    }
    SharedPtr<T> operator = (const SharedPtr<T>& rhs) {
        if(ptr == rhs.ptr) return rhs;
        ptr = rhs.ptr;
        cnt = rhs.cnt;
        (*cnt) ++;
        return *this;
    }
    ~SharedPtr() {
        reset();
    }
    T& operator *() {
        return *ptr;
    }
    T* operator ->() {
        return ptr;
    }
    int getCount() {
        return *cnt;
    }

private:
    void reset() {
        (*cnt) --;
        if(*cnt == 0) {
            cout << "delete " << endl;
            delete ptr;
            delete cnt;
        }
    }
    T *ptr;
    int* cnt;
};

int main()
{
    cout << "Shared Ptr" << endl;
    int *p = new int(5);
    SharedPtr<int> ptr_p(p);
    cout << "cnt : " << ptr_p.getCount() << endl;
    cout << *ptr_p << endl;

    SharedPtr<Node> ptr_node(new Node(2, 3));
    cout << "ptr cnt : " << ptr_node.getCount() << endl;
    cout << "x : " << ptr_node->x << " , y : " << ptr_node->y << endl;
    ptr_node->x = 5; ptr_node->y = 6;
    cout << "x : " << ptr_node->x << " , y : " << ptr_node->y << endl;
    SharedPtr<Node> ptr_node2 = ptr_node;
    cout << "ptr2 cnt : " << ptr_node.getCount() << endl;
    cout << "x : " << ptr_node2->x << " , y : " << ptr_node2->y << endl;
    SharedPtr<Node> ptr_node3(ptr_node);
    cout << "ptr3 cnt : " << ptr_node.getCount() << endl;
    cout << "x : " << ptr_node3->x << " , y : " << ptr_node3->y << endl;
    return 0;
}