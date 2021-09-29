#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
struct SparseTable{
    vector<vector<int>> rmq;
    int n,l;
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
int main(){
    vector<int> arr({5,10,7,3,8,1});
    SparseTable st = SparseTable(arr);
    // Expected value = 3
    cout<<st.query(2,3)<<"\n";
    return 0;
}