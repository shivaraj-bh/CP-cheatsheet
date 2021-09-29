/* 
created by sbh69840 at 10/09/2021 16:00
*/
#include<bits/stdc++.h>
using namespace std;
struct SegmentTree{
    int N;
    vector<int> t;
    vector<int> lazy;
    vector<int> &arr;
    SegmentTree(vector<int> &a):arr(a){
        N = (int)a.size();
        t.resize(4*N);
        lazy.resize(4*N);
        build();
    }
    // The merge operation has to be '+'
    void merge(int &root,int &l,int &r){
        root = l + r; 
    }
    void build(){
        build_util(1,0,N-1);
    }
    void build_util(int v,int tl,int tr){
        if(tl==tr){
            t[v] = arr[tl];
            return;
        }
        int tm = tl+(tr-tl)/2;
        build_util(2*v,tl,tm);
        build_util(2*v+1,tm+1,tr);
        merge(t[v],t[2*v],t[2*v+1]);
    }
    void update(int l,int r,int new_val){
        update_util(l,r,new_val,1,0,N-1);
    }
    void update_util(int l,int r,int new_val,int v,int tl,int tr){
        if(lazy[v]!=0){
            t[v]+=(tr-tl+1)*lazy[v];
            if(tl!=tr){
                lazy[2*v] += lazy[v];
                lazy[2*v+1] += lazy[v];
            }   
            lazy[v] = 0;
        }
        if(l>r)return;
        if(l==tl&&r==tr){
            t[v]+=(tr-tl+1)*new_val;
            if(tl!=tr){
                lazy[2*v]+=new_val;
                lazy[2*v+1]+=new_val;
            }
            return;
        }
        int tm = tl + (tr-tl)/2;
        update_util(l,min(r,tm),new_val,2*v,tl,tm);
        update_util(max(tm+1,l),r,new_val,2*v+1,tm+1,tr);
        merge(t[v],t[2*v],t[2*v+1]);
    }
    int query(int l,int r){
        return query_util(l,r,1,0,N-1);
    }
    int query_util(int l,int r,int v,int tl,int tr){
        if(lazy[v]!=0){
            t[v]+=(tr-tl+1)*lazy[v];
            if(tl!=tr){
                lazy[2*v] += lazy[v];
                lazy[2*v+1] += lazy[v];
            }
            lazy[v] = 0;
        }
        if(l>r)return 0;
        if(l==tl&&r==tr)
            return t[v];
        int tm = tl+(tr-tl)/2;
        int res = 0;
        int l_child = query_util(l,min(r,tm),2*v,tl,tm);
        int r_child = query_util(max(tm+1,l),r,2*v+1,tm+1,tr);
        merge(res,l_child,r_child);
        return res;
    }
};
int main(){
    vector<int> a = {1,2,3,4,5};
    SegmentTree st(a);
    cout<<st.query(0,2)<<"\n";
    st.update(0,2,10);
    st.update(2,3,5);
    cout<<st.query(0,3)<<"\n";
    return 0;
}