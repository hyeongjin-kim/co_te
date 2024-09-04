#어떤 수열의 연속 부분 수열에 같은 길이의 펄스 수열을 각 원소끼리 곱하여 연속 펄스 부분 수열을 만들려 합니다.
#펄스 수열이란 [1, -1, 1, -1 …] 또는 [-1, 1, -1, 1 …] 과 같이 1 또는 -1로 시작하면서 1과 -1이 번갈아 나오는 수열입니다.
#예를 들어 수열 [2, 3, -6, 1, 3, -1, 2, 4]의 연속 부분 수열 [3, -6, 1]에 펄스 수열 [1, -1, 1]을 곱하면 연속 펄스 부분수열은 [3, 6, 1]이 됩니다.
#또 다른 예시로 연속 부분 수열 [3, -1, 2, 4]에 펄스 수열 [-1, 1, -1, 1]을 곱하면 연속 펄스 부분수열은 [-3, -1, -2, 4]이 됩니다.
#정수 수열 sequence가 매개변수로 주어질 때, 연속 펄스 부분 수열의 합 중 가장 큰 것을 return 하도록 solution 함수를 완성해주세요.

def solution(sequence):
    answer = 0
    #결국 이 문제는 홀수번째에 -를 곱한 수열과 짝수번째의 -를 곱한 수열의 최대 부분합을 구해 둘 중 큰 것을 고르는 문제임
    a = [sequence[i] * (-1)**i for i in range (len(sequence))]
    b = [sequence[i] * (-1)**(i+1) for i in range (len(sequence))]
    answer = max(kadane(a), kadane(b))
    return answer
#카단 알고리즘 -> 어떤 배열의 최대 부분합을 구하는 알고리즘 O(N)
#lsum : 지금까지의 부분 합
#gsum : 최대 부분합
def kadane(sequence):
    lsum = sequence[0]
    gsum = sequence[0]
    
    for i in range(1, len(sequence)):
        lsum += sequence[i] #부분합 추가
        lsum = max(lsum, sequence[i]) #지금까지의 부분합보다 현재 숫자가 더크면 -> 여기서부터 시작하는게 더 큼
        gsum = max(lsum, gsum) #최대 부분합 업데이트
    return gsum
