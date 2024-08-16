#https://school.programmers.co.kr/learn/courses/30/lessons/150366#

def solution(commands):
    arr = [[None for _ in range(50)] for _ in range(50)]
    answer = []
    m = []
    for a in range(len(commands)):
        com = commands[a].split()
        if(com[0] == "UPDATE"):
            if(len(com) == 3):
                up1(arr, com[1], com[2])
            else:
                up2(arr, int(com[1])-1 , int(com[2])-1, com[3], m)
        elif(com[0] == "MERGE"):
            merge(arr, int(com[1])-1, int(com[2])-1, int(com[3])-1, int(com[4])-1, m)
        
        elif(com[0] == "UNMERGE"):
            unmerge(arr, int(com[1])-1, int(com[2])-1,m)
        
        elif(com[0] == "PRINT"):
            if(arr[int(com[1])-1][int(com[2])-1] is not None):
                answer.append(arr[int(com[1])-1][int(com[2])-1])
            else:
                answer.append("EMPTY")
        
    return answer

def up1(arr, v1, v2):
    for i in range(50):
        for j in range(50):
            if(arr[i][j] == v1):
                arr[i][j] = v2

def up2(arr, r, c, v, m):    
    arr[r][c] = v
    for i in range(len(m)):
        if((r,c) in m[i]):
            for a, b in m[i]:
                arr[a][b] = v
            break
                
def merge(arr, r1, c1, r2, c2, m):
    if(r1 == r2 and c1 == c2):
        return
    check1 = False
    check2 = False
    i1 = -1
    i2 = -1
    if(m):
        for k in range(len(m)):
            if((r1,c1) in m[k]):
                i1 = k
                check1 = True
                break
        for k in range(len(m)):
            if((r2,c2) in m[k]):
                i2 = k
                check2 = True
                break
    if(check1 and check2):
        if(i1 == i2): return
        if(arr[r1][c1] is not None):
            for a,b in m[i2]:
                arr[a][b] = arr[r1][c1]
        else:
            for a,b in m[i1]:
                arr[a][b] = arr[r2][c2]
        m[i1] = m[i1] + m[i2]
        m.remove(m[i2])
        
    elif(check1 and not check2):
        if(arr[r1][c1] is not None):
            arr[r2][c2] = arr[r1][c1]
        else:
            for a,b in m[i1]:
                arr[a][b] = arr[r2][c2]
        m[i1].append((r2,c2))
    
    elif(not check1 and check2):
        if(arr[r1][c1] is not None):
            for a,b in m[i2]:
                arr[a][b] = arr[r1][c1]
        else:
            arr[r1][c1] = arr[r2][c2]
        m[i2].append((r1,c1))
    else:
        m.append([(r1, c1), (r2, c2)])
        if(arr[r1][c1] is not None):
            arr[r2][c2] = arr[r1][c1]
        else:
            arr[r1][c1] = arr[r2][c2]
        
def unmerge(arr, r, c, m):
    if(m):
        for i in range(len(m)):
            if((r,c) in m[i]):
                value = arr[r][c]
                for a, b in m[i]:
                    arr[a][b] = None
                arr[r][c] = value
                m.remove(m[i])
                break
