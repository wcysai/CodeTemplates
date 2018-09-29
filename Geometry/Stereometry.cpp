#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long double T;
typedef double db;
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
    Point operator+(Point p) {return {x+p.x,y+p.y,z+p.z};}
    Point operator-(Point p) {return {x-p.x,y-p.y,z-p.z};}
    Point operator*(T d) {return {x*d,y*d,z*d};}
    Point operator/(T d) {return {x/d,y/d,z/d};}
    bool operator==(Point p) {return tie(x,y,z)==tie(p.x,p.y,p.z);}
    bool operator!=(Point p) {return !operator==(p);}
    bool operator<(Point p) {return tie(x,y,z)<tie(p.x,p.y,p.z);}
};
Point zero{0,0,0};
T operator|(Point v, Point w) {return v.x*w.x + v.y*w.y + v.z*w.z;}
T sq(Point v) {return v|v;}
db abs(Point v) {return sqrt(sq(v));}
Point unit(Point v) {return v/abs(v);}
db angle(Point v, Point w) 
{
    db cosTheta=(v|w)/abs(v)/abs(w);
    return acos(max(-1.0,min(1.0,cosTheta)));
}
Point operator*(Point v,Point w) {return {v.y*w.z-v.z*w.y,v.z*w.x-v.x*w.z,v.x*w.y-v.y*w.x};}
T orient(Point p, Point q, Point r, Point s) {return (q-p)*(r-p)|(s-p);}
T orientByNormal(Point p, Point q, Point r, Point n) {return (q-p)*(r-p)|n;}
class Plane 
{
public:
    Point n; T d;
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

T point_to_segment(Point &p1,Point &p2,Point &p3)
{
    T l=0.0,r=1.0,ans1,ans2;
    while(r-l>1e-14)
    {
        T dis=(r-l)/3.0;
        T lmid=l+dis,rmid=l+2.0*dis;
        Point Q=p2+((p3-p2)*lmid),R=p2+((p3-p2)*rmid);
        ans1=p1|Q;ans2=p1|R;
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

