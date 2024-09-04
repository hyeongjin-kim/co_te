#https://school.programmers.co.kr/learn/courses/30/lessons/258709
from itertools import combinations
from collections import defaultdict

def solution(dice):
    answer = []
    max_win = 0
    com = list(combinations([i for i in range(len(dice))], len(dice)//2)) #주사위를 가잘 수 있는 모든 경우의 수 생성
    case = [[com[i], com[-1-i]] for i in range(len(com)//2)] #주사위를 뽑았을 때 나와 상대가 보유한 주사위끼리 묶어 매치의 경우의 수 생성
    
    for a, b in case:
        case_a = defaultdict(int) #내가 낼 수 있는 경우의 수 
        case_b = defaultdict(int) #상대가 낼 수 있는 경우의 수
        
        for dice_num in a:
            c_a = defaultdict(int) #임시 경우의 수 딕셔너리
            if(not case_a): #맨 처음 주사위를 던질 때
                for num in dice[dice_num]:
                    case_a[num] += 1 #던진 주사위 눈금을 낼 수 있는 경우의 수가 1 증가
            else:
                for before_case in case_a.keys(): #두번째부터
                    for num in dice[dice_num]:
                        c_a[before_case + num] += case_a[before_case] #임시 경우의 수 딕셔너리에 지금까지 주사위를 던져 나온 경우의 수에 지금 던진 주사위를 더해 이 숫자를 만들 수 있는 경우의 수가 1 증가
                case_a = c_a #경우의 수 딕셔너리 업데이드
        for dice_num in b:
            c_b = defaultdict(int) #임시 경우의 수 딕셔너리
            if(not case_b): #맨 처음 주사위를 던질 때
                for num in dice[dice_num]: 
                    case_b[num] += 1 #던진 주사위 눈금을 낼 수 있는 경우의 수가 1 증가
            else:
                for before_case in case_b.keys():
                    for num in dice[dice_num]:
                        c_b[before_case + num] += case_b[before_case] #임시 경우의 수 딕셔너리에 지금까지 주사위를 던져 나온 경우의 수에 지금 던진 주사위를 더해 이 숫자를 만들 수 있는 경우의 수가 1 증가
                case_b = c_b #경우의 수 딕셔너리 업데이드
                
        win, draw, lose = 0, 0, 0 #승, 무, 패 세기
        for aa in case_a.keys():
            for bb in case_b.keys():
                #각각의 경우의 수 매치
                if(aa > bb):
                    win += case_a[aa]*case_b[bb] #내가 이기는 경우
                elif(aa == bb):
                    draw += case_a[aa]*case_b[bb] #비기는 경우
                else:
                    lose += case_a[aa]*case_b[bb] #내가 지는 경우
        if(max_win < win):
            max_win = win #승이 maxwin보다 많은 경우 최대 승리수 업데이트
            answer = [i + 1 for i in a] #답을 내 주사위들로 채움
        if(max_win < lose):
            max_win = lose #패가 maxwin보다 많은 경우 -> 나와 상대의 주사위가 바뀐다면 내가 이기는경우의 수가 많아짐 -> 최대 승리수 업데이트
            answer = [i + 1 for i in b] #답을 상대 주사위들로 채움
            
    return answer 
