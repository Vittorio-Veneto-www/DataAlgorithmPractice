#include<bits/stdc++.h>
using namespace std;
int n,m;
unsigned s1,s2;
unsigned my_rand(){ 
   unsigned s3=s1,s4=s2;
   s1=s4;
   s3^=s3<<23;
   s2=s3^s4^(s3>>17)^(s4>>26);
   return s2+s4;
}
#define MAXN 3000000
unsigned c[MAXN+10];
void update(int x,unsigned val){
	while(x<=n){
		c[x]+=val;
		x+=x&-x;
	}
}
unsigned getsum(int x){
	unsigned ret=0;
	while(x){
		ret+=c[x];
		x^=x&-x; 
	}
	return ret;
}
int main()
{
	cin>>n>>m>>s1>>s2;
	unsigned ans=0;
	while(m--){
		unsigned op,x,y;
		op=2-(my_rand()&1);
		if(op==1){
			x=my_rand()%n+1;
			y=my_rand();
			update(x,y);
		}
		else{
		    x=my_rand()%n+1;
		    y=my_rand()%n+1;
		    if(x>y)
		        swap(x,y);
		    ans+=getsum(y)-getsum(x-1);
		}
	}
	cout<<ans<<endl;
}
