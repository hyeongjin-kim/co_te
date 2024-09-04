//https://school.programmers.co.kr/learn/courses/30/lessons/132266?language=cpp
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    
    vector<vector<int>> v(n + 1); //인접리스트
    
    for(auto r: roads){
        int a = r[0];
        int b = r[1];
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    vector<int> node(n + 1, n + 1); //각 노드까지의 거리를 저장
    node[destination] = 0; //도착지점은 0으로
    #각 노드에서 도착지점까지의 거리를 구하므로, UCS를 통해 도착지점에서 각 노드까지의 거리들을 모두 구하면 됨
    priority_queue<int> q;
    q.push(destination); //도착지점을 시작지점으로 삼아서 push
    
    while(!q.empty()){
        int cur = q.top();
        q.pop();
        for(auto a: v[cur]){//현재 노드에서 갈 수 있는 노드들 중, 현재 노드에서 가는게 지금까지 저장된 거리보다 짧은 경우 q에 추가
            if(node[a] > node[cur] + 1){
                node[a] = node[cur] + 1;
                q.push(a);
            }
        }
    }
    
    for(auto s: sources){ //노드들 중 소스에 있는 노드들만 거리를 조회, answer에 저장
        if(node[s] == n + 1) answer.push_back(-1);
        else answer.push_back(node[s]);
    }
    
    return answer;
}
