import heapq
from typing import List
class Dijkstra:
    def __init__(self,n:int,m:int):
        self.n = n
        self.m = m
        self.adj = [[] for _ in range(self.n)]
        for i in range(self.m):
            u,v,w = map(int,input().split())
            u-=1;v-=1
            self.adj[u].append((v,w))
            self.adj[v].append((u,w))
        self.dis = [float('inf')]*self.n
        self.parent = [-1]*self.n 
    def restart(self):
        for i in range(self.n):
            self.dis[i] = float('inf')
            self.parent[i] = -1
    def solve(self,s):
        self.restart()
        self.dis[s] = 0
        h = [(0,s)]
        while h:
            w,u = heapq.heappop(h)
            for v in self.adj[u]:
                if self.dis[v[0]]>self.dis[u]+v[1]:
                    self.dis[v[0]] = self.dis[u]+v[1]
                    self.parent[v[0]] = u
                    heapq.heappush(h,(self.dis[v[0]],v[0]))
    def get_shortest_distance(self):
        return self.dis[self.n-1]
    def get_shortest_path(self)->List[int]:
        v = []
        u = self.n-1
        while self.parent[u]!=-1:
            v.append(u+1)
            u = self.parent[u]
        v.append(u+1)
        return v[::-1]
if __name__=="__main__":
    n,m = map(int,input().split())
    dijkstra = Dijkstra(n,m)
    dijkstra.solve(0)
    print(dijkstra.get_shortest_distance())
    print(dijkstra.get_shortest_path())
            
        