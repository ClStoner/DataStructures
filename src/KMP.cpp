#include <bits/stdc++.h>
using namespace std;

/*
KMP 支持单模式串的匹配
时间复杂度 O(n)
空间复杂度 O(n)

*/
class KMP2{
public:
    vector<int> PrefixFunction(string &s) {
        int n = s.size();
        vector<int> pi(n, 0);
        for(int i = 1; i < n; ++ i) {
            int j = pi[i - 1];
            while(j > 0 && s[i] != s[j]) j = pi[j - 1];
            if(s[i] == s[j]) ++ j;
            pi[i] = j;
        }
        return pi;
    }
    /// @brief 查找串 pattern 在 text 中出现的所有位置
    /// @param text 
    /// @param pattern 
    /// @return 
    vector<int> FindOccurrences(string &text, string &pattern) {
        int sz1 = pattern.size(), sz2 = text.size();
        string s = pattern + '#' + text;
        vector<int> ans;
        vector<int> pi = PrefixFunction(s);
        for(int i = sz1 + 1; i <= sz1 + sz2; ++ i) {
            if(pi[i] == sz1) {
                ans.push_back(i - 2 * sz1);
            }
        }
        return ans;
    }
    vector<int> FindOccurrences2(string &text, string &pattern) {
        int sz1 = pattern.size();
        int sz2 = text.size();
        vector<int> pi = PrefixFunction(pattern);
        int i = 0, j = 0;
        vector<int> ans;
        for(int i = 0, j = 0; i < sz2; ++ i) {
            while(j > 0 && text[i] != pattern[j]) {
                j = pi[j - 1];
            }
            if(text[i] == pattern[j]) {
                j ++;
            }
            if(j == sz1) {
               ans.push_back(i - sz1 + 1);  j = pi[j - 1];
            }
        }
        return ans;
    }
};


class KMP {
public:
    /// @brief 计算字符串前缀函数
    /// @param s 
    /// @return 
    vector<int> PrefixFunction(string &s) {
        int n = s.size();
        vector<int> pi(n, 0);
        for(int i = 1; i < n; ++ i) {
            int j = pi[i - 1];
            while(j && s[i] != s[j]) j = pi[j - 1];
            if(s[i] == s[j]) ++ j;
            pi[i] = j;
        }
        return pi;
    }
    /// @brief 在文本串 text 中查找模式串 pattern 出现的次数，以及返回匹配的下标
    /// @param text 
    /// @param pattern 
    /// @return 
    vector<int> FindOccurence(string &text, string &pattern) {
        int sz1 = text.size(), sz2 = pattern.size();
        vector<int> ans;
        vector<int> pi = PrefixFunction(pattern);
        for(int i = 0, j = 0; i < sz1; ++ i) {
            while(j && text[i] != pattern[j]) j = pi[j - 1];
            if(text[i] == pattern[j]) ++ j;
            if(j == sz2) {
                ans.push_back(i - j + 1); j = pi[j - 1];
            }
        }
        return ans;
    }
};

int main()
{
    string text, pattern; cin >> text >> pattern;
    KMP K;
    vector<int> pi = K.PrefixFunction(pattern);
    vector<int> ans = K.FindOccurence(text, pattern);
    // cout << ans << endl;
    for(auto it : ans) {
        cout << it + 1 << endl;
    }
    for(auto it : pi) {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}