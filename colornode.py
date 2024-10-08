#https://www.codetree.ai/training-field/frequent-problems/problems/color-tree/submissions?page=1&pageSize=5
MAX_ID = 100005
MAX_DEPTH = 105
COLOR_MAX = 5
class Node:
    def __init__(self):
        self.mid = 0
        self.pid = 0
        self.color = 0
        self.maxdepth = 0
        self.child = []
        self.lastUpdate = 0

class ColorCount:
    def __init__(self):
        self.cnt = [0] * (COLOR_MAX + 1)

    def __add__(self, obj):
        res = ColorCount()
        for i in range(1, COLOR_MAX + 1):
            res.cnt[i] = self.cnt[i] + obj.cnt[i]
        return res

    def score(self):
        result = 0
        for i in range(1, COLOR_MAX + 1):
            result += 1 if self.cnt[i] else 0
        return result * result

count = int(input())

nodes = [Node() for _ in range(MAX_ID)]
isRoot = [False] * MAX_ID

def canMakeChild(curr, needDepth):
    if(curr.mid == 0):
        return True
    if(curr.maxdepth <= needDepth):
        return False
    return canMakeChild(nodes[curr.pid], needDepth + 1)

def get_color(node):
    if node.mid == 0:
        return 0, 0
    info = get_color(nodes[node.pid])
    if(info[1] > node.lastUpdate):
        return info
    else:
        return node.color, node.lastUpdate

def getvalue(curr, color, lastUpdate):
    # root에서부터 내려온 색 정보보다 현재 노드의 색정보가 최신이라면 갱신합니다
    if lastUpdate < curr.lastUpdate:
        lastUpdate = curr.lastUpdate
        color = curr.color
    result = [0, ColorCount()]
    result[1].cnt[color] = 1
    for childId in curr.child:
        child = nodes[childId]
        # 각 자식이 이루는 SubTree에서의 점수와 color count 값을 가져옵니다
        subResult = getvalue(child, color, lastUpdate)
        result[1] = result[1] + subResult[1]
        result[0] += subResult[0]
    result[0] += result[1].score()
    return result

for i in range(1, count + 1):
    cmd = list(map(int, input().split()))
    a = cmd[0]
    if(a == 100):
        mid = cmd[1]
        pid = cmd[2]
        color = cmd[3]
        maxdepth = cmd[4]

        if(pid == -1):
            isRoot[mid] = True

        if(isRoot[mid] or canMakeChild(nodes[pid], 1)):
            nodes[mid].mid = mid
            nodes[mid].pid = 0 if isRoot[mid] else pid
            nodes[mid].color = color
            nodes[mid].maxdepth = maxdepth
            nodes[mid].lastUpdate = i

            if(not isRoot[mid]):
                nodes[pid].child.append(mid)

    elif(a == 200):
        mid = cmd[1]
        color = cmd[2]
        nodes[mid].color = color
        nodes[mid].lastUpdate = i


    elif(a == 300):
        mid = cmd[1]
        color = get_color(nodes[mid])[0]
        print(color)


    elif(a == 400):
        value = 0
        for i in range(1, MAX_ID):
            if(isRoot[i]):
                value += getvalue(nodes[i], nodes[i].color, nodes[i].lastUpdate)[0]
        print(value)
