#include<iostream>
#include<queue>
#include<vector>
#define ll long long
const int N = 1e5;
const ll MAX = 1e15;
using namespace std;
// std::pair is slow because of forwarding initialization in the constructor
struct fast_pair{
    int first;
    ll second;
};
bool operator<(const fast_pair&a,const fast_pair&b){
    return a.second>b.second;
}
vector<fast_pair>adj[N];
int n,m;
ll dis[N];
int parent[N];
void dijkstra(int s){
    for(int i=0;i<n;i++)dis[i]=MAX;
    for(int i=0;i<n;i++)parent[i] = -1;
    dis[s] = 0;
    priority_queue<fast_pair> pq;
    pq.push({s,0});
    int u;
    while(!pq.empty()){
        u = pq.top().first;
        pq.pop();   
        for(const auto &v:adj[u]){
            if(dis[v.first]>dis[u]+v.second){
                dis[v.first] = dis[u]+v.second;
                pq.push({v.first,dis[v.first]});
                parent[v.first] = u;
            }
        }
    }
}
int main(){
    cin>>n>>m;
    int u,v;
    ll w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        u--,v--;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dijkstra(0);
    if(dis[n-1]!=1e15){
        int u = n-1;
        vector<int> v;
        while(parent[u]!=-1){
            v.push_back(u+1);
            u = parent[u];
        }
        v.push_back(u+1);
        cout<<dis[n-1]<<"\n";
        for(int i=(int)v.size()-1;i>=0;i--){
            cout<<v[i]<<" ";
        }
        cout<<"\n";
    }
}