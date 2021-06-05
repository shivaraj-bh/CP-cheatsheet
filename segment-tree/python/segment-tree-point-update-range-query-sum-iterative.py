"""
created by sbh69840 at 05/06/2021 20:03
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
    def __init__(self, nums: List[Data]):
        self.n = len(nums)
        self.t = [Data() for _ in range(self.n)] + nums
        for i in range(self.n-1,0,-1):
            self.merge(self.t[i],self.t[i<<1],self.t[i<<1|1])
    # Change this to your convinence
    @staticmethod
    def merge(cur:Data,l:Data,r:Data):
        cur.val = l.val+r.val
    def update(self, i: int, val: Data) -> None:
        i+=self.n
        self.t[i] = val
        while i>1:
            self.merge(self.t[i>>1],self.t[i],self.t[i^1])
            i>>=1
    def query(self, l: int, r: int) -> Data:
        res = Data()
        l+=self.n
        r+=self.n+1
        while l<r:
            if l&1:
                self.merge(res,res,self.t[l])
                l+=1
            if r&1:
                r-=1
                self.merge(res,res,self.t[r])
            l>>=1
            r>>=1
        return res
if __name__=="__main__":
    arr = [Data(i) for i in range(1,5)]
    st = SegmentTree(arr)
    print(st.query(0,1))
    st.update(1,Data(5))
    print(st.query(0,1))