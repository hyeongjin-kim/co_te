#https://school.programmers.co.kr/learn/courses/30/lessons/181188
def solution(targets):
    answer = 0
    #모든 미사일을 관통하도록 발사해야함 -> 왼쪽부터 오른쪽까지 쭉 훑으면서 겹쳐서 맞출 수 있다면 맞추고 아니라면 새 로켓을 쏴야함
    
    targets.sort(key = lambda a : a[0]) #시작 위치 순으로 정렬
    interval = [] #겹치는 구간들(로켓을 발사할 곳)을 저장할 리스트
    
    
    for idx, mi in enumerate(targets):
        if(idx == 0): #맨 처음은 일단 리스트에 넣음
            interval.append(mi)
            answer+=1
            
        else:
            a, b = interval[answer-1] #지금까지 결정된 로켓중 가장 오른쪽에 쏠 로켓을 쏠 수 있는 구간
            if(b > mi[0]): #만약 이 구간과 현재 보고있는 미사일이 겹친다면, 겹치는 구간을 업데이트함(마지막에 결정된 로켓으로 이것까지 맞출 수 있음
                if(mi[1] < b):
                    interval[answer-1][1] = mi[1]
            else: #겹치지 않는다면 새 로켓을 쏴야함 이 미사일이 있는 곳을 다음 로켓을 쏠 수 있는 구간으로 지정
                interval.append(mi)
                answer+=1
    
    return answer
