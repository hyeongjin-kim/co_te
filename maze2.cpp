//https://school.programmers.co.kr/learn/courses/30/lessons/150365#
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int minstep = abs(x-r) + abs(y-c);
    if(abs(minstep - k) %2 != 0 or minstep > k ) return "impossible";
    
    int rest = k - minstep;
    int rcount = 0;
    int lcount = 0;
    int ucount = 0;
    int dcount = 0;
    if(x - r > 0) ucount+= x-r;
    else dcount += r-x;
    if(y - c > 0) lcount += y-c;
    else rcount += c-y;
    
    int dplus = min(rest/2, n - max(x,r));
    rest -= dplus * 2;
    int lplus = min(rest/2, min(y,c) - 1);
    rest -= lplus * 2;
    
    answer.append(dcount + dplus,'d');
    answer.append(lcount + lplus, 'l');
    for(int i = 0; i< rest; i++){
        if(i%2 == 0) answer += "r";
        else answer += "l";
    }
    answer.append(rcount+ lplus,'r');
    answer.append(ucount + dplus, 'u');
    return answer;
}
