#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct SAM
{
    vector<map<char,int>> edges; 
    vector<int> link;            
    vector<int> length;
    int last;                    
    void init()
    {
        edges.clear(); link.clear(); length.clear(); 
        edges.push_back(map<char,int>());
        link.push_back(-1);
        length.push_back(0);
        last=0;
    }
    int add(int p,char ch) 
    {
        edges.push_back(map<char,int>());
        length.push_back(length[p]+1); link.push_back(0);
        int r=edges.size()-1;
        while(p>=0&&edges[p].find(ch)==edges[p].end()) 
        {
            edges[p][ch]=r;
            p=link[p];
        }
        if(p!=-1) 
        {
            int q=edges[p][ch];
            if(length[p]+1==length[q]) link[r]=q;
            else 
            {
                edges.push_back(edges[q]); 
                length.push_back(length[p]+1);
                link.push_back(link[q]); 
                int qq=edges.size()-1;
                link[q]=qq; link[r]=qq;
                while(p>=0&&edges[p][s[i]]==q) 
                {
                    edges[p][s[i]]=qq;
                    p=link[p];
                }
            }
        }
        return r;
    }
    void build(string &s)
    {
        init();
        int cur=0;
        for(int i=0;i<(int)s.size();i++) cur=add(cur,s[i]);
    }
};
