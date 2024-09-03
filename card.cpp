//https://school.programmers.co.kr/learn/courses/30/lessons/258707
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;

int solution(int coin, vector<int> cards) {
    int answer = 1;
    vector<int> hand;
    vector<int> sub;
    auto a = cards.begin() + cards.size()/3;
    hand.assign(cards.begin(), a);
    int preturn = 0;
    int n = cards.size();
    while(true){
        bool pass = false;
        sub.push_back(*a++);
        sub.push_back(*a++);
        
        for(auto i: hand){
            auto b = find(hand.begin(), hand.end(), n - i + 1);
            if(b != hand.end()){
                answer++;
                preturn++;
                hand.erase(b);
                b = find(hand.begin(), hand.end(), i);
                hand.erase(b);
                pass = true;
                break;
            }
        }
        if(!pass and coin > 0){
            for(auto i: hand){
                auto b = find(sub.begin(), sub.end(), n - i + 1);
                if(b != sub.end()){
                    answer++;
                    preturn++;
                    sub.erase(b);
                    b = find(hand.begin(), hand.end(), i);
                    hand.erase(b);
                    pass = true;
                    coin--;
                    break;
                }
            }
            if(!pass and coin > 1){
                for(auto i: sub){
                    auto b = find(sub.begin(), sub.end(), n - i + 1);
                    if(b != sub.end()){
                        answer++;
                        preturn++;
                        sub.erase(b);
                        b = find(sub.begin(), sub.end(), i);
                        sub.erase(b);
                        pass = true;
                        coin-=2;
                        break;
                    }
                }
            }
        }
        if(!pass or a == cards.end()) break;
    }
    
    return answer;
}
