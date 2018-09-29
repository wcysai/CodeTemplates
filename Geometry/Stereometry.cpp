#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long double db;
typedef long long ll;
typedef pair<int,int> P;
const db PI=acos(-1.0);
const db eps=1e-10;

int sgn( double ta, double tb)
{
    if(fabs(ta-tb)<eps)return 0;
    if(ta<tb) return -1;
    return 1;
}

class Point
{
public:
    db x,y,z;
    Point(){}
    Point(db tx,db ty,db tz) {x=tx,y=ty,z=tz;}
    bool operator<(const Point &rhs) const
    {
        return x<rhs.x||(x==rhs.x&&y<rhs.y)||(x==rhs.x&&y==rhs.y&&z<rhs.z);
    }
    friend Point operator*(const Point &lhs,const db rhs) {return Point(lhs.x*rhs,lhs.y*rhs,lhs.z*rhs);}
    friend Point operator*(const db lhs,const Point &rhs) {return Point(lhs*rhs.x,lhs*rhs.y,lhs*rhs.z);}
    friend Point operator/(const Point &lhs,const db rhs) {return Point(lhs.x/rhs,lhs.y/rhs,lhs.z/rhs);}
    friend Point operator+(const Point &lhs,const Point &rhs)
    {
        return Point(lhs.x+rhs.x,lhs.y+rhs.y,lhs.z+rhs.z);
    }
    friend Point operator - (const Point &lhs,const Point &rhs)
    {
        return Point(lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z);
    }
    bool operator == (const Point &rhs)const
    {
        return sgn(x,rhs.x)==0&&sgn(y,rhs.y)==0&&sgn(z,rhs.z)==0;
    }
};

db dot(const Point &p, const Point &q)
{
    return p.x*q.x+p.y*q.y+p.z*q.z;
}
db dis2(const Point &p, const Point &q)
{
    return (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y)+(p.z-q.z)*(p.z-q.z);
}
db dis(const Point &p,const Point &q)
{
    return sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y)+(p.z-q.z)*(p.z-q.z));
}
class Line
{
public:
    Point s,e;
    db x,y,z;
    Line(){}
    Line(Point ts,Point te):s(ts),e(te){}
    Line(db _x,db _y,db _z):x(_x),y(_y),z(_z){}

    friend Line operator +(const Line &p,const Line &q) 
    {
        return Line(p.x+q.x,p.y+q.y,p.z+q.z);
    }

    friend Line operator -(const Line &p,const Line &q) 
    {
        return Line(p.x-q.x,p.y-q.y,p.z-q.z);
    }

    friend Line operator /(const Line &p,const Line &q) //xmult
    {
        return Line(p.y*q.z-p.z*q.y,p.z*q.x-p.x*q.z,p.x*q.y-p.y*q.x);
    }

    friend double operator *(const Line &p,const Line &q) //dot
    {
        return p.x*q.x+p.y*q.y+p.z*q.z;
    }

    bool pton()
    {
        x=e.x-s.x;y=e.y-s.y;z=e.z-s.z;
        return true;
    }

    db length()
    {
        return sqrt(x*x+y*y+z*z);
    }
};
db mixed(Line &p, Line &q, Line &r)
{
    return p.x*(q.y*r.z-q.z*r.y)-p.y*(q.x*r.z-q.z*r.x)+p.z*(q.x*r.y-q.y*r.x);
}
db get_angle(Line &p, Line &q)
{
    return atan2((p/q).length(),p*q);
}
class Plane
{
public:
    Point p,q,r;
    db A,B,C,D;  
    Line norm;
    Plane(){}
    Plane(Point tp,Point tq,Point tr):p(tp),q(tq),r(tr){}
    Plane(db _A,db _B,db _C, db _D):A(_A),B(_B),C(_C),D(_D){}

    bool pton()
    {
        Line lp(p,q),lq(p,r);
        lp.pton();lq.pton();
        norm=lp/lq;
        A=norm.x;B=norm.y;C=norm.z;
        D=A*p.x+B*p.y+C*p.z;
        return true;
    }
};
db dist_to_plane(Point &pt, Plane &p)
{
    db A=p.A,B=p.B,C=p.C,D=p.D;
    return (A*pt.x+B*pt.y+C*pt.z+D)/sqrt(A*A+B*B+C*C);
}
db volume(Point &pt, Plane &p)
{
    Line lp(p.p,pt),lq(p.q,pt),lr(p.r,pt);
    lp.pton();lq.pton();lr.pton();
    db v=mixed(lp,lq,lr);return abs(v)/6.0;
}
Point line_plane_intersection(Line &l, Plane &p)
{
    Point A=l.s,B=l.e;
    db vA=volume(A,p),vB=volume(B,p);
    return (A*vB+B*vA)/(vA+vB);
}
int main()
{
    return 0;
}

