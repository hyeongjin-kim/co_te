#https://school.programmers.co.kr/learn/courses/30/lessons/150366#

def solution(commands):
    arr = [[None for _ in range(50)] for _ in range(50)] //전체 표
    answer = []
    m = [] //merge된 칸들을 저장하는 리스트
    for a in range(len(commands)):
        com = commands[a].split() //커멘드 분해
        if(com[0] == "UPDATE"): //업데이트인 경우
            if(len(com) == 3): //특정 값을 가진 곳을 모든 다른 값으로 변경
                up1(arr, com[1], com[2])
            else: //특정 위치의 값을 다른 값으로 변경(merge된 경우 그 곳들도 모두 변경
                up2(arr, int(com[1])-1 , int(com[2])-1, com[3], m)
        elif(com[0] == "MERGE"): //특정 두 셀을 merge함
            merge(arr, int(com[1])-1, int(com[2])-1, int(com[3])-1, int(com[4])-1, m)
        
        elif(com[0] == "UNMERGE"): //특정 칸을 unmerge함
            unmerge(arr, int(com[1])-1, int(com[2])-1,m)
        
        elif(com[0] == "PRINT"): //특정 칸의 값을 출력
            if(arr[int(com[1])-1][int(com[2])-1] is not None):
                answer.append(arr[int(com[1])-1][int(com[2])-1])
            else:
                answer.append("EMPTY")
        
    return answer

def up1(arr, v1, v2): //특정 값을 가진 모든 칸의 값을 변경
    for i in range(50):
        for j in range(50):
            if(arr[i][j] == v1):
                arr[i][j] = v2

def up2(arr, r, c, v, m): //특정 칸의 값을 변경, merge되어 merge list에 있는 경우, 해당 리스트의 값들도 모두 변경
    arr[r][c] = v
    for i in range(len(m)):
        if((r,c) in m[i]):
            for a, b in m[i]:
                arr[a][b] = v
            break
                
def merge(arr, r1, c1, r2, c2, m): //특정 두 셀을 merge함 각 셀이 이미 merge되어있는 경우, 한꺼번에 merge함
    if(r1 == r2 and c1 == c2):
        return
    check1 = False //r1, c1이 이미 merge되어있는지 여부
    check2 = False //r2, c2가 이미 merge되어있는지 여부
    i1 = -1 //r1, c1이 이미 merge되어있을 때 그 정보가 저장된 인덱스
    i2 = -1 //r2, c2가 이미 merge되어있을 때 그 정보가 저장된 인덱스
    if(m): //mergelist가 있는 경우
        for k in range(len(m)):
            if((r1,c1) in m[k]): //r1, c1이 이미 merge되어있는 경우, 인덱스 저장, 플레그 활성
                i1 = k
                check1 = True
                break
        for k in range(len(m)): //r2, c2가 이미 merge되어있는 경우, 인덱스 저장, 플레그 활성
            if((r2,c2) in m[k]):
                i2 = k
                check2 = True
                break
    if(check1 and check2): //둘 다 merge 되어있는 경우
        if(i1 == i2): return //이미 둘이 merge되어있는 경우는 처리 x
        if(arr[r1][c1] is not None): //r1, c1에 정보가 있으면 나머지를 그걸로 채움
            for a,b in m[i2]:
                arr[a][b] = arr[r1][c1]
        else: //r1, c1에 정보가 없다면 r2, c2에 있는것으로 나머지를 채움(정보일 수도, NONE 일수도)
            for a,b in m[i1]: 
                arr[a][b] = arr[r2][c2]
        m[i1] = m[i1] + m[i2] //두 리스트 연결
        m.remove(m[i2]) //한쪽 제거
        
    elif(check1 and not check2): //r1, c1이 이미 merge되어있는 경우,
        if(arr[r1][c1] is not None): //r1, c1에 정보가 있으면 나머지를 그걸로 채움
            arr[r2][c2] = arr[r1][c1]
        else: //r1, c1에 정보가 없다면 r2, c2에 있는것으로 나머지를 채움(정보일 수도, NONE 일수도)
            for a,b in m[i1]:
                arr[a][b] = arr[r2][c2]
        m[i1].append((r2,c2)) //리스트에 r2, c2 추가
    
    elif(not check1 and check2): //r2, c2가 이미 merge되어있는 경우,
        if(arr[r1][c1] is not None): //r1, c1에 정보가 있으면 나머지를 그걸로 채움
            for a,b in m[i2]:
                arr[a][b] = arr[r1][c1]
        else: //r1, c1에 정보가 없다면 r2, c2에 있는것으로 나머지를 채움(정보일 수도, NONE 일수도)
            arr[r1][c1] = arr[r2][c2]
        m[i2].append((r1,c1)) //리스트에 r1, c1 추가

    else: //둘 다 merge되어있지 않은 경우
        m.append([(r1, c1), (r2, c2)]) //mergelist에 추가
        if(arr[r1][c1] is not None): //r1, c1에 정보가 있으면 r2, c2를 그걸로 채움
            arr[r2][c2] = arr[r1][c1]
        else: //r1, c1에 정보가 없다면 r2, c2에 있는것으로 r1, c1을 채움(정보일 수도, NONE 일수도)
            arr[r1][c1] = arr[r2][c2]
        
def unmerge(arr, r, c, m): //merge 된 셀 해제
    if(m):
        for i in range(len(m)):
            if((r,c) in m[i]): //해당 칸이 merge되어있다면
                value = arr[r][c] //그 칸의 값 저장
                for a, b in m[i]: //같이 merge되어있던 모든 칸 초기화
                    arr[a][b] = None
                arr[r][c] = value //해당 칸만 값 복원
                m.remove(m[i]) //리스트에서 제거
                break
