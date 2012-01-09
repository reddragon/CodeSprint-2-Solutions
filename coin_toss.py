from decimal import *
import sys

base = {}
def populate():
	base[1] = 2;
	
	for i in range(2,1005):
		base[i] = 2*(base[i-1]+1)
		

def solve(cur, target):
	if(cur == target):
		return 0
	
	return 1 + solve(cur+1, target)/2 + base[target]/2
	

sys.setrecursionlimit(1500)
populate()
line = sys.stdin.readline()
n = int(line.split()[0])

for i in range(1,n+1):
	line = sys.stdin.readline()
	target = int(line.split()[0])
	cur = int(line.split()[1])
	print (str(solve(cur,target)) +  ".00")
