#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct heap
{
    priority_queue<int> q1,q2;
    void push(int x) {q1.push(x);}
    void erase(int x) {q2.push(x);}
    int top()
    {
        while(q2.size()&&q1.top()==q2.top()) q1.pop(),q2.pop();
        return q1.top();
    }
    void pop()
    {
        while(q2.size()&&q1.top()==q2.top()) q1.pop(),q2.pop();
        q1.pop();
    }
    int size()
    {
        return q1.size()-q2.size();
    }
};
int main()
{
    return 0;
}
