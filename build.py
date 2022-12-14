#!/usr/bin/python3
import os

name = 'a.out'
libs = '-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf'

os.system(f'gcc sauce/*.c -I nara/include -Lnara -lnara {libs} -o {name}')
# os.system(f'gcc nara/*.c sauce/*.c -I nara {libs} -o {name}')
# os.system('rm -rf *.o')
if os.path.exists(name):
    os.system(f'./{name}')

