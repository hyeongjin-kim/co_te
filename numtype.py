from itertools import combinations
from collections import defaultdict
#https://school.programmers.co.kr/learn/courses/30/lessons/136797#
import sys
sys.setrecursionlimit(200000)
t = [
[1, 7, 6, 7, 5, 4, 5, 3, 2, 3],
[7, 1, 2, 4, 2, 3, 5, 4, 5, 6],
[6, 2, 1, 2, 3, 2, 3, 5, 4, 5],
[7, 4, 2, 1, 5, 3, 2, 6, 5, 4],
[5, 2, 3, 5, 1, 2, 4, 2, 3, 5],
[4, 3, 2, 3, 2, 1, 2, 3, 2, 3],
[5, 5, 3, 2, 4, 2, 1, 5, 3, 2],
[3, 4, 5, 6, 2, 3, 5, 1, 2, 4],
[2, 5, 4, 5, 3, 2, 3, 2, 1, 2],
[3, 6, 5, 4, 5, 3, 2, 4, 2, 1]
]

a = defaultdict(dict)

def solution(numbers):

    return solve(0, 4, 6, numbers)

def solve(i, l, r, numbers):
    if(i == len(numbers)): return 0
    
    if((l, r) in a[i]):
        return a[i][(l, r)]
    w = float("inf")
    
    num = int(numbers[i])
    
    if(num != r):
        w = min(w, solve(i+1, num, r, numbers) + t[l][num])
    if(num != l):
        w = min(w, solve(i+1, l, num, numbers) + t[num][r])
    
    a[i][(l,r)] = w
    return w
    
