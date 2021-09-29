/* 
created by sbh69840 at 06/05/2021 16:00
*/
#include<bits/stdc++.h>
using namespace std;
struct data{
    //Change this to your convinence
    int val;
};
struct SegmentTree{
    int N;
    vector<data> t;
    vector<data> &arr;
    SegmentTree(vector<data> &a):arr(a){
        N = (int)a.size();
        t.resize(4*N);
        build();
    }
    //Change this to your convinence
    void merge(data &cur,data &l, data &r){
        cur.val = l.val+r.val;
    }
    void build(){
        build_util(1,0,N-1);
    }
    void build_util(int v,int tl,int tr){
        if(tl==tr){
            t[v] = arr[0][tl];
            return;
        }   
        int tm = tl + (tr-tl)/2;
        build_util(2*v,tl,tm);
        build_util(2*v+1,tm+1,tr);
        merge(t[v],t[2*v],t[2*v+1]);
    }
    void update(int pos, data new_val){
        update_util(pos,new_val,1,0,N-1);
    }
    void update_util(int pos, data new_val, int v,int tl,int tr){
        if(tl==tr){
            t[v] = new_val;
            return;
        }
        int tm = tl + (tr-tl)/2;
        if(pos<=tm)
            update_util(pos,new_val,2*v,tl,tm);
        else 
            update_util(pos,new_val,2*v+1,tm+1,tr);
        merge(t[v],t[2*v],t[2*v+1]);
    }
    data query(int l,int r){
        return query_util(l,r,1,0,N-1);
    }
    data query_util(int l, int r, int v, int tl, int tr){
        if(l>r)
            return {};
        if(l==tl&&r==tr)
            return t[v];
        int tm = tl+(tr-tl)/2;
        data res;
        data l_child = query_util(l,min(r,tm),2*v,tl,tm);
        data r_child = query_util(max(tm+1,l),r,2*v+1,tm+1,tr);
        merge(res,l_child,r_child);
        return res;
    }
};
int main(){
    vector<data> a = {{1},{2},{3},{4}};
    SegmentTree st(a);
    cout<<st.query(0,1).val<<endl;
    st.update(1,5);
    cout<<st.query(0,1).val<<endl;
    return 0;
}