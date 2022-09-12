#include<iostream>
#include<stdio.h>
#include<queue>
#include<algorithm>
#define WQD 1000000000000000ll
#define maxn 100001
using namespace std;
struct VD
{
 long long v,d;
 bool operator<(const VD&a)const
 {  return a.d<d;
 }
};
struct Edge
{
 long long to,w,next;
};
Edge edge[maxn];
long long head[maxn],u,v,d,m,n,S,num=0;
long long dis[maxn];
void add(long long from,long long to,long long di)
{
 edge[++num].next=head[from];
 edge[num].to=to;
 edge[num].w=di;
 head[from]=num;
}
void dijkstra(long long s)
{
 priority_queue<VD>q;
 for(long long i=1;i<=n;i++) dis[i]=WQD;
 dis[s]=0;
 VD temp;
 temp.d=dis[s];temp.v=s;
 q.push(temp);
 while(!q.empty())
 {
  temp=q.top();
  q.pop();
  long long p=temp.v;
  if(dis[p]<temp.d) continue;
  for(long long i=head[p];i!=0;i=edge[i].next)
   if(dis[edge[i].to]>dis[p]+edge[i].w)
   {
    dis[edge[i].to]=dis[p]+edge[i].w;
    temp.v=edge[i].to;temp.d=dis[edge[i].to];
    q.push(temp);
   }
 }
 return;
}
int main()
{ 
 cin>>n>>m;
 for(long long i=1;i<=m;i++)
  {cin>>u>>v>>d;
  add(u,v,d);
  }
  cin>>S;
 dijkstra(S);
 for(long long i=1;i<=n;i++){
 	if(dis[i]==WQD)
 		printf("-1\n");
 	else
 		printf("%lld\n",dis[i]);
 	}
  return 0;
}
