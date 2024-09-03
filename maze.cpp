//https://school.programmers.co.kr/learn/courses/30/lessons/150365#
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int minstep = abs(x-r) + abs(y-c);
    if(abs(minstep - k) %2 != 0 or minstep > k ) return "impossible";
    if(k >= 2 * n -r + c - x + y - 2){
        answer.append(n - x, 'd');
        answer.append(y - 1, 'l');
        for(int i = 0; i< (k - (n - r) - (c - 1) - (n-x) - (y-1)); i++){
            if(i%2 == 0) answer += "r";
            else answer += "l";
        }
        answer.append(c - 1, 'r');
        answer.append(n - r, 'u');
    } 
    else if(k >= 2 * n - x - r){
        answer.append(n - x, 'd');
        int remain = k - (2 * n - x - r);
        int a = (remain - (c - y))/2;
        answer.append(a, 'l');
        answer.append(remain - a, 'r');
        answer.append(n - r, 'u');
    }
    else{
        int a = (k - abs(c-y) - (r - x))/2;
        answer.append(a, 'd');
        if(c - y > 0) answer.append(c - y, 'r');
        else answer.append(y - c, 'l');
        answer.append(a + r - x, 'u');
    } 
 
    
    return answer;
}
