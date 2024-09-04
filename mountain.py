#https://school.programmers.co.kr/learn/courses/30/lessons/258705

def solution(n, tops):
    answer = 0
    #a : 두번째 삼각형이 삼각형으로 채워지는 경우
    #b : 두번째 삼각형이 마름모로 채워지는 경우
    a = 2 + tops[0] #윗 줄의 첫번째에 삼각형이 있다면 3가지, 아니면 2가지
    b = 1 #나머지를 전부 삼각형으로 채워야하므로 단 한가지
    answer += a + b
    if(n > 1):
        for i in tops[1:]:
            #n번째 삼각형을 삼각형으로 채우는 경우 = n-1번째 삼각형을 삼각형으로 채웠을 때 * (윗 줄의 첫번째에 삼각형이 있다면 3가지, 아니면 2가지) +  n-1번째 삼각형을 마름모로 채웠을 때(n - 1까지 채우는 방법과 동일)
            a = (2 + i) * a +(1+ i)  * b
            #n번째 삼각형을 마름모로 채웠을 때 = n - 1까지 채우는 방법과 동일
            b = answer
            answer = a + b # 두경우의 수를 더함
    
    return answer % 10007
