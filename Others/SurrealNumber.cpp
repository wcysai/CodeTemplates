double getans(double l,double r)
{
    assert(l<r);
    assert(!(l==0&&r==0));
    if(l==-INF&&r==INF) return 0;
    if(l==-INF) return r-1;
    if(r==INF) return l+1;
    if(l<0&&r>0) return 0.0;
    if(l<0&&r<=0) return -getans(-r,-l);
    double res=1.0;
    while(true)
    {
        double t=0.0;
        while(t<=l) t+=res;
        if(t<r) return t;
        res/=2.0;
    }
    assert(0);
}
