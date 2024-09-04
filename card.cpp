//https://school.programmers.co.kr/learn/courses/30/lessons/258707
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;

int solution(int coin, vector<int> cards) {
    int answer = 1; //손패를 못내는 라운드도 세니 1부터 시작
    int n = cards.size();
    vector<int> hand; //손에 들고 있는 카드 => 초기에 뽑는 n/3개
    vector<int> sub; //뽑을지 말지 결정해야하는 후보 카드
    auto a = cards.begin() + cards.size()/3; //카드 덱을 전체적으로 훑을 반복자
    hand.assign(cards.begin(), a); //손패에 초기카드 뽑기
    while(true){
        bool pass = false; //이번턴에 카드를 냈는지 체크하는 변수
        //카드 두장 뽑아서 서브에 넣기
        sub.push_back(*a++);
        sub.push_back(*a++);
        
        for(auto i: hand){
            auto b = find(hand.begin(), hand.end(), n - i + 1); //패에 있는 카드끼리 조합해 카드를 낼 수 있는지 체크
            if(b != hand.end()){ //낼 수 있다면 두 카드를 제거하고 이번턴 넘기기
                answer++;
                hand.erase(b);
                b = find(hand.begin(), hand.end(), i);
                hand.erase(b);
                pass = true;
                break;
            }
        }
        if(!pass and coin > 0){ //패에 있는 카드끼리는 조합이 안되지만, 서브에 있는 카드와 패에 있는 카드가 조합이 되고, 코인을 보유하고 있는 경우 확인
            for(auto i: hand){
                auto b = find(sub.begin(), sub.end(), n - i + 1);
                if(b != sub.end()){ //낼 수 있다면 코인하나를 소모하고 패와 서브에서 카드를 제거하고 턴 넘기기
                    answer++;
                    sub.erase(b);
                    b = find(hand.begin(), hand.end(), i);
                    hand.erase(b);
                    pass = true;
                    coin--;
                    break;
                }
            }
            if(!pass and coin > 1){ //서브에서만 카드를 조합할 수 있는 경우 확인
                for(auto i: sub){
                    auto b = find(sub.begin(), sub.end(), n - i + 1);
                    if(b != sub.end()){ //낼 수 있다면 코인 두개를 소모하고 서브에서 두 카드를 제거하고 턴넘기기
                        answer++;
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
        if(!pass or a == cards.end()) break; //더이상 뽑을 카드가 없거나, 이번턴에 카드를 낼 수 없다면 게임 종료
    }
    
    return answer;
}
