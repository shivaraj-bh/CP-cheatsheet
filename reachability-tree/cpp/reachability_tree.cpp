#include<bits/stdc++.h>
using namespace std;
struct RT{
    int n,m;
    bool max_rt;
    vector<int> root;
    vector<pair<int,int>> tree;
    // [u,v,w,e_id] u,v and e_id are in zero based indexing
    vector<array<int,4>> &edges;
    RT(vector<array<int,4>> &E,int N,int M,bool is_mx):edges(E){
        n = N,m = M;
        tree.resize(n+m,make_pair(-1,-1));
        root.resize(n+m);
        max_rt = is_mx;
    }
    int find(int u){
        return root[u] = root[u]==u?u:find(root[u]);
    }
    void construct_tree(){
        int u,v,w,e_id;
        if(max_rt)
            sort(edges.begin(),edges.end(),[](array<int,4> a,array<int,4> b){return a[2]<b[2];});
        else
            sort(edges.begin(),edges.end(),[](array<int,4> a,array<int,4> b){return a[2]>b[2];});
        for(int i=0;i<n+m;i++) root[i] = i;
        for(auto edge:edges){
            u = edge[0],v = edge[1],w = edge[2],e_id = edge[3]+n;
            u = find(u),v = find(v);
            if(u==v)continue;
            // assign u to the left and v to the right child of e_id 
            tree[e_id].first = u,tree[e_id].second = v;
            root[u] = root[v] = e_id;
        }
    }
};
int main(){
    int n = 4,m = 3;
    vector<array<int,4>> E{{0,1,10,0},{1,2,20,1},{1,3,15,2}};
    
    RT rt(E,n,m,true);
    rt.construct_tree();
    for(int i=n;i<n+m;i++){
        cout<<i<<" "<<rt.tree[i].first<<" "<<rt.tree[i].second<<"\n";
    }
    return 0;
}