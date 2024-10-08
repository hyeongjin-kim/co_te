#https://www.codetree.ai/training-field/frequent-problems/problems/magical-forest-exploration/description?page=1&pageSize=5
from queue import PriorityQueue
R, C, K = map(int, input().split())

table = [[0 for _ in range(C + 1)] for _ in range(R + 4) ]
isexit = [[0 for _ in range(C + 1)] for _ in range(R + 4) ]
gol = {}
dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

def bfs(i):
    if(len(gol) == 1):
        return R
    isvisit = [[0 for _ in range(C + 1)] for _ in range(R + 4) ]
    r, c, e = gol[i]
    queue = PriorityQueue()
    queue.put([-r, r, c])
    maxr = 0
    while(queue.qsize()):
        key, r, c = queue.get()
        maxr = max(r, maxr)
        if(maxr == R + 4): return R
        isvisit[r][c] = 1
        if(r + 1 < R + 4 and table[r + 1][c] != 0 and isvisit[r + 1][c] == 0 and ((table[r][c] == table[r + 1][c]) or ((table[r][c] != table[r + 1][c]) and isexit[r][c] == 1))):
            if(r + 1 == R + 4): return R;
            queue.put([-r - 1, r + 1, c])
        if(c - 1 > 1 and table[r][c - 1] != 0 and isvisit[r][c - 1] == 0 and ((table[r][c] == table[r][c - 1]) or ((table[r][c] != table[r][c - 1]) and isexit[r][c] == 1))):
            queue.put([-r, r, c - 1])
        if(c + 1 < C + 1 and table[r][c + 1] != 0 and isvisit[r][c + 1] == 0 and ((table[r][c] == table[r][c + 1]) or ((table[r][c] != table[r][c + 1]) and isexit[r][c] == 1))):
            queue.put([-r, r, c + 1])
        if(r - 1 >= 4 and table[r - 1][c] != 0 and isvisit[r - 1][c] == 0 and ((table[r][c] == table[r - 1][c]) or ((table[r][c] != table[r - 1][c]) and isexit[r][c] == 1))):
            queue.put([-r + 1, r - 1, c])
    return maxr - 3



def candown(i):
    q, w, e = gol[i]
    if(table[q + 1][w - 1] != 0):
        return False
    if(q + 2 >= R + 4 or table[q + 2][w] != 0):
        return False
    if(table[q + 1][w + 1] != 0):
        return False
    return True

def canleft(i):
    q, w, e = gol[i]
    if(q - 1 < 0 or table[q - 1][w - 1] != 0):
        return False
    if(w - 2 < 1 or table[q][w - 2] != 0):
        return False
    if( w - 1 < 1 or table[q + 1][w - 1] != 0):
        return False
    if( w - 2 < 1 or table[q + 1][w - 2] != 0):
        return False
    if(q + 2 >= R + 4 or table[q + 2][w - 1] != 0):
        return False
    return True

def canright(i):
    q, w, e = gol[i]
    if(table[q - 1][w + 1] != 0):
        return False
    if(w + 2 >= C + 1 or table[q][w + 2] != 0):
        return False
    if(table[q + 1][w + 1] != 0):
        return False
    if(w + 2 >= C + 1 or table[q + 1][w + 2] != 0):
        return False
    if(q + 2 >= R + 4 or table[q + 2][w + 1] != 0):
        return False
    return True

def move(i):
    q, w, e = gol[i]
    if(candown(i)):
        gol[i] = [q + 1, w, e]
        return True

    elif(canleft(i)):
        gol[i] = [q + 1, w - 1, (e + 3)%4 ]
        return True

    elif(canright(i)):
        gol[i] = [q + 1, w + 1, (e + 1)%4]
        return True
    return False

answer = 0

for i in range(1, K + 1):
    a, b = map(int, input().split())
    gol[i] = [2, a, b]

    while(move(i)):
        continue
    q, w, e = gol[i]
    if(q <= 4):
        table = [[0 for _ in range(C + 1)] for _ in range(R + 4) ]
        isexit = [[0 for _ in range(C + 1)] for _ in range(R + 4) ]
        gol = {}
    else:
        table[q][w] = i
        table[q + 1][w] = i
        table[q - 1][w] = i
        table[q][w + 1] = i
        table[q][w - 1] = i
        isexit[q + dy[e]][ w + dx[e]] = 1
        answer += bfs(i)
print(answer)
