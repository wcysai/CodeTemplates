#include<bits/stdc++.h>
#define MAXN 105
using namespace std;
int sz;
const double eps=1e-9;
bool IsZero(double v) 
{
    return abs(v)<eps;
}
enum GAUSS_MODE {
  DEGREE, ABS
};
template <typename T>
void GaussianElimination(vector<vector<T>>&a, int limit, GAUSS_MODE mode=DEGREE) 
{
    if(a.empty()||a[0].empty()) return;
    int h=static_cast<int>(a.size());
    int w=static_cast<int>(a[0].size());
    vector<int> deg(h);
    for(int i=0;i<h;i++) 
        for(int j=0;j<w;j++) 
            deg[i]+=!IsZero(a[i][j]);
    int r=0;
    for(int c=0;c<limit;c++) 
    {
        int id=-1;
        for(int i=r;i<h;i++) 
            if(!IsZero(a[i][c])&&(id==-1||(mode==DEGREE&&deg[i]<deg[id])||(mode==ABS&&abs(a[id][c])<abs(a[i][c]))))
                id=i;
        if(id==-1) continue;
        if(id>r) 
        {
            swap(a[r],a[id]); swap(deg[r],deg[id]);
            for(int j=c;j<w;j++) a[id][j]=-a[id][j];
        }
        vector<int> nonzero;
        for(int j=c;j<w;j++) 
            if(!IsZero(a[r][j])) 
                nonzero.push_back(j);
        T inv_a=1/a[r][c];
        for(int i=r+1;i<h;i++) 
        {
            if(IsZero(a[i][c])) 
                continue;
            T coeff=-a[i][c]*inv_a;
            for (int j:nonzero) 
            {
                if (!IsZero(a[i][j])) deg[i]--;
                a[i][j] += coeff * a[r][j];
                if (!IsZero(a[i][j])) deg[i]++;
            }
        }
        ++r;
    }
    for(r=h-1;r>=0;r--) 
    {
        for(int c=0;c<limit;c++) 
        {
            if(!IsZero(a[r][c])) 
            {
                T inv_a=1/a[r][c];
                for(int i=r-1;i>=0;i--) 
                {
                  if (IsZero(a[i][c])) continue;
                  T coeff = -a[i][c] * inv_a;
                  for (int j = c; j < w; j++) {
                      a[i][j] += coeff * a[r][j];
                  }
                }
              break;
            }
        }
    }
}
 
template <typename T>
vector<T> SolveLinearSystem(vector<vector<T>> a, const vector<T>& b, int w) {
  int h = static_cast<int>(a.size());
  assert(h == static_cast<int>(b.size()));
  if (h > 0) {
    assert(w == static_cast<int>(a[0].size()));
  }
  for (int i = 0; i < h; i++) {
    a[i].push_back(b[i]);
  }
  GaussianElimination(a, w);
  vector<T> x(w, 0);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (!IsZero(a[i][j])) {
        x[j] = a[i][w] / a[i][j]; 
        break;
      }
    }
  }
  return x;
}
