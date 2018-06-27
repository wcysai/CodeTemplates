#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
typedef unsigned long long ull;
const ull B=1000000007;
bool contain(string a,string b)
{
	int al=a.length(),bl=b.length();
	if(al>bl) return false;
	ull t=1;
	for(int i=0;i<al;i++)
		t*=B;
	ull ah=0,bh=0;
	for(int i=0;i<al;i++) ah=ah*B+a[i];
	for(int i=0;i<al;i++) bh=bh*B+b[i];
	for(int i=0;i+al<=bl;i++)
	{
		if(ah==bh) return true;
		if(i+al<bl) bh=bh*B+b[i+al]-b[i]*t;
	}
	return false;
}