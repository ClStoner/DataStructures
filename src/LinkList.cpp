#include <bits/stdc++.h>
using namespace std;
//https://paste.ubuntu.com/p/GqnPqRXDMM/

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class List {
public:

/// 创建链表，以输入为0结束
ListNode* CreateList() {
    ListNode* head = new ListNode(0);
    ListNode* p = head;
    ListNode* q;
    int x;
    while(cin>>x && x) {
        q = new ListNode(x);
        p->next = q; p = p->next;
    }
    return head->next;
}
/// 打印链表
void print(ListNode* head) {
    ListNode* p = head;
    while(p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}
/// 实现链表翻转
ListNode* ReverseList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    // 循环的方式实现链表翻转
    ListNode* pre = nullptr;
    ListNode* cur = head;
    ListNode* nxt;
    while(cur) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
    // // 递归实现链表翻转
    // ListNode* nxt = head->next;
    // ListNode* newHead = ReverseList(nxt);
    // nxt->next = head; head->next = nullptr;
    // return newHead;
}

///链表区间翻转
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(head == nullptr || head->next == nullptr || m == n) return head;
    ListNode* newHead = new ListNode(-1);
    newHead->next = head;
    ListNode* cur = head;
    ListNode* pre = newHead;
    ListNode* nxt;
    for(int i = 1; i < m; ++ i) {
        pre = cur; cur = cur->next;
    }
    for(int i = m; i < n; ++ i) {
        nxt = cur->next;
        cur->next = nxt->next;
        nxt->next = pre->next;
        pre->next = nxt;
    }
    return newHead->next;
}
/// 链表每k个一组翻转
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head == nullptr || head->next == nullptr || k == 1) return head;
    // 递归版本
    int id = 0;
    ListNode* cur = head;
    ListNode* nxt;
    while(cur) {
        id ++;
        if(id == k) break;
        cur = cur->next;
        nxt = cur->next;
    }
    if(id < k) return head;
    cur->next = nullptr;
    nxt = reverseKGroup(nxt, k);
    ListNode* newHead = ReverseList(head);
    head->next = nxt;
    return newHead;

    //// 非递归版本
    // int id = 0;
    // ListNode* newHead = new ListNode(-1);
    // newHead->next = head;
    // ListNode* pre = newHead;
    // ListNode* cur = head;
    // ListNode* nxt;
    
    // while(cur ) {
    //     ++ id;
    //     if(id == k) {
    //         cur->next = nullptr;
    //         pre->next = ReverseList(head);
    //         head->next = nxt;
    //         pre = head;
    //         head = nxt;
    //         cur = nxt;
    //         id = 0;
    //     }
    //     else {
    //         cur = cur->next;
    //         if(cur == nullptr) break;
    //         nxt = cur->next;
    //     }
    // }
    // return newHead->next; 
}
    
    
bool hasCycle(ListNode *head) {
    ListNode* fast = head;
    ListNode* low = head;
    if(head == nullptr) return false;
    while(fast->next == nullptr || fast == nullptr) {
        fast = fast->next->next;
        low = low->next;
        if(low == fast) return true;
    }
    return false;
}
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
    // write code here
    ListNode* head = new ListNode(0);
    ListNode* cur = head;
    while(pHead1 && pHead2) {
        if(pHead1->val < pHead2->val) {
            cur->next = pHead1;
            pHead1 = pHead1->next;
        }
        else {
            cur->next = pHead2;
            pHead2 = pHead2->next;
        }
        cur = cur->next;
    }
    if(pHead2 == nullptr) cur->next = pHead1;
    if(pHead1 == nullptr) cur->next = pHead2;
    return head->next;
}
ListNode* mergeK(vector<ListNode*>& lists, int left, int right) {
    if(left > right) return nullptr;
    if(left == right) return lists[left];
    int mid = (left + right) >> 1;
    ListNode* lhead = mergeK(lists, left, mid);
    ListNode* rhead = mergeK(lists, mid + 1, right);
    return Merge(lhead, rhead);
}
ListNode* mergeKLists(vector<ListNode*>& lists) {
    // write code here
    int n = lists.size();
    return mergeK(lists, 0, n - 1);
}
ListNode* FindKthToTail(ListNode* pHead, int k) {
    // write code here
    ListNode* fast = pHead;
    ListNode* low = nullptr;
    int id = 1;
    while(fast) {
        if(id == k) {
            low = pHead;
        }
        else if(id > k) {
            low = low->next;
        }
        fast = fast->next;
        ++ id;
    }
    return low;
}
ListNode* removeNthFromEnd(ListNode* head, int n) {
    // write code here
    if(n == 0) return head;
    ListNode* fast = head;
    ListNode* low = nullptr;
    ListNode* pre = nullptr;
    if(head == nullptr) return head;
    int id = 1;
    while(fast) {
        if(id == n) {
            low = head;
        }
        else if(id > n) {
            pre = low;
            low = low->next;
        }
        ++ id;
        fast = fast->next;
    }
    if(low == nullptr) return head;
    if(pre == nullptr) return head->next;
    pre->next = low->next;
    delete low;
    return head;
}
ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
    ListNode *p1, *p2;
    p1 = pHead1;
    p2 = pHead2;
    while(p1 != p2) {
        p1 = (p1 == nullptr ? pHead2 : p1->next);
        p2 = (p2 == nullptr ? pHead1 : p2->next);
    }
    return p1;
}
ListNode* EntryNodeOfLoop(ListNode* pHead) {
    // unordered_set<ListNode*> t;
    // ListNode* p = pHead;
    // while(p) {
    //     if(t.find(p) != t.end()) return p;
    //     t.insert(p);
    //     p = p->next;
    // }
    // return nullptr;
    ListNode* fast = pHead;
    ListNode* low = pHead;
    while(fast && fast->next) {
        fast = fast->next->next;
        low = low->next;
        if(low == fast) break;
    }
    if(fast == nullptr || fast->next == nullptr) return nullptr;
    fast = pHead;
    while(fast != low) {
        fast = fast->next;
        low = low->next;
    }
    return low;
}
ListNode* addInList(ListNode* head1, ListNode* head2) {
    // write code here
    if(head1 == nullptr) return head2;
    if(head2 == nullptr) return head1;
    head1 = ReverseList(head1);
    head2 = ReverseList(head2);
    ListNode* node = nullptr;
    int add = 0;
    while(head1 && head2) {
        int x = head1->val + head2->val + add;
        add = x / 10; x = x % 10;
        ListNode* now = new ListNode(x);
        now->next = node;
        node = now;
        head1 = head1->next; head2 = head2->next;
    }
    ListNode* p = nullptr;
    if(head1 == nullptr) {
        p = head2;
    }
    else if(head2 == nullptr) {
        p = head1;
    }
    else p = nullptr;
    while(p) {
        int x = add + p->val;
        add = x / 10; x = x % 10;
        ListNode* now = new ListNode(x);
        now->next = node; node = now;
        p = p->next;
    }
    if(add) {
        ListNode* now = new ListNode(add);
        now->next = node; node = now;
    }
    return node;
}
ListNode* sortInList(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* left = head;
    ListNode* right = head->next->next;
    while(right && right->next) {
        left = left->next;
        right = right->next->next;
    }
    right = left->next;
    left->next = nullptr;
    function<ListNode*(ListNode*, ListNode*)> f;
    f = [&](ListNode* head1, ListNode* head2) {
        ListNode* head = new ListNode(-1);
        ListNode* cur = head;
        while(head1 && head2) {
            if(head1->val < head2->val) {
                cur->next = head1;
                head1 = head1->next;
            }
            else {
                cur->next = head2;
                head2 = head2->next;
            }
            cur = cur->next;
        }
        if(!head1) cur->next = head2;
        if(!head2) cur->next = head1;
        return head->next;
    };
    return f(sortInList(head), sortInList(right));
}
bool isPail(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return true;
    if(head->next->next == nullptr) return head->val == head->next->val;
    ListNode* low = head;
    ListNode* fast = head;
    while(true) {
        low = low->next;
        fast = fast->next;
        if(fast == nullptr) { // 奇数
            low = low->next;
            break;
        }   
        fast = fast->next;
        if(fast == nullptr) break; // 偶数
    }
    ListNode* rhead = ReverseList(low);
    low = head; fast = rhead;
    while(fast) {
        if(low->val != fast->val) return false;
        low = low->next;
        fast = fast->next;
    }
    return true;
}
ListNode* oddEvenList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* odd = new ListNode(-1);
    ListNode* even = new ListNode(-1);
    ListNode* cur = head;
    ListNode* nxt;
    ListNode* cur_odd = odd;
    ListNode* cur_even = even;
    int id = 1;
    while(cur) {
        nxt = cur->next;
        cur->next = nullptr;
        if(id & 1) {// 奇数
            cur_odd->next = cur;
            cur_odd = cur_odd->next;
        }
        else { //偶数
            cur_even->next = cur;
            cur_even = cur_even->next;
        }
        cur = nxt;
        ++ id;
    }
    cur_odd->next = even->next;
    return odd->next;
}
ListNode* deleteDuplicates(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* cur = head;
    ListNode* tmp;
    while(cur && cur->next) {
        if(cur->val == cur->next->val) {
            tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        }
        else cur = cur->next;
    }
    return head;
}
ListNode* deleteDuplicates2(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* newHead = new ListNode(-1);
    newHead->next = head;
    ListNode* pre = newHead;
    ListNode* cur = head;
    ListNode* tmp;
    while(cur && cur->next) {
        if(cur->val != cur->next->val) {
            pre = cur; cur = cur->next;
            continue;
        }
        while(cur->next && cur->val == cur->next->val) {
            tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        }
        tmp = cur->next;
        pre->next = tmp;
        delete cur;
        cur = tmp;
    }
    return newHead->next;
}
};

class BinSearch{
public:
    /**
     * 在无重复数字的升序数组中二分查找目标值，查找成功返回下标，否则返回-1
     * 时间复杂度O(log n)，空间复杂度O(1)
     * 
     * @param nums int整型vector 
     * @param target int整型 
     * @return int整型
     */
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0) return -1;
        int low = 0, high = nums.size();
        while(low <= high) {
            int mid = (low + high) >> 1;
            if(nums[mid] == target) return mid;
            if(nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }
    /**
     * 二维数组中查找，数组满足从左到右递增，从上到下递增，找到返回true，否则返回false
     *  时间复杂度O(n+m), 空间复杂度O(1)
     * 
     * @param target int整型 
     * @param array int整型vector<vector<>> 
     * @return bool布尔型
     */
    bool Find(int target, vector<vector<int> >& array) {
        int n = array.size();
        if(n == 0) return false;
        int m = array[0].size();
        if(m == 0) return false;
        int i = 0, j = m - 1;
        while(i < n && j >= 0) {
            if(array[i][j] == target) return true;
            if(array[i][j] > target) -- j;
            else ++ i;
        }
        return false;
    }
     /**
     * 给定数组，寻找峰值并返回峰值索引（如果多个峰值，放回任意一个即可），峰值严格大于相邻的连个元素     
     * 时间复杂度O(log n)
     * 
     * @param nums int整型vector 
     * @return int整型
     */
    int findPeakElement(vector<int>& a) {
        int n = a.size();
        if(n == 1) return 0;
        if(a[0] > a[1]) return 0;
        if(a[n - 1] > a[n - 2]) return n - 1;
        int low = 1, high = n - 2;
        while(low <= high) {
            int mid = (low + high) >> 1;
            int mx = max(a[mid], max(a[mid - 1], a[mid + 1]));
            if(mx == a[mid]) return mid;
            if(mx == a[mid - 1]) high = mid - 1;
            else low = mid + 1;
        }
        return -1;
    }
    /**
     * 计算数组逆序对
     * 时间复杂度O(n log n )，空间复杂度 O(n)
     * 
     * @param nums int整型vector 
     * @return int整型
     */
    //// 归并排序求逆序对
    // int InversePairs(vector<int>& a) {
    //     // write code here
    //     int mod = 1000000007;
    //     int n = a.size();
    //     vector<int> b(n);
    //     auto merge = [mod, &b](vector<int>& a, int left, int mid, int right) -> int {
    //         int i = left, j = mid + 1;
    //         int k = left;
    //         int ans = 0;
    //         while(i <= mid && j <= right) {
    //             if(a[i] > a[j]) {
    //                 ans = (ans + mid - i + 1) % mod;
    //                 b[k ++] = a[j ++];
    //             }
    //             else {
    //                 b[k ++] = a[i ++];
    //             }
    //         }
    //         if(i > mid) {
    //             while(j <= right) {
    //                 b[k ++] = a[j ++];
    //             }
    //         }
    //         if(j > right ) {
    //             while(i <= mid) {
    //                 b[k ++] = a[i ++];
    //             }
    //         }
    //         for(int i = left; i <= right; ++ i) {
    //             a[i] = b[i];
    //         }
    //         return ans;
    //     };
    //     function<int(vector<int>&, int, int)> f;
    //     f = [&](vector<int>& a, int left, int right) {
    //         if(left >= right) return 0;
    //         int mid = (left + right) >> 1;
    //         int ans = f(a, left, mid);
    //         ans = (ans + f(a, mid + 1, right)) % mod;
    //         return (ans + merge(a, left, mid, right) ) % mod;
    //     };
    //     return f(a, 0, n - 1);
    // }
    //// 树状数组求逆序对
    inline int lowbit(int x) {
        return x &(-x);
    }
    void add(int x) {
        while(x < maxn) {
            c[x] ++;
            x += lowbit(x);
        }
    }
    long long ask(int x) {
        long long ans = 0;
        while(x) {
            ans = (ans + c[x]) % mod;
            x -= lowbit(x);
        }
        return ans;
    }
    void moddd(long long &ans, long long x) {
        ans = (ans + x + mod) % mod;
    }
    int InversePairs(vector<int>& a) {
        int n = a.size();
        for(int i = 0; i < n; ++ i) b[i] = a[i];
        sort(b, b + n);
        int p = unique(b, b + n) - b;
        long long ans = 0;
        for(int i = 0; i < n; ++ i) {
            int x = lower_bound(b, b + p, a[i]) - b + 1;
            add(x);
            moddd(ans, i - ask(x));
        }
        return (int)(ans);
    }
    static const int maxn = 1e5 + 10;
    const long long mod = 1000000007;
    long long c[maxn];
    int b[maxn];


     /**
     * 寻找旋转数组中的最小值
     * 时间复杂度O(log n)， 空间复杂度O(1)
     * 
     * @param nums int整型vector 
     * @return int整型
     */
    int minNumberInRotateArray(vector<int>& a) {
        int n = a.size();
        int low = 0, high = n - 1;
        while(low < high) {
            int mid = (low + high) >> 1;
            if(a[mid] < a[high]) high = mid;
            else if(a[mid] == a[high]) -- high;
            else low = mid + 1;
        }
        return a[low];
    }
    int compare(string version1, string version2) {
        // write code here
        auto preString = [](const string &s) -> vector<int> {
            vector<int> ans;
            int x = 0;
            bool flag = false;
            for(int i = 0; i < s.size(); ++ i) {
                // cout << "x : " << x <<endl;
                if(s[i] >= '1' && s[i] <= '9') {
                    flag = true;
                }
                if(s[i] == '.') {
                    if(flag) ans.push_back(x); x = 0;
                    continue;
                }
                x = 10 * x + (s[i] - '0');
            }
            if(x) ans.push_back(x);
            return ans;
        };
        vector<int> a = preString(version1);
        vector<int> b = preString(version2);
        int n = a.size();
        int m = b.size();
        for(int i = 0; i < min(n, m); ++ i) {
            // cout << a[i] << " " << b[i] << endl;
            if(a[i] < b[i]) return -1;
            if(a[i] > b[i]) return 1;
        }
        if(n < m) {
            for(int i = n; i < m; ++ i) {
                if(b[i]) return -1;
            }
        }
        if(n > m) {
            for(int i = m; i < n; ++ i) {
                if(a[i]) return 1;
            }
        }
        return 0;
    }
};
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};
/*
请实现两个函数，分别用来序列化和反序列化二叉树，不对序列化之后的字符串进行约束，但要求能够根据序列化之后的字符串重新构造出一棵与原二叉树相同的树。

二叉树的序列化(Serialize)是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，从而使得内存中建立起来的二叉树可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树等遍历方式来进行修改，序列化的结果是一个字符串，序列化时通过 某种符号表示空节点（#）

二叉树的反序列化(Deserialize)是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。

*/
class BinaryTree
{
public:
    /**
     * 二叉树先序遍历
     *
     * 
     * @param root TreeNode类 
     * @return int整型vector
     */
    vector<int> preorderTraversal(TreeNode* root) {
        function<void(TreeNode* root, vector<int>&)> f;
        f = [&](TreeNode* root, vector<int>& a) {
            if(root == nullptr) return;
            a.push_back(root->val);
            f(root->left, a);
            f(root->right, a);
        };
        vector<int> ans;
        f(root, ans);
        return ans;
    }
     /**
     * 二叉树中序遍历
     *
     * 
     * @param root TreeNode类 
     * @return int整型vector
     */
    vector<int> inorderTraversal(TreeNode* root) {
        function<void(TreeNode*, vector<int>&)> f;
        f = [&](TreeNode* root, vector<int>& a) {
            if(root == nullptr) return;
            f(root->left, a);
            a.push_back(root->val);
            f(root->right, a);
        };
        vector<int> ans;
        f(root, ans);
        return ans;
    }
     /**
     * 二叉树后序遍历
     *
     * 
     * @param root TreeNode类 
     * @return int整型vector
     */
    vector<int> postorderTraversal(TreeNode* root) {
        function<void(TreeNode*, vector<int>&)>f;
        f = [&](TreeNode* root, vector<int>& a) {
            if(root == nullptr) return;
            f(root->left, a);
            f(root->right, a);
            a.push_back(root->val);
        };
        vector<int> ans;
        f(root, ans);
        return ans;
    }
    /**
     * 二叉树层次遍历
     *
     * 
     * @param root TreeNode类 
     * @return int整型vector<vector<>>
     */
    vector<vector<int> > levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> ans;
        while(!q.empty()) {
            int n = q.size();
            vector<int> tmp;
            for(int i = 0; i < n; ++ i) {
                TreeNode* cur = q.front(); q.pop();
                if(cur == nullptr) continue;
                tmp.push_back(cur->val);
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right); 
            }
            if(tmp.size())ans.push_back(tmp);
        }
        return ans;
    }
    /**
     * 之字形打印二叉树
     *
     * 
     * @param pRoot TreeNode类 
     * @return int整型vector<vector<>>
     */
    vector<vector<int> > Print(TreeNode* pRoot) {
        queue<TreeNode*> q;
        vector<vector<int>> ans;
        if(pRoot == nullptr) return ans;
        q.push(pRoot);
        bool flag = false;
        while(!q.empty()) {
            vector<int> tmp;
            int n = q.size();
            for(int i = 0; i < n; ++ i) {
                TreeNode* cur = q.front(); q.pop();
                tmp.push_back(cur->val);
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            if(flag) reverse(tmp.begin(), tmp.end());
            ans.push_back(tmp);
            flag ^= true;
        }
        return ans;
    }
    /**
     * 二叉树最大深度
     *
     * 
     * @param root TreeNode类 
     * @return int整型
     */
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
    /**
     * 判断是否有从根节点到叶子节点的节点值之和等于 sum 的路径
     *
     * 
     * @param root TreeNode类 
     * @param sum int整型 
     * @return bool布尔型
     */
    bool hasPathSum(TreeNode* root, int sum) {
        if(root == nullptr) return false;
        if(root->left == nullptr && root->right == nullptr && root->val == sum) return true;
        if(hasPathSum(root->left, sum - root->val)) return true;
        if(hasPathSum(root->right, sum - root->val)) return true;
        return false;
    }
    /**
     * 将二叉搜索树转换成一个排序的双向链表
    */
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(!pRootOfTree) return pRootOfTree;
        TreeNode* head = pRootOfTree;
        TreeNode* pre = nullptr;
        while(head->left) {
            head = head->left;
        }
        function<void(TreeNode*)> f;
        f = [&](TreeNode* root) {
            if(!root) return;
            f(root->left);
            root->left = pre;
            if(pre) pre->right = root;
            pre = root;
            f(root->right);
        };
        f(pRootOfTree);
        return head;
    }
    /**
     * 判断二叉树是否是对称的
     *
     * 
     * @param pRoot TreeNode类 
     * @return bool布尔型
     */
    bool isSymmetrical(TreeNode* pRoot) {
        if(!pRoot) return true;
        function<bool(TreeNode*, TreeNode*)> f;
        f = [&](TreeNode* T1, TreeNode* T2) {
            if(!T1 && !T2) return true;
            if((T1 && !T2) || (!T1 && T2)) return false;
            if(T1->val != T2->val) return false;
            return f(T1->left, T2->right) && f(T1->right, T2->left);
        };
        return f(pRoot->left, pRoot->right);
    }
    /**
     * 两颗二叉树，将它们合并成一颗二叉树。合并规则是：都存在的结点，就将结点值加起来，否则空的位置就由另一个树的结点来代替
     *
     * 
     * @param t1 TreeNode类 
     * @param t2 TreeNode类 
     * @return TreeNode类
     */
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if(!t1 && !t2) return nullptr;
        if(t1 && !t2) return t1;
        if(!t1 && t2) return t2;
        TreeNode* root = t1;
        root->val += t2->val;
        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);
        return root;
    }
    /**
     * 二叉树翻转
     *
     * 
     * @param pRoot TreeNode类 
     * @return TreeNode类
     */
    TreeNode* Mirror(TreeNode* pRoot) {
        if(!pRoot) return pRoot;
        Mirror(pRoot->left);
        Mirror(pRoot->right);
        swap(pRoot->left, pRoot->right);
        return pRoot;
    }
    /**
     * 判断是否是搜索二叉树
     *
     * 
     * @param root TreeNode类 
     * @return bool布尔型
     */
    bool isValidBST(TreeNode* root) {
        ////递归的写法
        // TreeNode* pre = nullptr;
        // function<bool(TreeNode*)> f;
        // f = [&](TreeNode* root) {
        //     if(!root) return true;
        //     if(!f(root->left)) return false;
        //     if(pre) {
        //         if(root->val < pre->val) return false;
        //     }
        //     pre = root;
        //     if(!f(root->right)) return false;
        //     return true;
        // };
        // return f(root);
        ////使用栈的写法
        if(!root) return true;
        stack<TreeNode*> s;
        TreeNode* cur = root;
        int pre = INT_MIN;
        while(!s.empty() || cur) {
            while(cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top(); s.pop();
            if(cur->val < pre) return false;
            pre = cur->val;
            cur = cur->right;
        }
        return true;
    }
     /**
     * 判断二叉树是否是完全二叉树
     *
     * 
     * @param root TreeNode类 
     * @return bool布尔型
     */
    bool isCompleteTree(TreeNode* root) {
        if(!root) return true;
        queue<TreeNode*> q;
        TreeNode* cur;
        q.push(root);
        bool flag = false;
        while(!q.empty()) {
            cur = q.front(); q.pop();
            if(flag) {
                if(cur->left || cur->right) return false;
            }
            if(!cur->left && cur->right) return false;
            else if(cur->left && !cur->right) {
                flag = true;
                q.push(cur->left);
            }
            else if(!cur->left && !cur->right) flag = true;
            else {
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return true;
    }
     /**
     * 判断二叉树是否是平衡二叉树
     *
     * 
     * @param pRoot TreeNode类 
     * @return bool布尔型
     */
    bool IsBalanced_Solution(TreeNode* root) {
        if(!root) return true;
        function<int(TreeNode*)> f;
        f = [&](TreeNode* root) {
            if(!root) return 0;
            int ldep = f(root->left);
            if(ldep == -1) return -1;
            int rdep = f(root->right);
            if(rdep == -1) return -1;
            if(abs(ldep - rdep) > 1) return -1;
            return max(ldep, rdep) + 1;
        };
        return f(root) != -1;
    }
    /**
     * 二叉树最佳公共祖先
     *
     * 
     * @param root TreeNode类 
     * @param p int整型 
     * @param q int整型 
     * @return int整型
     */
    int lowestCommonAncestor(TreeNode* root, int p, int q) {
        if(!root) return -1;
        if(root->val == p || root->val == q) return root->val;
        int l = lowestCommonAncestor(root->left, p, q);
        int r = lowestCommonAncestor(root->right, p, q);
        if(l != -1 && r != -1) return root->val;
        if(l == -1 && r != -1) return r;
        if(l != -1 && r == -1) return l;
        return -1;
    }
     /**
     * 根据二叉树前序中序遍历顺序重建二叉树
     *
     * 
     * @param preOrder int整型vector 
     * @param vinOrder int整型vector 
     * @return TreeNode类
     */
    TreeNode* reConstructBinaryTree(vector<int>& preOrder, vector<int>& vinOrder) {
        auto a = preOrder.data();
        auto b = vinOrder.data();
        int n = preOrder.size();

        function<TreeNode*(int*, int*, int)> f;
        f = [&](int* a, int* b, int n) {
            TreeNode* root = nullptr;
            if(n == 0) return root;
            root = new TreeNode(a[0]);
            if(n == 1) {
                return root;
            }
            int mid = 0;
            for(int i = 0; i < n; ++ i) {
                if(a[0] == b[i]) {
                    mid = i; break;
                }
            }
            if(mid) root->left = f(a + 1, b,  mid);
            if(mid < n - 1) root->right = f(a + mid + 1, b + mid + 1, n - mid - 1);
            return root;
        };
        return f(a, b, n);
    }
    /**
     * 根据二叉树的前序和中序恢复二叉树，并打印二叉树的右视图
     *
     * 求二叉树的右视图
     * @param preOrder int整型vector 先序遍历
     * @param inOrder int整型vector 中序遍历
     * @return int整型vector
     */
    vector<int> solve(vector<int>& preOrder, vector<int>& inOrder) {
        int n = preOrder.size();
        const int* a = preOrder.data();
        const int* b = inOrder.data();
        function<TreeNode*(const int*, const int*, int)> f;
        f = [&](const int *a, const int* b, int n) {
            TreeNode* root = nullptr;
            if(n == 0) return root;
            root = new TreeNode(a[0]);
            int mid = 0;
            for(int i = 0; i < n; ++ i) {
                if(a[0] == b[i]) {
                    mid = i; break;
                }
            }
            if(mid) root->left = f(a + 1, b, mid);
            if(mid < n - 1) root->right = f(a + mid + 1, b + mid + 1, n - mid - 1);
            return root;
        };
        TreeNode* root = f(a, b, n);
        vector<int> ans;
        queue<TreeNode*> q;
        if(!root) return ans;
        q.push(root);
        TreeNode* cur;
        while(!q.empty()) {
            n = q.size();
            bool flag = true;
            for(int i = 0; i < n; ++ i) {
                cur = q.front(); q.pop();
                if(i == 0) ans.push_back(cur->val);
                if(cur->right) q.push(cur->right);
                if(cur->left) q.push(cur->left);
            }
        }
        return ans;
    }
    char* Serialize(TreeNode *root) {    
         if (!root) {
            return "#";
        }
        string res = to_string(root->val);
        res.push_back('!');
        string left = Serialize(root->left);
        string right = Serialize(root->right);
        res = res + left + right;
        char *ret = new char[res.length()];
        strcpy(ret, res.c_str());
        return ret;
    }
    TreeNode* f(char *& s) {
        TreeNode* root = nullptr;
        if(*s == '#') {
            s ++;
            return root;
        }
        int x = 0;
        while(*s != '!') {
            x = 10 * x + ((*s - '0'));
            s ++;
        }
        root = new TreeNode(x);
        s ++;
        root->left = f(s);
        root->right = f(s);
        return root;
    }
    TreeNode* Deserialize(char *str) {
        return f(str);
    }

};
class Queue
{
public:
    void push(int val) {
        stack1.push(val);
        if(stack2.empty()) stack2.push(val);
        else {
            int x = stack2.top();
            if(x > val) x = val;
            
            stack2.push(x);
        }
    }
    void pop() {
        stack1.pop(); stack2.pop();
    }
    int top() {
        return stack1.top();
    }
    int min() {
        return stack2.top();
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};


class Solution {
public:
/**
 * 有序括号序列
 *
 * 
 * @param s string字符串 
 * @return bool布尔型
 */
bool isValid(string s) {
    int n = s.size();
    stack<int> st;
    map<char, int> m;
    m['('] = 0; m[')'] = 1; m['['] = 2; m[']'] = 3;  m['{'] = 4; m['}'] = 5; 
    for(int i = 0; i < n; ++ i) {
        int x = m[s[i]];
        if(x & 1) { // 右括号
            if(st.empty()) return false;
            if(st.top() == (x ^ 1)) st.pop();
            else return false;
        }
        else {
            st.push(x);
        }
    }
    return st.size() == 0;
}
/**
 * 在数组中找出其中不去重的最小的 k 个数
 *
 * 
 * @param input int整型vector 
 * @param k int整型 
 * @return int整型vector
 */
vector<int> GetLeastNumbers_Solution(vector<int>& input, int k) {
    int n = input.size();
    int* a = const_cast<int*>(input.data());
    function<void(int*, int, int, int)> f;
    
    f(a, 0, n, k);
    input.resize(k);
    return input;
}
/**
 * 寻找第k大的数
 *
 * 
 * @param a int整型vector 
 * @param n int整型 
 * @param K int整型 
 * @return int整型
 */
int findKth(vector<int>& input, int n, int K) {
    int* a = const_cast<int*>(input.data());
    function<int(int*, int, int, int)> f;
    f = [&](int* a, int low, int high, int K) {
        if(low == high && low == K) return a[low];
        int pivot = a[high - 1];
        int i = low, j = low, k = high;
        while(i < k) {
            if(a[i] < pivot) swap(a[i ++], a[j ++]);
            else if(a[i] > pivot) swap(a[i], a[-- k]);
            else ++ i;
        }
        if(K < j) return f(a, low, j, K);
        if(K >= k) return f(a, k, high, K);
        else return a[j];
    };
    return f(a, 0, n, n - K);
}
/**
 * 中缀表达式求值
 *
 * 返回表达式的值
 * @param s string字符串 待计算的表达式
 * @return int整型
 */
int solve(string s) {
    unordered_map<char, int> mp;
    mp['('] = -1; mp['+'] = 0; mp['-'] = 0; mp['*'] = 1; mp[')'] = 2;
    int n = s.size();
    stack<int> num;
    stack<char> op;
    auto oper = [](int a, int b, char op) -> int {
        if(op == '+') return a + b;
        else if(op == '-') return a - b;
        else return a * b;
    };
    auto cmp = [&mp](char a, char b) -> int {
        if(mp[a] == mp[b]) return 0;
        if(mp[a] > mp[b]) return 1;
        return -1;
    };
    int x = 0;
    num.push(x);
    for(int i = 0; i < n; ++ i) {
        if(isdigit(s[i])) {
            x = 10 * x + (s[i] - '0');
            if(i == n - 1 || !isdigit(s[i +1])) {
                num.push(x);
                cout << "x : " << x <<endl;
                x = 0;
            }
            continue;
        } 
        if(op.empty() || s[i] == '(') op.push(s[i]);
        if(s[i] == ')') {
            while(!op.empty()) {
                int c = op.top(); op.pop();
                if(c == '(') break;
                int a = num.top(); num.pop();
                int b = num.top(); num.pop();
                num.push(oper(b, a, c));
            }
        }
        else {
            while(!op.empty() && cmp(op.top(), s[i]) >= 0) {
                int c = op.top(); op.pop();
                int a = num.top(); num.pop();
                int b = num.top(); num.pop();
                num.push(oper(b, a, c));
            }
            op.push(s[i]);
        }
    }

    while(!op.empty()) {
        int c = op.top(); op.pop();
        int a = num.top(); num.pop();
        int b = num.top(); num.pop();
        num.push(oper(b, a, c));
    }
    return num.top();
}
/**
 * 数组中出现次数超过一半的数
 * 摩尔投票
 * 时间复杂度O(n)，空间复杂度O(1)
 * 
 * @param numbers int整型vector 
 * @return int整型
 */
int MoreThanHalfNum_Solution(vector<int>& numbers) {
    int n = numbers.size();
    int cand = 0;
    int cnt = 0;
    for(int i = 0; i < n; ++ i) {
        if(cnt == 0) {
            cand = numbers[i]; cnt = 1;
        }
        else {
            if(numbers[i] == cand) cnt ++;
            else cnt --;
        }
    }
    return cand;
}
 /**
 * 请在数组中找出两个加起来等于目标值的数的下标
 * 
 * 
 * @param numbers int整型vector 
 * @param target int整型 
 * @return int整型vector
 */
vector<int> twoSum(vector<int>& numbers, int target) {
    unordered_map<int, int> m;
    int n = numbers.size();
    for(int i = 0; i < n; ++ i) {
        if(m.find(target - numbers[i]) != m.end()) {
            return vector<int>{m[target - numbers[i]], i + 1};
        }
        m[numbers[i]] = i + 1;
    }
    return vector<int>{};
}
/**
 * 给定无重复数组，找出其中没有出现的最小的正整数
 * 时间复杂度O(n) 空间复杂度O(1)
 * 
 * @param nums int整型vector 
 * @return int整型
 */
int minNumberDisappeared(vector<int>& a) {
    int n = a.size();
    for(int i = 0; i < n; ++ i) {
        if(a[i] <= 0) a[i] = n + 1;
    }
    for(int i = 0; i < n; ++ i) {
        if(a[i] >= n + 1) continue;
        a[abs(a[i]) - 1] = -(a[abs(a[i]) - 1]);
    }
    int ans = n + 1;
    for(int i = 0; i < n; ++ i) {
        if(a[i] > 0) {
            ans = i + 1; break;
        }
    }
    return ans;

}
/**
 * 找出数组S中所有满足条件的三元组。使得和为0
 * 空间复杂度O(n^2),时间复杂度O(n^2)
 * 
 * @param num int整型vector 
 * @return int整型vector<vector<>>
 */
vector<vector<int> > threeSum(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> ans;
    if(n < 3) return ans;
    sort(a.begin(), a.end());
    for(int x = 0; x < n; ++ x) {
        if(x && a[x] == a[x - 1]) continue;
        int left = x + 1, right = n - 1;
        while(left < right) {
            int sum = a[x] + a[left] + a[right];
            if(sum == 0) {
                ans.push_back(vector<int>{a[x], a[left], a[right]});
                while(left < right && a[left] == a[left + 1]) ++ left;
                while(left < right && a[right] == a[right - 1]) -- right;
                ++ left; -- right;
            } 
            else if(sum < 0) {
                ++ left;
            }
            else {
               -- right;
            }
        }
    }
    return ans;
    
}


};
/// 递归回溯类
class RecuBack
{
public:
/**
 * 没有重复项数字的全排列
 * 空间复杂度O(n!) 时间复杂度O(n!)
 * 
 * @param num int整型vector 
 * @return int整型vector<vector<>>
*/
vector<vector<int> > permute(vector<int>& num) {
    int n = num.size();
    sort(num.begin(), num.end());
    function<void(vector<int>&, vector<int>&, vector<bool>&, vector<vector<int>>& ) > f;
    f = [&](vector<int>&a, vector<int>& tmp, vector<bool> &vis, vector<vector<int>>& ans) {
        if(tmp.size() == n) {
            ans.push_back(tmp);
            return;
        }
        for(int i = 0; i < n; ++ i) {
            if(vis[i]) continue;
            vis[i] = true;
            tmp.push_back(a[i]);
            f(a, tmp, vis, ans);
            vis[i] = false;
            tmp.pop_back();
        }
        
    };
    vector<int> tmp;
    vector<bool> vis(n, false);
    vector<vector<int>> ans;
    f(num, tmp, vis, ans);
    return ans;
}

/**
 *  有重复项数字的全排列
 * 时间复杂度O(n!) 空间复杂度O(n!)
 * 
 * @param num int整型vector 
 * @return int整型vector<vector<>>
 */
vector<vector<int> > permuteUnique(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    function<void(vector<int>&, vector<bool>& )> f;
    f = [&](vector<int>&tmp, vector<bool>& vis) {
        if(tmp.size() == n) {
            res.push_back(tmp);
            return;
        }
        for(int i = 0; i < n; ++ i) {
            if(vis[i] || (i && nums[i] == nums[i - 1] && !vis[i - 1])) continue;
            vis[i] = true;
            tmp.push_back(nums[i]);
            f(tmp, vis);
            vis[i] = false;
            tmp.pop_back();
        }
    };
    vector<int> tmp;
    vector<bool> vis(n, false);
    f(tmp, vis);
    return res;
}
/**
 * 岛屿数量，计算联通分块
 * 时间复杂度O(n*m)
 * 判断岛屿数量
 * @param grid char字符型vector<vector<>> 
 * @return int整型
 */

int solve(vector<vector<char> >& grid) {
    int ans = 0;
    int n = grid.size();
    if(n == 0) return ans;
    int m = grid[0].size();
    if(m == 0) return ans;
    function<bool(int, int)> judge;
    judge = [&](int x, int y) {
        if(x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '1') return true;
        return false;
    };
    function<void(int, int)> dfs;
    int nx[4] = {0, 0, 1, -1};
    int ny[4] = {1, -1, 0, 0};
    dfs = [&](int x, int y) {
        grid[x][y] = '0';
        for(int i = 0; i < 4; ++ i) {
            int xx = x + nx[i];
            int yy = y + ny[i];
            if(judge(xx, yy)) dfs(xx, yy);
        }
    };
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(grid[i][j] == '0') continue;
            dfs(i, j);
            ans ++;
        }
    }
    return ans;
}
/**
 * 字符串排列
 *
 * 时间复杂度O(n!)
 * @param str string字符串 
 * @return string字符串vector
 */
vector<string> Permutation(string str) {
    int n = str.size();
    sort(str.begin(), str.end());
    vector<string> res;
    function<void(string&, vector<bool>&)> f;
    f = [&](string& s, vector<bool>& vis) {
        if(s.size() == n) {
            res.push_back(s);
            return;
        }
        for(int i = 0; i < n; ++ i) {
            if(vis[i] || (i && str[i] == str[i - 1] && !vis[i - 1])) continue;
            vis[i] = true;
            s.push_back(str[i]);
            f(s, vis);
            s.pop_back();
            vis[i] = false;
        }
    };
    vector<bool> vis(n, false);
    string s;
    f(s, vis);
    return res;   
}
/**
 * N皇后问题，N 皇后问题是指在 n * n 的棋盘上要摆 n 个皇后，
    要求：任何两个皇后不同行，不同列也不在同一条斜线上，
    求给一个整数 n ，返回 n 皇后的摆法数。
 * 时间复杂度O(n!)
 * 
 * @param n int整型 the n
 * @return int整型
 */
int Nqueen(int n) {
    // write code here
}

};



int add(int a, int b) {
    return a + b;
}

// Lambda 表达式
auto multiply = [](int a, int b) {
    return a * b;
};
int main()
{
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++ i) cin >> a[i];
    RecuBack sol;
    auto ans = sol.permuteUnique(a);
    int cnt = 0;
    for(auto v : ans) {
        cout << cnt << " : "; 
        for(auto it : v) {
            cout << it << " ";
        }
        cout << endl;
        ++ cnt;
    }
    // cout << sol.threeSum(a) << endl;
}
/*

0.226 0.36
*/