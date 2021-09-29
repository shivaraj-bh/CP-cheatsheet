#include<bits/stdc++.h>
using namespace std;
struct RT{
    int n,m;
    bool max_rt;
    vector<int> root;
    vector<vector<int>> tree;
    // [u,v,w] u,v and e_id are in zero based indexing
    vector<array<int,3>> &edges;
    // stores ids of each edge to determine it's index after sorting
    vector<int> &edge_ids;
    RT(vector<array<int,3>> &E,vector<int> &ids,int n_,int m_,bool is_mx):edges(E),edge_ids(ids){
        n = n_,m = m_;
        tree.resize(n+m,{-1,-1});
        root.resize(n+m);
        max_rt = is_mx;
    }
    int find(int u){
        return root[u] = root[u]==u?u:find(root[u]);
    }
    int construct_tree(){
        if(m==0)return 0;
        int u,v,w,e_id;
        if(max_rt)
            sort(edge_ids.begin(),edge_ids.end(),[this](int a,int b){return edges[a][2]<edges[b][2];});
        else
            sort(edge_ids.begin(),edge_ids.end(),[this](int a,int b){return edges[a][2]>edges[b][2];});
        for(int i=0;i<n+m;i++) root[i] = i;
        for(int i=0;i<m;i++){
            e_id = edge_ids[i];
            u = edges[e_id][0],v = edges[e_id][1],w = edges[e_id][2];
            e_id+=n;
            u = find(u),v = find(v);
            // assign u to the left and v to the right child of e_id 
            tree[e_id][0] = u,tree[e_id][1] = v;
            root[u]=root[v] = e_id;
        }
        return edge_ids[m-1]+n;
    }
};
int main(){
    int n = 4,m = 3;
    vector<array<int,3>> E{{0,1,10},{1,2,20},{1,3,15}};
    vector<int> ids(m);
    iota(ids.begin(),ids.end(),0);
    RT rt(E,ids,n,m,true);
    rt.construct_tree();
    for(int i=n;i<n+m;i++){
        cout<<i<<" "<<rt.tree[i][0]<<" "<<rt.tree[i][1]<<"\n";
    }
    return 0;
}