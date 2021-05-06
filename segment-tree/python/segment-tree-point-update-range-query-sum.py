"""
created by sbh69840 at 06/05/2021 13:45
"""
from typing import List
# Change this class to your convinence
class Data:
    def __init__(self,val:int=0):
        self._val:int = val
    @property
    def val(self)->int:
        return self._val
    @val.setter 
    def val(self,new_val:int):
        self._val = new_val
    def __str__(self)->str:
        return str(self._val)
class SegmentTree:
    def __init__(self, arr:List[Data]):
        self._n = len(arr)
        self._arr = arr
        self._t = [Data() for _ in range(4*self._n)]
        self.build()
    def build(self):
        self.build_util(1,0,self._n-1)
    # Change this to your convinence
    @staticmethod
    def merge(cur:Data,l:Data,r:Data):
        cur.val = l.val+r.val
    """
    :v: index of the node in binary tree
    :tl: left index of current range in the tree
    :tr: right index of current range in the tree
    """
    def build_util(self,v:int,tl:int,tr:int):
        if tl==tr:
            self._t[v].val = self._arr[tl].val
            return
        tm = (tl+tr)//2
        self.build_util(2*v,tl,tm)
        self.build_util(2*v+1,tm+1,tr)
        self.merge(self._t[v],self._t[2*v],self._t[2*v+1])
    def update(self,pos:int,new_val:Data):
        self.update_util(pos,new_val,1,0,self._n-1)
    def update_util(self,pos:int,new_val:Data,v:int,tl:int,tr:int):
        if tl==tr:
            self._t[v].val = new_val
            return 
        tm = (tl+tr)//2
        if pos<=tm:
            self.update_util(pos,new_val,2*v,tl,tm)
        else:
            self.update_util(pos,new_val,2*v+1,tm+1,tr)
        self.merge(self._t[v],self._t[2*v],self._t[2*v+1])
    def query(self,l:int,r:int)->Data:
        return self.query_util(l,r,1,0,self._n-1)
    def query_util(self,l:int,r:int,v:int,tl:int,tr:int)->Data:
        if l>r:
            return Data()
        if l==tl and r==tr:
            return self._t[v]
        tm = (tl+tr)//2
        res = Data()
        self.merge(res,self.query_util(l,min(r,tm),2*v,tl,tm),self.query_util(max(tm+1,l),r,2*v+1,tm+1,tr))
        return res
if __name__=="__main__":
    arr = [Data(i) for i in range(1,5)]
    st = SegmentTree(arr)
    print(st.query(0,1))
    st.update(1,5)
    print(st.query(0,1))
    
            
            
        