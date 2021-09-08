# Reachability Tree
Also known as Edge Decomposition Tree beacause we construct a new tree with 2n-1 nodes where the internal nodes represent the edges with the root node being either the edge with maximum edge weight or minimum edge weight depending on whether it is an max RT or min RT. <br>
Properties <br>
1. Maximum edge weight in a path from u to v is LCA(u,v) in the max RT and vice versa.