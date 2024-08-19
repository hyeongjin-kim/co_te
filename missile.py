#https://school.programmers.co.kr/learn/courses/30/lessons/181188
def solution(targets):
    answer = 0
    
    targets.sort(key = lambda a : a[0])
    interval = []
    
    
    for idx, mi in enumerate(targets):
        if(idx == 0):
            interval.append(mi)
            answer+=1
            
        else:
            a, b = interval[answer-1]
            if(b > mi[0]):
                if(mi[1] < b):
                    interval[answer-1][1] = mi[1]
            else:
                interval.append(mi)
                answer+=1
    
    return answer
