#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
struct SparseTable{
    vector<vector<int>> rmq;
    int n,l;
    SparseTable(){}
    SparseTable(vector<int> &arr){
        n = (int)arr.size();
        l = __lg(n);
        rmq.assign(n,vector<int>(l+1,-INF));
        for(int i=0;i<n;i++)rmq[i][0] = arr[i];
        build();
    }
    int f(int &a,int &b){
        return min(a,b);
    }
    void build(){
        for(int j=1;j<=l;j++)
            for(int i=0;i+(1<<j)<=n;i++)
                rmq[i][j] = f(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
    }
    int query(int l,int r){
        int j = __lg(r-l+1);
        return f(rmq[l][j],rmq[r-(1<<j)+1][j]);
    }
};
struct LCA{
    vector<vector<int>> adj;
    vector<int> tour,tin,time_to_node;
    SparseTable rmq;
    LCA(vector<vector<int>> &adj,int n,int root=0):adj(adj){
        tin.resize(n);
        time_to_node.resize(2*n);
        dfs(root,root);
        rmq = SparseTable(tour);
    }
    void dfs(int u,int p){
        tin[u] = (int)tour.size();
        time_to_node[tin[u]] = u;
        tour.push_back(tin[u]);
        for(int v:adj[u])
            if(v!=p)dfs(v,u),tour.push_back(tin[u]); 
    }
    int lca(int u,int v){
        if(tin[u]>tin[v])swap(u,v);
        return time_to_node[rmq.query(tin[u],tin[v])];
    }
};
int main(){
    vector<vector<int>> adj({{4},{4},{3},{4,2},{3,1,0}});
    LCA lca = LCA(adj,5,3);
    // Expected value = 4
    cout<<lca.lca(0,1)<<"\n";
    return 0;
}