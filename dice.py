from itertools import combinations
from collections import defaultdict

def solution(dice):
    answer = []
    max_win = 0
    com = list(combinations([i for i in range(len(dice))], len(dice)//2))
    case = [[com[i], com[-1-i]] for i in range(len(com)//2)]
    
    for a, b in case:
        case_a = defaultdict(int)
        case_b = defaultdict(int)
        
        for dice_num in a:
            c_a = defaultdict(int)
            if(not case_a):
                for num in dice[dice_num]:
                    case_a[num] += 1
            else:
                for before_case in case_a.keys():
                    for num in dice[dice_num]:
                        c_a[before_case + num] += case_a[before_case]
                case_a = c_a
        for dice_num in b:
            c_b = defaultdict(int)
            if(not case_b):
                for num in dice[dice_num]:
                    case_b[num] += 1
            else:
                for before_case in case_b.keys():
                    for num in dice[dice_num]:
                        c_b[before_case + num] += case_b[before_case]
                case_b = c_b
                
        win, draw, lose = 0, 0, 0
        for aa in case_a.keys():
            for bb in case_b.keys():
                if(aa > bb):
                    win += case_a[aa]*case_b[bb]
                elif(aa == bb):
                    draw += case_a[aa]*case_b[bb]
                else:
                    lose += case_a[aa]*case_b[bb]
        if(max_win < win):
            max_win = win
            answer = [i + 1 for i in a]
        if(max_win < lose):
            max_win = lose
            answer = [i + 1 for i in b]
            
    return answer 