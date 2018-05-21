#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct SuffixAutomaton 
{
    vector<map<char,int>> edges; 
    vector<int> link;            
    vector<int> length;          
    int last;                    
    SuffixAutomaton(string s) 
    {
        edges.push_back(map<char,int>());
        link.push_back(-1);
        length.push_back(0);
        last=0;
        for(int i=0;i<s.size();i++) 
        {
            edges.push_back(map<char,int>());
            length.push_back(i+1);
            link.push_back(0);
            int r=edges.size()-1;
            int p=last;
            while(p>=0 && edges[p].find(s[i])==edges[p].end()) 
            {
                edges[p][s[i]]=r;
                p=link[p];
            }
            if(p!=-1) 
            {
                int q=edges[p][s[i]];
                if(length[p]+1==length[q]) link[r]=q;
                else 
                {
                    edges.push_back(edges[q]); // copy edges of q
                    length.push_back(length[p]+1);
                    link.push_back(link[q]); // copy parent of q
                    int qq=edges.size()-1;
                    // add qq as the new parent of q and r
                    link[q]=qq;
                    link[r]=qq;
                    // move short classes pointing to q to point to q'
                    while(p>=0 && edges[p][s[i]]==q) 
                    {
                        edges[p][s[i]]=qq;
                        p=link[p];
                    }
                }
            }
            last=r;
        }
        vector<int> terminals;
        int p=last;
        while(p>0) 
        {
            terminals.push_back(p);
            p=link[p];  
        }
    }
};
int main()
{
    return 0;
}