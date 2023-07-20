import random
import sys
import time

CT = int(sys.argv[1])

print('Generating data ...')

s = time.time()

l = list(range(CT))

m = time.time()
print(f'Generated {CT} numbers in {round(m - s, 3)} seconds.')

random.shuffle(l)

e = time.time()
print(f'Shuffled data in {round(e - m, 3)} seconds.')

print('Done generating data.')
print('Writing data ...')

with open('data/random.txt', 'w') as file:
    for i in range(CT):
        file.write(f'{l[i]}\n')
        if i % (CT / 100) == 0:
            print(f'Writing data: {int(i / (CT / 100))}% complete.')
