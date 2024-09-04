//https://school.programmers.co.kr/learn/courses/30/lessons/150365#
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int minstep = abs(x-r) + abs(y-c);
    //k에서 최단거리를 뺀만큼 소모해야함 -> 그만큼 어디론가 갔다가 되돌아와야함 -> 2의 배수만큼 필요
    //즉 k와 최단거리의 차가 홀수면 불가능 또는, k가 최단거리보다 작으면 불가능
    if(abs(minstep - k) %2 != 0 or minstep > k ) return "impossible";
    //알파벳이 d, l, r, u 순이므로 최대한 좌하단으로 갔다가, 되돌아갈 거리를 제외하고 남은 만큼 좌우좌우를 반복하고, 돌아가는게 사전순서상 가장 빠름
    if(k >= 2 * n -r + c - x + y - 2){ //좌측 최하단으로 갈 수 있는 경우 -> (n, 1)로 갈 수 있는 경우
        answer.append(n - x, 'd'); //쭉 내려갔다가
        answer.append(y - 1, 'l'); //쭉 왼쪽으로
        for(int i = 0; i< (k - (n - r) - (c - 1) - (n-x) - (y-1)); i++){  //되돌아갈 거리를 제외하고 좌우좌우 반복 이때 반드시 (n.1)에서 끝남 왜냐하면 그렇지 않은 경우는 k-최단거리가 홀수이기 때문
            if(i%2 == 0) answer += "r";
            else answer += "l";
        }
        answer.append(c - 1, 'r'); //도착지점 밑까지 쭉 오른쪽으로
        answer.append(n - r, 'u'); //도착지점까지 쭉 위로
    } 
    else if(k >= 2 * n - x - r){ //쭉 내려갈 수는 있으나, (n, 1)은 갈 수 없는 경우
        answer.append(n - x, 'd'); //쭉 내려감
        int remain = k - (2 * n - x - r); 
        int a = (remain - (c - y))/2; 
        answer.append(a, 'l'); //되돌아갈 거리를 제외하고 갈수 있는 만큼 왼쪽으로
        answer.append(remain - a, 'r'); //도착지점 밑까지 쭉 오른쪽으로
        answer.append(n - r, 'u'); //도착지점까지 쭉 위로
    }
    else{ //최하단을 거치고 갈 수 없는 경우 -> U자 형태로 된 구조만 가능
        int a = (k - abs(c-y) - (r - x))/2;
        answer.append(a, 'd'); //되돌아갈 거리를 제외하고 갈 수 있는 만큼 아래로
        if(c - y > 0) answer.append(c - y, 'r'); //도착지점의 방향으로 열을 맞춤
        else answer.append(y - c, 'l');
        answer.append(a + r - x, 'u'); //도착지점까지 쭉 위로
    } 
 
    
    return answer;
}
