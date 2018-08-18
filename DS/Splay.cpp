#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
using namespace std;
struct Node
{   int sz,label,f;
    Node *p,*ch[2];
    Node(int v=0) {p=ch[0]=ch[1]=0;label=v;f=1; }
};
typedef Node* pnode;
int sz(pnode t)
{
    return t?t->sz:0;
}
void pushup(Node *x)
{
    if(!x) return;
    x->sz=x->f+sz(x->ch[0])+sz(x->ch[1]);
}
void rot(Node *x)
{
    Node *y,*z;
    y=x->p,z=y->p;
    int xp=(x==y->ch[0])?0:1,yp=(z)?((y==z->ch[0])?0:1):-1;
    if((y->ch[xp]=x->ch[1^xp]))y->ch[xp]->p=y;
    x->ch[1^xp]=y,y->p=x;
    if((x->p=z))z->ch[yp]=x;
    pushup(y);
}
 
void splay(Node *x)
{
    if(!x)return;
    while (x->p)rot(x);
    pushup(x);
}

void merge (pnode &c,Node *L,Node *R)
{
    if(!L||!R){ c=(!L)?R:L,pushup(c);return;}
    c=L;
    while (c->ch[1])c=c->ch[1];
    splay(c);c->ch[1]=R;if(R) R->p=c;
    pushup(c);
}
Node *find (Node *T,int k,Node *p=0)
{
    if(!T)return p;
    return (T->label==k)?T:(T->label>k)?find(T->ch[0],k,T):find(T->ch[1],k,T);
}
void split (pnode T,pnode & L,pnode & R ,int x)
{
    if(!T){L=R=NULL;return;}
    T=find(T,x);splay(T);
    if(T->label>x)L=T->ch[0],T->ch[0]=0,R=T;
    else R=T->ch[1],T->ch[1]=0,L=T;
    if(L)L->p=0;if(R)R->p=0;
    pushup(L);pushup(R);
}
 
void insert(pnode &T,int x)
{
    pnode n=new Node(x);
    pnode l=0,r=0;
    if(T) 
    {
        T=find(T,x);splay(T);
        if(T->label==x)T->f++;
        else
        {
            split(T,l,r,x),n->ch[0]=l,n->ch[1]=r;
            if(l)l->p=n;
            if(r)r->p=n;
            T=n;
        }
    }
    if(!T) T=n;
    pushup(T);
}
void erase(pnode &n,int k)
{
    if(!n) return;
    n=find(n,k);splay(n);
    if(n->label==k)
    {
        n->f--;
        if(!n->f)
        {
            if(n->ch[0]) n->ch[0]->p=0;
            if(n->ch[1]) n->ch[1]->p=0;
            merge(n,n->ch[1],n->ch[0]);
        }
    }
}
