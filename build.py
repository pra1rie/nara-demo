#!/usr/bin/python3
import os


name = 'a.out'
libs = ['SDL2main', 'SDL2', 'SDL2_image', 'SDL2_ttf']
paths = '-I nara'
files = [
	'nara/nara_font',
	'nara/nara_global',
	'nara/nara_sprite',
	'nara/nara_util',
	'nara/nara_window',
	'sauce/game',
	'sauce/main',
]

out = ''
compiler = 'gcc'

print_cmd = False

def comp(f: str):
	global out
	cmd = f'{compiler} -c -o obj/{f.split("/")[-1]}.o {paths} {f}.c'
	if print_cmd:
		print(cmd)
	os.system(cmd)
	out += f'obj/{f.split("/")[-1]}.o '


def link():
	global out
	for lib in libs:
		out += '-l' + lib + ' '
	cmd = f'{compiler} -o {name} {paths} {out}'
	if print_cmd:
		print(cmd)
	os.system(cmd)


if not os.path.exists('obj/'):
	os.mkdir('obj/')

for f in files:
	comp(f)
link()

if print_cmd:
	print(out)

os.system('rm -rf obj/')
os.system(f'./{name}')
