#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long double T;
typedef long double db;
typedef long long ll;
typedef pair<int,int> P;
const T PI=acos(-1.0);
const T eps=1e-10;

int sgn( double ta, double tb)
{
    if(fabs(ta-tb)<eps)return 0;
    if(ta<tb) return -1;
    return 1;
}

class Point
{
public:
    T x,y,z;
    Point(){}
    Point(T tx,T ty,T tz) {x=tx,y=ty,z=tz;}
    db dist2(Point p) {return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)+(z-p.z)*(z-p.z);}
    db dist(Point p) {return sqrt(dist2(p));}
    Point operator+(Point p) {return {x+p.x,y+p.y,z+p.z};}
    Point operator-(Point p) {return {x-p.x,y-p.y,z-p.z};}
    Point operator*(T d) {return {x*d,y*d,z*d};}
    Point operator/(T d) {return {x/d,y/d,z/d};}
    bool operator==(Point p) {return tie(x,y,z)==tie(p.x,p.y,p.z);}
    bool operator!=(Point p) {return !operator==(p);}
    const bool operator<(Point &p)const {return tie(x,y,z)<tie(p.x,p.y,p.z);}
};
Point zero{0,0,0};
T operator|(Point v, Point w) {return v.x*w.x + v.y*w.y + v.z*w.z;}
T sq(Point v) {return v|v;}
db abs(Point v) {return sqrt(sq(v));}
Point unit(Point v) {return v/abs(v);}
db angle(Point v, Point w) 
{
    db cosTheta=(v|w)/abs(v)/abs(w);
    return acos(max((db)-1.0,min((db)1.0,cosTheta)));
}
Point operator*(Point v,Point w) {return {v.y*w.z-v.z*w.y,v.z*w.x-v.x*w.z,v.x*w.y-v.y*w.x};}
T orient(Point p, Point q, Point r, Point s) {return (q-p)*(r-p)|(s-p);}
T orientByNormal(Point p, Point q, Point r, Point n) {return (q-p)*(r-p)|n;}
class Plane 
{
public:
    Point n; T d;
    Plane(){}
    Plane(Point n,T d) : n(n), d(d) {}
    Plane(Point n, Point p) : n(n), d(n|p) {}
    Plane(Point p, Point q, Point r) : Plane((q-p)*(r-p), p) {}
    T side(Point p) {return (n|p)-d;}
    db dist(Point p) {return abs(side(p))/abs(n);}
    Plane translate(Point t) {return {n,d+(n|t)};}
    Plane shiftup(db dist) {return {n,d+dist*abs(n)};}
    Point proj(Point p) {return p-n*side(p)/sq(n);}
    Point refl(Point p) {return p-n*2*side(p)/sq(n);}
};

class Line
{
public:
    Point d,o;
    Line(){}
    Line(Point p,Point q):d(q-p),o(p){}
    Line(Plane p1,Plane p2)
    {
        d=p1.n*p2.n;
        o=(p2.n*p1.d-p1.n*p2.d)*d/sq(d);
    }
    db dist2(Point p) {return sq(d*(p-o))/sq(d);}
    db dist(Point p) {return sqrt(dist2(p));}
    bool cmpProj(Point p,Point q) {return (d|p)<(d|q);}
    Point proj(Point p) {return o+d*(d|(p-o))/sq(d);}
    Point refl(Point p) {return proj(p)*2-p;}
    Point inter(Plane p) {return o-d*p.side(o)/(d|p.n);}
};

db dist(Line l1,Line l2)
{
    Point n=l1.d*l2.d;
    if(n==zero) return l1.dist(l2.o);
    return abs((l2.o-l1.o)|n)/abs(n);
}

Point closestOnL1(Line l1,Line l2) 
{
    Point n2 = l2.d*(l1.d*l2.d);
    return l1.o+l1.d*((l2.o-l1.o)|n2)/(l1.d|n2);
}

db angle(Plane p1,Plane p2)
{
    return angle(p1.n,p2.n);
}

bool is_parallel(Plane p1,Plane p2)
{
    return p1.n*p2.n==zero;
}

bool is_perpendicular(Plane p1,Plane p2)
{
    return (p1.n|p2.n)==0;
}

db angle(Line l1,Line l2)
{
    return angle(l1.d,l2.d);
}

bool is_parallel(Line l1,Line l2)
{
    return l1.d*l2.d==zero;
}

bool is_perpendicular(Line l1,Line l2)
{
    return (l1.d|l2.d)==0;
}

db angle(Plane p, Line l)
{
    return PI/2-angle(p.n,l.d);
}

bool is_parallel(Plane p,Line l)
{
    return (p.n|l.d)==0;
}

bool is_perpendicular(Plane p,Line l)
{
    return p.n*l.d==zero;
}

Line perpthrough(Plane p,Point o) {return Line(o,o+p.n);}

Plane perpthrough(Line l,Point o) {return Plane(l.d,o);}

Point vectorArea2(vector<Point> p)
{
    Point S=zero;
    for(int i=0,n=p.size();i<n;i++) S=S+p[i]*p[(i+1)%n];
    return S;
}

db area(vector<Point> p) {return abs(vectorArea2(p))/2.0;}

class Polyhedron
{
public:
	Polyhedron(){}
    vector<vector<Point> > faces;
    void clear(){faces.clear();}
    db surface_area()
    {
        db S=0;
        for(auto f:faces) S=S+area(f);
        return S;
    }

    struct edge{int v;bool same;};
    void reorient()
    {
        int n=faces.size();
        vector<vector<edge> > G(n);
        map<pair<Point,Point>, int> es;
        for(int u=0;u<n;u++)
        {
            for(int i=0,m=(int)faces[u].size();i<m;i++)
            {
                Point p=faces[u][i],q=faces[u][(i+1)%m];
                if(es.count({p,q})) 
                {
                    int v=es[{p,q}];
                    G[u].push_back({v,true});G[v].push_back({u,true});
                }
                else if(es.count({q,p}))
                {
                    int v=es[{q,p}];
                    G[u].push_back({v,false});G[v].push_back({u,false});
                }
                else es[{p,q}]=u;
            }
        }
        vector<bool> vis(n,false),flip(n);
        flip[0]=false;
        queue<int> q;q.push(0);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(edge e:G[u])
            {
                if(!vis[e.v])
                {
                    vis[e.v]=true;
                    flip[e.v]=flip[u]^e.same;
                    q.push(e.v);
                }
            }
        }
        for(int u=0;u<n;u++)
            if(flip[u])
                reverse(faces[u].begin(),faces[u].end());
    }
    
    db volume()
    {
        double ans=0.0;
        for(auto f:faces) ans+=(vectorArea2(f)|f[0]);
        return abs(ans)/6.0;
    }
};
struct fac
{
    int a,b,c;
    bool ok;
};
struct T3dhull
{
    int n;
    Point ply[MAXN];
    int trianglecnt;
    fac tri[MAXN];
    int vis[MAXN][MAXN];
    double area(Point a,Point b,Point c){return abs((b-a)*(c-a));}
    double volume(Point a,Point b,Point c,Point d){return (b-a)*(c-a)|(d-a);}
    double ptoplane(Point &p,fac &f)
    {
        Point m=ply[f.b]-ply[f.a],n=ply[f.c]-ply[f.a],t=p-ply[f.a];
        return (m*n)|t;
    }
    void deal(int p,int a,int b)
    {
        int f=vis[a][b];
        fac add;
        if(tri[f].ok)
        {
            if((ptoplane(ply[p],tri[f]))>eps) dfs(p,f);
            else
            {
                add.a=b,add.b=a,add.c=p,add.ok=1;
                vis[p][b]=vis[a][p]=vis[b][a]=trianglecnt;
                tri[trianglecnt++]=add;
            }
        }
    }
    void dfs(int p,int cnt)
    {
        tri[cnt].ok=0;
        deal(p,tri[cnt].b,tri[cnt].a);
        deal(p,tri[cnt].c,tri[cnt].b);
        deal(p,tri[cnt].a,tri[cnt].c);
    }
    bool same(int s,int e)
    {
        Point a=ply[tri[s].a],b=ply[tri[s].b],c=ply[tri[s].c];
        return fabs(volume(a,b,c,ply[tri[e].a]))<eps
            &&fabs(volume(a,b,c,ply[tri[e].b]))<eps
            &&fabs(volume(a,b,c,ply[tri[e].c]))<eps;
    }
    void construct()
    {
        int i,j;
        trianglecnt=0;
        if(n<4) return ;
        bool tmp=true;
        for(i=1;i<n;i++) if((abs(ply[0]-ply[i]))>eps){ swap(ply[1],ply[i]); tmp=false; break;}
        if(tmp) return;
        tmp=true;
        for(i=2;i<n;i++)if((abs((ply[0]-ply[1])*(ply[1]-ply[i])))>eps){swap(ply[2],ply[i]); tmp=false; break;}
        if(tmp) return ;
        tmp=true;
        for(i=3;i<n;i++) if(fabs((ply[0]-ply[1])*(ply[1]-ply[2])|(ply[0]-ply[i]))>eps){swap(ply[3],ply[i]); tmp=false; break;}
        if(tmp) return;
        fac add;
        for(i=0;i<4;i++)
        {
            add.a=(i+1)%4,add.b=(i+2)%4,add.c=(i+3)%4,add.ok=1;
            if((ptoplane(ply[i],add))>0) swap(add.b,add.c);//保证逆时针，即法向量朝外，这样新点才可看到。
            vis[add.a][add.b]=vis[add.b][add.c]=vis[add.c][add.a]=trianglecnt;//逆向的有向边保存
            tri[trianglecnt++]=add;
        }
        for(i=4;i<n;i++)//构建更新凸包
        {
            for(j=0;j<trianglecnt;j++)//对每个点判断是否在当前3维凸包内或外(i表示当前点,j表示当前面)
            {
                if(tri[j].ok&&(ptoplane(ply[i],tri[j]))>eps)//对当前凸包面进行判断，看是否点能否看到这个面
                {
                    dfs(i,j); break;//点能看到当前面，更新凸包的面(递归，可能不止更新一个面)。当前点更新完成后break跳出循环
                }
            }
        }
        int cnt=trianglecnt;//这些面中有一些tri[i].ok=0，它们属于开始建立但后来因为在更大凸包内故需删除的，所以下面几行代码的作用是只保存最外层的凸包
        trianglecnt=0;
        for(i=0;i<cnt;i++)
        {
            if(tri[i].ok)
                tri[trianglecnt++]=tri[i];
        }
    }
    double area()//表面积
    {
        double ret=0;
        for(int i=0;i<trianglecnt;i++)
            ret+=area(ply[tri[i].a],ply[tri[i].b],ply[tri[i].c]);
        return ret/2;
    }
    double volume()//体积
    {
        Point p(0,0,0);
        double ret=0;
        for(int i=0;i<trianglecnt;i++)
            ret+=volume(p,ply[tri[i].a],ply[tri[i].b],ply[tri[i].c]);
        return fabs(ret/6);
    }
    int facetri() {return trianglecnt;}//表面三角形数
    int facepolygon()//表面多边形数
    {
        int ans=0,i,j,k;
        for(i=0;i<trianglecnt;i++)
        {
            for(j=0,k=1;j<i;j++)
            {
                if(same(i,j)) {k=0;break;}
            }
            ans+=k;
        }
        return ans;
    }
}hull;


T point_to_segment(Point &p1,Point &p2,Point &p3)
{
    T l=0.0,r=1.0,ans1,ans2;
    while(r-l>1e-14)
    {
        T dis=(r-l)/3.0;
        T lmid=l+dis,rmid=l+2.0*dis;
        Point Q=p2+((p3-p2)*lmid),R=p2+((p3-p2)*rmid);
        ans1=p1.dis2(Q);ans2=p1.dis2(R);
        if(ans1<ans2) r=rmid; else l=lmid;
    }
    return sqrt(min(ans1,ans2));
}
T segment_dist(Point &p1, Point &p2, Point &p3, Point &p4)
{
    T l=0.0,r=1.0,ans1,ans2;
    while(r-l>1e-14)
    {
        T dis=(r-l)/3.0;
        T lmid=l+dis,rmid=l+2.0*dis;
        Point p=p1+((p2-p1)*lmid),q=p1+((p2-p1)*rmid);
        ans1=point_to_segment(p,p3,p4);ans2=point_to_segment(q,p3,p4);
        if(ans1<ans2) r=rmid; else l=lmid;
    }
    return min(ans1,ans2);
}
int main()
{
    return 0;
}

