#https://school.programmers.co.kr/learn/courses/30/lessons/133500
import sys
sys.setrecursionlimit(10**6)
ad = []
answer = 0
b = []

def solution(n, lighthouse):
    global ad
    global b
    ad = [[] for _ in range(n+1)]
    for x, y in lighthouse:
        ad[x].append(y)
        ad[y].append(x)
    b = [False for _ in range(n+1)]
    
    dfs(1, 1)
    
    return answer

def dfs(node, parent):
    global b
    global answer
    global ad
    for child in ad[node]:
        if(child == parent):
            continue
        dfs(child, node)
        if(not b[node] and not b[child]):
            answer+=1
            b[node] = True

    
