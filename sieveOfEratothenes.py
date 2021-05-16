import random

def sieveMethod(num):
    primeList = []
    
    a = [True] * num                          # Initialize the primality list
    a[0] = a[1] = False

    for (i, isprime) in enumerate(a):
        if isprime:
            primeList.append(i)
            for n in range(i*i, num, i):     # Mark factors non-prime
                a[n] = False

    return primeList

def writeKeys():
    with open('keys.txt', 'w') as f:
        for i in sieveMethod(2 ** 20):
            if i > 2 ** 15:
                f.write(f'{i}\n')

def readKeys():
    with open('keys.txt', 'r+') as f:
        data = []

        for nums in f.readlines():
            data.append(int(nums.strip()))
        
    val = random.choice(data) * random.choice(data)

    return val
