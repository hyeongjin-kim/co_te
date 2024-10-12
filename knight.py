#https://www.codetree.ai/training-field/frequent-problems/problems/royal-knight-duel/submissions?page=2&pageSize=5
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]
L, N, Q = map(int, input().split())

board = [[0] for _ in range(L + 1)]
live = [1 for _ in range(N + 1)]

damage = [0 for _ in range(N + 1)]

for i in range(1, L + 1):
    board[i].extend(list(map(int, input().split())))

def inrange(r, c):
    return 0 < r < L + 1 and 0 < c < L + 1

def move(i, d):
    if (d == 0):
        knight[i][0] -= 1
    elif (d == 1):
        knight[i][1] += 1
    elif (d == 2):
        knight[i][0] += 1
    else:
        knight[i][1] -= 1

def death(i):
    r, c, h, w, k = knight[i]
    for row in range(r, r + h):
        for col in range(c, c + w):
            knightboard[row][col] = 0

def update(i, d):
    r, c, h, w, k = knight[i]
    if(d == 0):
        for col in range(c, c + w):
            knightboard[r][col] = i
            knightboard[r + h][col] = 0
    elif(d == 1):
        for row in range(r, r + h):
            knightboard[row][c + w - 1] = i
            knightboard[row][c - 1] = 0

    elif(d == 2):
        for col in range(c, c + w):
            knightboard[r + h - 1][col] = i
            knightboard[r - 1][col] = 0
    else:
        for row in range(r, r + h):
            knightboard[row][c] = i
            knightboard[row][c + w] = 0

def calc(i):
    r, c, h, w, k = knight[i]
    for row in range(r, r + h):
        for col in range(c, c + w):
            if(board[row][col] == 1):
                k -= 1
                if(k == 0):
                    knight[i][4] = 0
                    live[i] = 0
                    return
    damage[i] += knight[i][4] - k
    knight[i][4] = k
knight = [[0,0,0,0,0]]
knightboard = [[0 for _ in range(L + 1)] for _ in range(L + 1)]


def push(i, d):
    r, c, h, w, k = knight[i]
    candidate = set()

    if(d == 0):
        if(inrange(r - 1, c)):
            for col in range(c, c + w):
                if(board[r - 1][col] == 2):
                    return False, set()
                if(knightboard[r - 1][col] != 0):
                    candidate.add((knightboard[r - 1][col]))
        else:
            return False, set()
    elif(d == 1):
        if (inrange(r, c + w)):
            for row in range(r, r + h):
                if(board[row][c + w] == 2): return False, set()
                if(knightboard[row][c + w] != 0):
                    candidate.add((knightboard[row][c + w]))
        else:
            return False, set()
    elif(d == 2):
        if(inrange(r + h, c)):
            for col in range(c, c + w):
                if(board[r + h ][col] == 2): return False, set()
                if(knightboard[r + h][col] != 0):
                    candidate.add((knightboard[r + h][col]))
        else:
            return False, set()
    else:
        if(inrange(r, c - 1)):
            for row in range(r, r + h):
                if(board[row][c - 1] == 2): return False, set()
                if(knightboard[row][c - 1] != 0):
                    candidate.add((knightboard[row][c - 1]))
        else:
            return False, set()
    result = True
    for candi in candidate:
        check, can = push(candi, d)
        if(not check):
            return False, set()
        result = result and check
        candidate = candidate | can
    return result , candidate

for i in range(1, N + 1):
    r, c, h, w, k = map(int, input().split())
    knight.append([r, c, h, w, k])
    for row in range(r, r + h):
        for col in range(c, c + w):
            knightboard[row][col] = i

cmd = []
for _ in range(Q):
    cmd.append(list(map(int, input().split())))

for q in range(Q):
    i, d = cmd[q]
    if(live[i]):
        result, candidate = push(i, d)
        if (result):
            candidate = list(candidate)
            candidate.sort(key = lambda x: knight[x][0] * - 1 * dr[d] + knight[x][1] * -1 * dc[d])
            for candi in candidate:
                move(candi, d)
                calc(candi)
                if (live[candi]):
                    update(candi, d)
                else:
                    move(candi, (d + 2)%4)
                    death(candi)
            move(i, d)
            update(i, d)

total = 0

for i in range(1, N + 1):
    if live[i]:
        total += damage[i]
print(total)
