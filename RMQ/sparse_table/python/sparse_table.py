from typing import List
from math import log2
class SparseTable:
    def __init__(self,arr:List[int]):
        self.n = len(arr)
        self.l = int(log2(self.n))
        self.rmq = [[-float('inf')]*(self.l+1) for _ in range(self.n)]
        for i in range(self.n):
            self.rmq[i][0] = arr[i]
        self.build()
    def f(self,a:int,b:int):
        return min(a,b)
    def build(self):
        j = 1
        while j<=self.l:
            i = 0
            while i+(1<<j)<=self.n:
                self.rmq[i][j] = self.f(self.rmq[i][j-1],self.rmq[i+(1<<(j-1))][j-1])
                i+=1
            j+=1
    def query(self,l:int,r:int):
        j = int(log2(r-l+1))
        return self.f(self.rmq[l][j],self.rmq[r-(1<<j)+1][j])
if __name__=="__main__":
    arr = [5,10,7,3,8,1]
    st = SparseTable(arr)
    # Expected value = 3
    print(st.query(2,3))