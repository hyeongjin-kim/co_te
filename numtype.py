from itertools import combinations
from collections import defaultdict
#https://school.programmers.co.kr/learn/courses/30/lessons/136797#
import sys
sys.setrecursionlimit(200000)
# (i,j) : 숫자 i에서 숫자 j를 누르는데 필요한 가중치
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

a = defaultdict(dict) # a[i][(l,r)] = i번째 숫자를 눌러야하고, 왼손은 l, 오른손은 r에 있을때 남은 모든 숫자를 누르는데 필요한 가중치

def solution(numbers):
    return solve(0, 4, 6, numbers)
    
#i번째 숫자를 눌러야하고, 왼손은 l, 오른손을 r에 있음
def solve(i, l, r, numbers):
    if(i == len(numbers)): return 0 #다 눌러서 누를 필요 X
    
    if((l, r) in a[i]): #저장되어 있음
        return a[i][(l, r)]
    w = float("inf") #필요한 가중치를 최대로 설정
    
    num = int(numbers[i]) #누를 숫자
    
    if(num != r): #왼손이 이동하는 경우
        w = min(w, solve(i+1, num, r, numbers) + t[l][num])
    if(num != l): #오른손이 이동하는 경우
        w = min(w, solve(i+1, l, num, numbers) + t[num][r])
    
    a[i][(l,r)] = w
    return w
    
