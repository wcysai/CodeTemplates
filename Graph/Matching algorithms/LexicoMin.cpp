#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int x[2*MAXN],y[2*MAXN];
vector<int> L1,L2,R1,R2;
int mini[4*MAXN];
bool visl[MAXN],visr[MAXN];
int matchL[MAXN],matchR[MAXN];
int res[MAXN];
vector<int> ans;
queue<int> que; 
void pushup(int k){
    mini[k]=min(mini[k*2],mini[k*2+1]);
}
bool cmp(int i,int j){
    return x[i]<x[j];
}
void go(int k,int l,int r,int x,int y,int val){
    if(mini[k]>val) return;
    if(l>y||x>r) return;
    if(l==r){
        visr[l]=true;
        if(matchR[l]!=-1&&!visl[matchR[l]]) {visl[matchR[l]]=true; que.push(matchR[l]);}
        mini[k]=INF; return;
    }
    int mid=(l+r)/2;
    go(k*2,l,mid,x,y,val); go(k*2+1,mid+1,r,x,y,val);
    pushup(k);
}
void modify(int k,int l,int r,int pos,int v){
    if(l==r){
        mini[k]=v; return;
    }
    int mid=(l+r)/2;
    if(pos<=mid) modify(k*2,l,mid,pos,v); else modify(k*2+1,mid+1,r,pos,v);
    pushup(k);
}
int get_cover(vector<int> &L,vector<int> &R){//save the answer in L1,L2,R1,R2
    L1.clear(); L2.clear(); R1.clear(); R2.clear();
    if(!R.size()) {L1=L; return 0;}
    sort(L.begin(),L.end(),cmp); sort(R.begin(),R.end(),cmp);
    vector<int> num(L.size(),-1);
    for(int i=0;i<(int)L.size();i++) visl[i]=false,matchL[i]=-1;
    for(int i=0;i<(int)R.size();i++) visr[i]=false,matchR[i]=-1;
    int rsz=(int)R.size(); 
    set<P> s;
    int now=0,res=0;
    for(int i=0;i<(int)L.size();i++){
        int id=L[i];
        while(now<(int)R.size()&&x[R[now]]<=x[id]) {s.insert(P(y[R[now]],now));  now++;}
        //printf("search %d\n",y[id]);
        auto it=s.lower_bound(P(y[id],INF));
        num[i]=now-1;
        //printf("i=%d id=%d num=%d\n",i,id,num[i]);
        if(it!=s.begin()){
            //puts("here");
            --it; res++;
            matchL[i]=it->S;  matchR[it->S]=i;
            s.erase(it); 
        }
        else {visl[i]=true; que.push(i);}
    }
    for(int i=0;i<(int)R.size();i++) modify(1,0,rsz-1,i,y[R[i]]);
    while(que.size()){
        int v=que.front(); que.pop();
        if(matchL[v]){
            go(1,0,rsz-1,0,matchL[v]-1,y[L[v]]); 
            go(1,0,rsz-1,matchL[v]+1,num[v],y[L[v]]); 
        }
        else go(1,0,rsz-1,0,num[v],y[L[v]]);
    }
    for(int i=0;i<(int)R.size();i++) modify(1,0,rsz-1,i,INF);
    for(int i=0;i<(int)L.size();i++) if(visl[i]) L1.push_back(L[i]); else L2.push_back(L[i]);
    for(int i=0;i<(int)R.size();i++) if(visr[i]) R1.push_back(R[i]); else R2.push_back(R[i]);
    return res;
}
vector<int> get_inter(vector<int> &L,vector<int> &R){
    sort(L.begin(),L.end()); sort(R.begin(),R.end());
    vector<int> tmp;
    int now=0;
    for(int i=0;i<(int)L.size();i++){
        while(now<(int)R.size()&&R[now]<L[i]) now++;
        if(now<(int)R.size()&&L[i]==R[now]) {tmp.push_back(L[i]); now++;}
    }
    return tmp;
}
void solve(vector<int> s1,vector<int> s2,vector<int> s3){
    /*puts("--->");
    for(auto x:s1) printf("%d ",x); puts("");
    for(auto x:s2) printf("%d ",x); puts("");
    for(auto x:s3) printf("%d ",x); puts("");
    puts("<---");*/
    if(!s1.size()) {for(auto x:s2) ans.push_back(x); return;}
    if(s1.size()==1){
        vector<int> tmp=s1; for(auto x:s2) tmp.push_back(x);
        for(auto x:s2) ans.push_back(x);
        int z=get_cover(tmp,s3);
        if(get_cover(tmp,s3)==(int)tmp.size()){
            for(auto x:s1) ans.push_back(x);
        }
        return;
    }
    vector<int> X,Y;
    for(int i=0;i<(int)s1.size();i++){
        if(i*2<(int)s1.size()) X.push_back(s1[i]); else Y.push_back(s1[i]);
    }
    vector<int> tmp=X; for(auto x:s2) tmp.push_back(x);
    get_cover(tmp,s3);
    /*puts("------>");
    for(auto x:L1) printf("%d ",x); puts("");
    for(auto x:L2) printf("%d ",x); puts("");
    for(auto x:R1) printf("%d ",x); puts("");
    for(auto x:R2) printf("%d ",x); puts("");
    puts("<------");*/
    sort(L1.begin(),L1.end()); sort(s1.begin(),s1.end());
    vector<int> X1=get_inter(L1,s1),X2=get_inter(L1,s2);
    vector<int> tmpL2=L2,tmpR2=R2;
    solve(move(X1),move(X2),move(R1)); solve(move(Y),move(tmpL2),move(tmpR2));
}
int main()
{
    for(int i=0;i<=400000;i++) mini[i]=INF;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
    scanf("%d",&m);
    for(int i=n+1;i<=n+m;i++) scanf("%d%d",&x[i],&y[i]);
    vector<int> A,B,C;
    for(int i=1;i<=n;i++) C.push_back(i);
    for(int i=n+1;i<=n+m;i++) A.push_back(i);
    solve(move(A),move(B),move(C));
    /*puts("ans");
    for(auto x:ans) printf("%d ",x);
    puts("");*/
    for(auto x:ans) res[x-n]++;
    for(int i=1;i<=m;i++) res[i]+=res[i-1];
    for(int i=1;i<=m;i++) printf("%d\n",res[i]);
    return 0;
}

