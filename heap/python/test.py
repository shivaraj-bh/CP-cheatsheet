from max_heap_list_siftdown_build_with_update import Heap2 
from max_heap_list_with_update import Heap1
import timeit,functools
def test1(arr):
    h1 = Heap1(arr)
def test2(arr):
    h2 = Heap2(arr)
t = int(input())
while t:
    t-=1
    n = int(input())
    arr = list(map(int,input().split()))
    build_with_up = timeit.Timer(functools.partial(test1,arr))
    build_with_down = timeit.Timer(functools.partial(test2,arr))
    build_with_up = build_with_up.timeit(5)
    build_with_down = build_with_down.timeit(5)
    print(f'{build_with_up = } {build_with_down = }') 