// Link to the problem: https://www.codechef.com/problems/TULIPS
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
const int LOGN = 20;
int DP[LOGN][N];
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
struct ET{
    vector<vector<int>> &adj;
    int timer,children;
    vector<int> st,en;
    ET(vector<vector<int>> &a,int n):adj(a){
        st.resize(n);
        en.resize(n);
        timer = 0;
    }
    void dfs(int u,int p){
        DP[0][u] = p;
        for(int i=1;i<LOGN;i++)DP[i][u] = DP[i-1][DP[i-1][u]];
        st[u] = timer;
        children = 0;
        for(int v:adj[u]){
            if(v!=p&&v!=-1){
                dfs(v,u);
                children++;
            }
        }
        if(children)
            en[u] = timer;
        else 
            en[u] = ++timer;
    }
};
namespace SD {
    const int SQRT = 500;
    map<int, int> mp[N / SQRT];
    int val[N], bl[N];
    int st[N / SQRT], en[N / SQRT], block_val[N / SQRT];
    void build(int n) {
    for (int i = 1; i <= n; i++) {
        bl[i] = i / SQRT;
        if (i == 1 || bl[i] != bl[i - 1]) {
        st[bl[i]] = i;
        }
        en[bl[i]] = i;
        mp[bl[i]][1]++;
        val[i] = block_val[bl[i]] = 1;
    }
    }
    int query_ind(int L, int R, int d, int x) {
    int ret = 0;
    int b = bl[L];
    for (int i = L; i <= R; i++) {
        int curr_val = max(block_val[b], val[i]);
        val[i] = d + x;
        ret += curr_val <= d;
        mp[b][curr_val]--;
        mp[b][val[i]]++;
    }
    return ret;
    }
    int query_blocks(int bl, int br, int d, int x) {
    int ret = 0;
    for (int b = bl; b <= br; b++) {
        for (auto& it : mp[b]) {
        if (it.first <= d) {
            ret += it.second;
        } else
            break;
        }
        mp[b].clear();
        mp[b][d + x] = en[b] - st[b] + 1;
        block_val[b] = d + x;
    }
    return ret;
    }
    int query(int L, int R, int d, int x) {
    if (bl[L] == bl[R]) {
        return query_ind(L, R, d, x);
    } else {
        return query_ind(L, en[bl[L]], d, x) +
            query_blocks(bl[L] + 1, bl[R] - 1, d, x) +
            query_ind(st[bl[R]], R, d, x);
    }
    }

}  // namespace SD

int query(int d,int u,int k,int x,int n,vector<array<int,3>> &E,vector<int> &st,vector<int> &en){
    if(n>1){
        for(int i=LOGN-1;i>=0;i--)
            if(E[DP[i][u]-n][2]<=k)u = DP[i][u];
    }
    return SD::query(st[u]+1,en[u],d,x);
}
int main(){
    int t,u,v,w;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        vector<array<int,3>> E;
        vector<int> edge_id;
        for(int i=0;i<n-1;i++){
            scanf("%d %d %d",&u,&v,&w);
            u--,v--;
            E.push_back({u,v,w});
            edge_id.push_back(i);
        }
        RT rt(E,edge_id,n,n-1,true);
        int tree_root = rt.construct_tree();
        ET et(rt.tree,2*n-1);
        et.dfs(tree_root,tree_root);
        SD::build(n);
        int q,x;
        scanf("%d %d",&q,&x);
        while(q--){
            int d,u,k;
            scanf("%d %d %d",&d,&u,&k);
            printf("%d\n",query(d,u-1,k,x,n,E,et.st,et.en));
            
        }
    }
    return 0;
}