//https://school.programmers.co.kr/learn/courses/30/lessons/150365#
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int minstep = abs(x-r) + abs(y-c); //최단거리
    //k에서 최단거리를 뺀만큼 소모해야함 -> 그만큼 어디론가 갔다가 되돌아와야함 -> 2의 배수만큼 필요
    //즉 k와 최단거리의 차가 홀수면 불가능 또는, k가 최단거리보다 작으면 불가능
    if(abs(minstep - k) %2 != 0 or minstep > k ) return "impossible";
    
    int rest = k - minstep; //남은거리
    int rcount = 0; //최단경로중 오른쪽으로 가는 횟수
    int lcount = 0; //최단경로중 왼쪽으로 가는 횟수
    int ucount = 0; //최단경로중 위로 가는 횟수
    int dcount = 0; //최단경로중 아래로 가는 횟수
    if(x - r > 0) ucount+= x-r; 
    else dcount += r-x;
    if(y - c > 0) lcount += y-c;
    else rcount += c-y;

    //최단경로를 제외하고, 남는 것은 반드시 아래 <-> 위, 왼쪽 <-> 아래 쌍을 지어 이동함 그래야 중간에 이동이 추가되어도 도착지점으로 돌아오니까
    //알파벳이 d, l, r, u 순이므로 최대한 좌하단으로 갔다가, 되돌아갈 거리를 제외하고 남은 만큼 좌우좌우를 반복하고, 돌아가는게 사전순서상 가장 빠름
    //위 또는 아래로 이동할 횟수
    int dplus = min(rest/2, n - max(x,r)); //아래로 다 가지 못한다면, 남는 만큼의 절반만큼 내려갔다가 올라감 / 맨 아래까지 내려감
    
    rest -= dplus * 2; //아래와 위로 가는 횟수 제외 
    //왼쪽 또는 오른쪽으로 이동할 횟수
    int lplus = min(rest/2, min(y,c) - 1); //왼쪽으로 다 가지 못한 다면, 남는 만큼의 절반만큼 왼쪽으로 갔다가 오른쪽으로 감 / 맨 왼쪽으로 감
    
    rest -= lplus * 2; //왼쪽과 오른쪽으로 가는 횟수 제외
    
    answer.append(dcount + dplus,'d'); // 아래로 가는 횟수
    answer.append(lcount + lplus, 'l'); //왼쪽으로 가는 횟수
    //남는 만큼 오른쪽 왼쪽을 반복
    //이때 반드시 (n.1)에서 끝남 왜냐하면 그렇지 않은 경우는 k-최단거리가 홀수이기 때문
    for(int i = 0; i< rest; i++){
        if(i%2 == 0) answer += "r";
        else answer += "l";
    }
    answer.append(rcount+ lplus,'r'); //오른쪽으로 가는 횟수
    answer.append(ucount + dplus, 'u'); //왼쪽으로 가는 횟수
    return answer;
}
