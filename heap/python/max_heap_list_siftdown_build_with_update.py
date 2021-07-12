# Max heap with sift down used for building
# Shivaraj B H - 12th of July 2021
from collections import deque
class Heap2:
    def __init__(self,items):
        self.heap = [None]+items[:]
        self.rank = {}
        for i in range(len(self.heap)-1,0,-1):
            self.down(i)
    def __len__(self):
        return len(self.heap)-1
    def push(self, x):
        """Insert new element x in the heap.
           Assumption: x is not already in the heap"""
        assert x not in self.rank
        i = len(self.heap)
        self.heap.append(x)    # add a new leaf
        self.rank[x] = i
        self.up(i) 
    def pop(self):
        """Remove and return smallest element"""
        root = self.heap[1]
        del self.rank[root]
        x = self.heap.pop()    # remove last leaf
        if self:               # if heap is not empty
            self.heap[1] = x    # move the last leaf
            self.rank[x] = 1    # to the root
            self.down(1)        # maintain heap order
        return root
    # snip}

    # snip{ our_heap_up_down
    def up(self, i):
        """The value of heap[i] has decreased. Maintain heap invariant."""
        x = self.heap[i]
        while i > 1 and x > self.heap[i // 2]:
            self.heap[i] = self.heap[i // 2]
            self.rank[self.heap[i // 2]] = i
            i //= 2
        self.heap[i] = x       # insertion index found
        self.rank[x] = i

    def down(self, i):
        """the value of heap[i] has increased. Maintain heap invariant."""
        x = self.heap[i]
        n = len(self.heap)
        while True:
            left = 2 * i       # climb down the tree
            right = left + 1
            if (right < n and self.heap[right] > x and
                    self.heap[right] > self.heap[left]):
                self.heap[i] = self.heap[right]
                self.rank[self.heap[right]] = i   # move right child up
                i = right
            elif left < n and self.heap[left] > x:
                self.heap[i] = self.heap[left]
                self.rank[self.heap[left]] = i    # move left child up
                i = left
            else:
                self.heap[i] = x   # insertion index found
                self.rank[x] = i
                return

    def update(self, old, new):
        """Replace an element in the heap
        """
        i = self.rank[old]     # change value at index i
        del self.rank[old]
        self.heap[i] = new
        self.rank[new] = i
        if old < new:          # maintain heap order
            self.up(i)
        else:
            self.down(i) 
