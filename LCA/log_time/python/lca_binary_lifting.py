from math import log2
from math import ceil
from typing import List 
class LCA:
    def __init__(self,adj:List[List[int]],n:int,root:int=0):
        self.adj = adj 
        self.tin = [0]*n
        self.tout = [0]*n 
        self.timer = 0
        self.l = ceil(log2(n))
        self.up = [[0]*(self.l+1) for _ in range(n)]
        self.dfs(root,root)
    def dfs(self,u:int,p:int)->None:
        self.tin[u] = self.timer
        self.timer+=1
        self.up[u][0] = p 
        for i in range(1,self.l+1):
            self.up[u][i] = self.up[self.up[u][i-1]][i-1]
        for v in self.adj[u]:
            if v!=p: self.dfs(v,u)
        self.timer+=1
        self.tout[u] = self.timer 
    def is_ancestor(self,u:int,v:int)->bool:
        return self.tin[u]<=self.tin[v] and self.tout[u]>=self.tout[v]
    def lca(self,u:int,v:int)->int:
        if self.is_ancestor(u,v):return u
        if self.is_ancestor(v,u):return v 
        for i in range(self.l,-1,-1):
            if not self.is_ancestor(self.up[u][i],v):
                u = self.up[u][i]
        return self.up[u][0] 
if __name__=='__main__':
    adj = [[1,2],[0,3,4],[0],[1],[1]]
    lca = LCA(adj,5)
    # Expected value = 1
    print(lca.lca(3,4))