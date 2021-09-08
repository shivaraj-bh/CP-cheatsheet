class RT:
    def __init__(self,edges,n,m,max_rt):
        self.edges = edges 
        self.n = n 
        self.m = m 
        self.max_rt = max_rt
        self.tree = [[-1,-1] for _ in range(self.n+self.m)]
        self.root = [0]*(n+m)
    def find(self,u):
        if self.root[u]!=u:
            self.root[u] = self.find(self.root[u])
        return self.root[u]
    def construct_tree(self):
        self.edges.sort(key=lambda x:x[2],reverse=not self.max_rt)
        for i in range(n+m):
            self.root[i] = i 
        for u,v,w,e_id in self.edges:
            e_id+=self.n
            u,v = self.find(u),self.find(v)
            if u==v: continue 
            self.tree[e_id][0],self.tree[e_id][1] = u,v 
            self.root[u]=self.root[v]=e_id 
if __name__=="__main__":
    n,m = 4,3
    edges = [[0,1,10,0],[1,2,20,1],[1,3,15,2]]
    rt = RT(edges,n,m,True)
    rt.construct_tree()
    for i in range(n,n+m):
        print(f'par = {i} left = {rt.tree[i][0]} right = {rt.tree[i][1]}')
            
            
