struct edge{int to,del,rev;};
void add_edge(int u,int v){
    G[u].push_back((edge){v,0,(int)G[v].size()});
    G[v].push_back((edge){u,0,(int)G[u].size()-1});
}
vector<int> res;
int now[MAXN];
void hierholzer(int v){//find an eulerian path starting from v, assuming connected
    while(now[v]<(int)G[v].size()){
        auto &e=G[v][now[v]];
        if(e.del) {now[v]++; continue;}
        e.del=1; G[e.to][e.rev].del=1;
        hierholzer(e.to);
        now[v]++;
    }
    res.push_back(v);
}
