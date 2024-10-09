#https://www.codetree.ai/training-field/frequent-problems/problems/ancient-ruin-exploration/description?page=1&pageSize=5
import copy
from collections import deque

K, M = list(map(int, (input().split())))
dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]

global p
p = []
for i in range(5):
    p.append(list(map(int, input().split())))
extra = list(map(int, input().split()))
global newp

newp = []
answer = []
global refill
refill = 0
pivot = [[0, 0], [1, 0], [2, 0], [0, 1], [1, 1], [2, 1], [0, 2], [1, 2], [2, 2]]


def spin90(sy, sx):
    global newp
    global p
    for y in range(sy, sy + 3):
        for x in range(sx, sx + 3):
            oy, ox = y - sy, x - sx
            ry, rx = ox, 3 - oy - 1
            newp[sy + ry][sx + rx] = p[y][x]
    return


def spin180(sy, sx):
    global newp
    global p
    for y in range(sy, sy + 3):
        for x in range(sx, sx + 3):
            oy, ox = y - sy, x - sx
            ry, rx = 3 - oy - 1, 3 - ox - 1
            newp[sy + ry][sx + rx] = p[y][x]
    return


def spin270(sy, sx):
    global newp
    global p
    for y in range(sy, sy + 3):
        for x in range(sx, sx + 3):
            oy, ox = y - sy, x - sx
            ry, rx = 3 - ox - 1, oy
            newp[sy + ry][sx + rx] = p[y][x]
    return


def bfs():
    isvisit = [[0 for _ in range(5)] for _ in range(5)]
    q = deque()
    score = 0
    tar = []
    for aa in range(5):
        for bb in range(5):
            if isvisit[aa][bb] == 0:
                cur = []
                q.append((aa, bb))
                isvisit[aa][bb] = 1
                while (len(q)):
                    cr, cc = q.popleft()
                    cur.append([cr, cc])
                    for k in range(4):
                        ny = cr + dy[k]
                        nx = cc + dx[k]
                        if 0 <= ny < 5 and 0 <= nx < 5 and isvisit[ny][nx] == 0 and newp[aa][bb] == newp[ny][nx]:
                            q.append((ny, nx))
                            isvisit[ny][nx] = 1
                if len(cur) > 2:
                    tar.extend(cur)
                    score += len(cur)
    return tar, score


def cleanrefill(target):
    global refill
    for r, c in target:
        newp[r][c] = 0

    for j in range(5):
        for i in [4, 3, 2, 1, 0]:
            if (newp[i][j] == 0):
                newp[i][j] = extra[refill]
                refill += 1


for _ in range(K):
    score = 0
    result = []
    for i in range(9):
        r, c = pivot[i]
        newp = copy.deepcopy(p)
        spin90(r, c)
        tar90, score90 = bfs()
        result.append([score90, 0, [r, c], tar90])
        newp = copy.deepcopy(p)
        spin180(r, c)
        tar180, score180 = bfs()
        result.append([score180, 1, [r, c], tar180])
        newp = copy.deepcopy(p)
        spin270(r, c)
        tar270, score270 = bfs()
        result.append([score270, 2, [r, c], tar270])

    result.sort(key=lambda x: (-x[0], x[1], x[2][1], x[2][0]))

    choice = result[0]

    if (choice[0] != 0):
        score += choice[0]
        newp = copy.deepcopy(p)
        if (choice[1] == 0):
            spin90(choice[2][0], choice[2][1])
        elif (choice[1] == 1):
            spin180(choice[2][0], choice[2][1])
        else:
            spin270(choice[2][0], choice[2][1])

        cleanrefill(choice[3])
        while (True):
            tar, val = bfs()
            if (val == 0):
                break
            score += val
            cleanrefill(tar)

        p = newp
        answer.append(score)
    else:
        break
print(*answer)
