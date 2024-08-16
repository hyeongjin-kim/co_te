def solution(sequence):
    answer = 0
    a = [sequence[i] * (-1)**i for i in range (len(sequence))]
    b = [sequence[i] * (-1)**(i+1) for i in range (len(sequence))]
    answer = max(kadane(a), kadane(b))
    return answer

def kadane(sequence):
    lsum = sequence[0]
    gsum = sequence[0]
    
    for i in range(1, len(sequence)):
        lsum += sequence[i]
        lsum = max(lsum, sequence[i])
        gsum = max(lsum, gsum)
    return gsum
