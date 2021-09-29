#include<bits/stdc++.h>
using namespace std;
struct LCA{
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> tin,tout;
    int l,timer;
    LCA(vector<vector<int>> &adj,int n,int root=0):adj(adj){
        tin.resize(n);
        tout.resize(n);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n,vector<int>(l+1));
        dfs(root,root);
    }
    void dfs(int u,int p){
        tin[u] = ++timer;
        up[u][0] = p;
        for(int i=1;i<=l;i++)up[u][i] = up[up[u][i-1]][i-1];
        for(int v:adj[u]){
            if(v!=p)dfs(v,u);
        } 
        tout[u] = ++timer;
    }
    bool is_ancestor(int u,int v){
        return tin[u]<=tin[v]&&tout[u]>=tout[v];
    }
    int lca(int u,int v){
        if(is_ancestor(u,v))return u;
        if(is_ancestor(v,u))return v;
        for(int i=l;i>=0;--i)
            if(!is_ancestor(up[u][i],v))
                u = up[u][i];
        return up[u][0];
    }
};
int main(){
    vector<vector<int>> adj({{1,2},{0,3,4},{0},{1},{1}});
    LCA lca = LCA(adj,5);
    // Expected value = 1
    cout<<lca.lca(3,4)<<"\n";
    return 0;
}