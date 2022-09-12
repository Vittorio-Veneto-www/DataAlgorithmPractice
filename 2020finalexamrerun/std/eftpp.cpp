#include<bits/stdc++.h>

#include<cctype>

#include<queue>

#define MAXN 10000

#define INF 0x7f7f7f7f

using namespace std;

int f,n,m,ans,c[MAXN*2+10];

struct node{

	int v;

	node *next;

}edge[MAXN*2+10],*adj[MAXN*2+10],*ecnt=&edge[0];

bool vis[MAXN*2+10];

void Read(int &x){

	char c;

	while((c=getchar())&&c!=EOF){

		if(isdigit(c)){

			x=c-'0';

			while((c=getchar())&&isdigit(c))

				x=x*10+c-'0';

			ungetc(c,stdin);

			return;

		}

	}

}

void addedge(int u,int v){

	node *p=++ecnt;

	p->v=v;

	p->next=adj[u];

	adj[u]=p;

}

void read(){

	Read(n),Read(m);

	int i,u,v;

	for(i=1;i<=m;i++){

		Read(u),Read(v);


			addedge(u,v);

			addedge(v,u);

		

	}

}

bool dfs(int u){

	for(node *p=adj[u];p;p=p->next){

		if(vis[p->v])

			continue;

		vis[p->v]=1;

		if(!c[p->v]||dfs(c[p->v])){

			c[u]=p->v;

			c[p->v]=u;

			return 1;

		}

	}

	return 0;

}

void maxmatch(){

	for(int i=1;i<=n;i++){

		memset(vis,0,sizeof vis);

		if(!c[i]&&dfs(i))

			ans++;

	}

}

int main()

{

	read();

	maxmatch();

	printf("%d",n-ans);

}
