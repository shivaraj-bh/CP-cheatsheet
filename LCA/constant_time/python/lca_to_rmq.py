from typing import List
from math import log2
from math import ceil
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
class LCA:
    def __init__(self,adj:List[List[int]],n:int,root:int=0):
        self.adj = adj 
        self.tin = [0]*n
        self.tour = []
        self.time_to_node = [0]*(2*n)
        self.dfs(root,root)
        self.rmq = SparseTable(self.tour)
    def dfs(self,u:int,p:int)->None:
        self.tin[u] = len(self.tour)
        self.time_to_node[self.tin[u]] = u
        self.tour.append(self.tin[u])
        for v in self.adj[u]:
            if v!=p:
                self.dfs(v,u)
                self.tour.append(self.tin[u])
    def lca(self,u:int,v:int)->int:
        if self.tin[u]>self.tin[v]: u,v = v,u 
        return self.time_to_node[self.rmq.query(self.tin[u],self.tin[v])]
if __name__=="__main__":
    adj = [[4],[4],[3],[4,2],[3,1,0]]
    lca = LCA(adj,5,3)
    # Expected value = 4
    print(lca.lca(0,1))