#https://school.programmers.co.kr/learn/courses/30/lessons/258705

def solution(n, tops):
    answer = 0
    a = 2 + tops[0]
    b = 1
    answer += a + b
    if(n > 1):
        for i in tops[1:]:
            a = (2 + i) * a +(1+ i)  * b
            b = answer
            answer = a + b 
    
    return answer % 10007
