from random import randint
print(6)
n = 10
while n<10000000:
    print(n)
    arr = set()
    while len(arr)<n:
        arr.add(randint(0,1000000000000000000))
    print(*arr)
    n*=10