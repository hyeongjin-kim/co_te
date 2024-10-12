#https://www.codetree.ai/training-field/frequent-problems/problems/rudolph-rebellion/submissions?page=2&pageSize=5
N, M, P, C, D = map(int, input().split())
rr, rc = map(int, input().split())

board = [[0 for _ in range(N + 1)] for _ in range(N + 1)]

board[rr][rc] = -1

spos = [[0, 0, 0]]
stun = [0 for _ in range(P + 1)]
out = [0 for _ in range(P + 1)]
score = [0 for _ in range(P + 1)]
power = [C, D]

def inrange(num):
    return 0 < num < N + 1

def direction(tar):
    sr, sc = tar[1:]
    rflag = (abs(sr - rr) > 0) * (-1 if(sr - rr < 0) else 1)
    cflag = (abs(sc - rc) > 0) * (-1 if(sc - rc < 0) else 1)

    return rflag, cflag

def collision(flag, i, dr, dc):
    rmove = power[flag] * dr
    cmove = power[flag] * dc
    spos[i][1] += rmove
    spos[i][2] += cmove
    interection(i, spos[i][1], spos[i][2], dr, dc)

def interection(i, r, c, dr, dc):
    if(inrange(r) and inrange(c)):
        target = board[r][c]
        board[r][c] = i
        spos[i][1] = r
        spos[i][2] = c
        if(target != 0):
            interection(target, r + dr, c + dc, dr, dc)
    else:
        out[i] = 1

def dist(sr, sc):
    return (sr - rr)**2 + (sc - rc)**2

for _ in range(P):
    pos = list(map(int, input().split()))
    spos.append(pos)
    board[pos[1]][pos[2]] = pos[0]

spos[1:] = sorted(spos[1:], key = lambda x: x[0])

for _ in range(M):
    snow = []
    for i in range(1, P + 1):
        if(out[i] == 0):
            stun[i] = max(0, stun[i] - 1)
            d = dist(spos[i][1], spos[i][2])
            snow.append([d, spos[i][1], spos[i][2]])
    snow.sort(key = lambda x: (x[0], -x[1], -x[2]))
    target = snow[0]
    dr, dc = direction(target)
    board[rr][rc] = 0
    rr += dr
    rc += dc

    if(board[rr][rc] > 0):
        tar = board[rr][rc]
        collision(0, tar, dr, dc)
        score[tar] += C
        stun[tar] = 2
    board[rr][rc] = -1

    for i in range(1, P + 1):
        if(out[i] == 0 and stun[i] == 0):
            _, sr, sc = spos[i]
            board[sr][sc] = 0
            candidate = [[dist(sr, sc), -1, 0, 0]]
            if (inrange(sr - 1) and inrange(sc) and board[sr - 1][sc] < 1):
                candidate.append([dist(sr - 1, sc), 0, -1, 0])
            if (inrange(sr) and inrange(sc + 1) and board[sr][sc + 1] < 1):
                candidate.append([dist(sr, sc + 1), 1, 0, 1])
            if (inrange(sr + 1) and inrange(sc) and board[sr + 1][sc] < 1):
                candidate.append([dist(sr + 1, sc), 2, 1, 0])
            if (inrange(sr) and inrange(sc - 1) and board[sr][sc - 1] < 1):
                candidate.append([dist(sr, sc - 1), 3, 0, -1])
            candidate.sort(key = lambda x: (x[0], x[1]))
            if(candidate[0][1] != -1):
                sr += candidate[0][2]
                sc += candidate[0][3]
                spos[i][1] = sr
                spos[i][2] = sc
                if (rc == sc and rr == sr):
                    # 충돌
                    collision(1, i, -candidate[0][2], -candidate[0][3])
                    score[i] += D
                    stun[i] = 2
                else:
                    board[sr][sc] = i
            else:
                board[sr][sc] = i
    if sum(out) == P:
         break
    for i in range(1, P + 1):
        if (out[i] == 0):
            score[i] += 1
print(*score[1:])
