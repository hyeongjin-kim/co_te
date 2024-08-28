#https://school.programmers.co.kr/learn/courses/30/lessons/152995

def solution(scores):
    answer = 1
    tar_a = scores[0][0]
    tar_b = scores[0][1]
    tar_score = tar_a + tar_b
    scores.sort(key = lambda x : (-x[0], x[1]))
    max_b = 0
    
    for a, b in scores:
        if(tar_a < a and tar_b < b):
            return -1
        if( b >= max_b):
            max_b = b
            if(a + b > tar_score):
                answer+=1
    return answer
