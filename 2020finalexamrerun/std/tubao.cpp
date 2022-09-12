#include<cstdio>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define MAXN 100000
int n,s[MAXN+10],ans;
void Read(int &x){
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF){
		if(c=='-')
			f=1;
		if(c>='0'&&c<='9'){
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			ungetc(c,stdin);
			if(f)
				x=-x;
			return;
		}
	}
}
struct point{
	int x,y;
	point(){
	}
	point(int xx,int yy){
		x=xx,y=yy;
	}
	point operator-(const point &b)const{
		return point(x-b.x,y-b.y);
	}
	void operator-=(const point&b){
		*this=*this-b;
	}
	bool operator<(const point&b)const{
		if(x==b.x)
			return y<b.y;
		return x<b.x;
	}
}a[MAXN+10];
long long Get_dist(const point &a,const point &b){
	return 1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y);
}
long long cross(const point &a,const point &b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}
void read(){
	Read(n);
	int i;
	bool f1=0,f2=0;
	for(i=1;i<=n;i++)
		Read(a[i].x),Read(a[i].y);
	sort(a+1,a+n+1);
}
void andrew(){
	int tp=0,i,k;
	for(i=1;i<=n;i++){
		while(tp>1&&cross(a[s[tp]]-a[s[tp-1]],a[i]-a[s[tp]])<=0)
			tp--;
		s[++tp]=i;
	}
	k=tp;
	for(i=n-1;i;i--){
		while(tp>k&&cross(a[s[tp]]-a[s[tp-1]],a[i]-a[s[tp]])<=0)
			tp--;
		s[++tp]=i;
	}
	double dist=0;
	long long sqr=0;
	for(int i=2;i<=tp;i++){
		dist+=sqrt(Get_dist(a[s[i]],a[s[i-1]]));
		sqr+=cross(a[s[i-1]],a[s[i]]);
	}
	sqr=abs(sqr);
	printf("%.2f ",dist);
	printf("%lld",sqr/2);
	if(sqr&1)
		printf(".50\n");
	else
		puts(".00");
}
int main()
{
	read();
	andrew();
}
