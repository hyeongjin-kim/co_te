#https://school.programmers.co.kr/learn/courses/30/lessons/133500
import sys
sys.setrecursionlimit(10**6) #최대 재귀 횟수 증가
ad = [] #인접리스트
answer = 0
b = [] #방문여부 확인 리스트
###인접한 두 노드중 어느 한쪽이든 한군데는 등대가 있어야 함
def solution(n, lighthouse):
    global ad 
    global b
    ad = [[] for _ in range(n+1)]
    for x, y in lighthouse: #인접리스트 생성
        ad[x].append(y)
        ad[y].append(x)
    b = [False for _ in range(n+1)]
    
    dfs(1, 1) 
    
    return answer
#항상 말단에는 등대를 추가하지 않음 --> 말단에 추가하면 등대가 있는 혜택을 말단 노드와 이 노드와 연결된 노드 단 두개밖에 못받음
#말단이 아니면 이 노드와 연결된 다른 노드들이 이 등대에 영향을 받음

def dfs(node, parent):
    global b
    global answer
    global ad
    for child in ad[node]:
        if(child == parent): #이미 왔던 곳으로 돌아가는 경우는 제외
            continue
        dfs(child, node) #자식 노드를 먼저 탐색함
        if(not b[node] and not b[child]): #자식노드와 자기 자신에 모두 등대가 없음 -> 현재 노드에 등대 추가 -> 말단에 추가하지 않기 위함
            answer+=1
            b[node] = True

    
