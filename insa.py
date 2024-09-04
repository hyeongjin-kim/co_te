#https://school.programmers.co.kr/learn/courses/30/lessons/152995

def solution(scores):
    answer = 1
    tar_a = scores[0][0] #완호의 근무태도 점수
    tar_b = scores[0][1] #완호의 동료평가
    tar_score = tar_a + tar_b #완호의 총점
    scores.sort(key = lambda x : (-x[0], x[1])) #근무태도에 대해서 내림차순, 동료평가에 대해서 오름차순으로 정렬
    max_b = 0 #최대 동료평가 점수

    
    for a, b in scores:
        if(tar_a < a and tar_b < b): #어떤 직원보다 두가지 점수가 모두 낮아 인센티브 x
            return -1
        if( b >= max_b): #근무태도 점수는 앞에 높은 사람이 있음 -> 앞에서 나온 최대 동료평가(직원 X)보다 이 사람(직원 Y)의 동료평가보다 낮다 -> 직원 X의 두 점수는 직원 Y보다 높다 직원 Y는 인센티브 X
            max_b = b
            if(a + b > tar_score): #이사람보다 완호의 총점이 낮으므로 등수 + 1
                answer+=1
    return answer
