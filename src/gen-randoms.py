import random
import sys

CT = int(sys.argv[1])

l = list(range(CT))
random.shuffle(l)

with open('data/random.txt', 'w') as file:
    for x in l:
        file.write(f'{x}\n')
