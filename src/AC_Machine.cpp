#include <bits/stdc++.h>
using namespace std;
#define mes(a, b) memset(a, b, sizeof(a))


/*
给定n个模式串s，1个匹配串t，，问有多少个模式串s是匹配串t的子串。
*/
const int maxn = 2e3 + 100;

class AC_Machine
{
public:
    int ch[maxn][26], fail[maxn], num[maxn];
    int tot;
    void Insert(string &s) {
        int n = s.size();
        int p = 0;
        for(int i = 0; i < n; ++ i) {
            int x = s[i] - '0';
            if(!ch[p][x]) ch[p][x] = ++ tot;
            p = ch[p][x];
        }
        num[p] ++;
    }
    void Build(){
        queue<int> q;
        for(int i = 0; i < 26; ++ i) {
            if(ch[0][i]) {
                fail[ch[0][i]] = 0; q.push(ch[0][i]);
            }
        }
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int i = 0; i < 26; ++ i) {
                if(ch[u][i]) {
                    fail[ch[u][i]] = ch[fail[u]][i]; q.push(ch[u][i]);
                }
                else {
                    ch[u][i] = ch[fail[u]][i];
                }
            }
        }
    }
    int Query(string &s) {
        int n = s.size();
        int p = 0;
        int ans = 0;
        for(int i = 0; i < n; ++ i) {
            int x = s[i] - '0';
            p = ch[p][x];
            for(int j = p; j && num[j] != -1; j = fail[j]) {
                ans += num[j]; num[j] = -1;
            }
        }
    }
};

int main()
{
    return 0;
}