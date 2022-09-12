#include<bits/stdc++.h>
#define MAXN 200000
int n,m,fa[MAXN+10];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	int v,u,i;
	for(i=1;i<=n;i++){
		fa[i]=i;
	}
	int ans=n-1;
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		if(find(u)!=find(v)){
			fa[fa[u]]=fa[v];
			ans--;
		}
		printf("%d\n",ans);
	}
}
