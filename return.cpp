//https://school.programmers.co.kr/learn/courses/30/lessons/132266?language=cpp
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    
    vector<vector<int>> v(n + 1);
    
    for(auto r: roads){
        int a = r[0];
        int b = r[1];
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    vector<int> node(n + 1, n + 1);
    node[destination] = 0;
    priority_queue<int> q;
    q.push(destination);
    
    while(!q.empty()){
        int cur = q.top();
        q.pop();
        for(auto a: v[cur]){
            if(node[a] > node[cur] + 1){
                node[a] = node[cur] + 1;
                q.push(a);
            }
        }
    }
    
    for(auto s: sources){
        if(node[s] == n + 1) answer.push_back(-1);
        else answer.push_back(node[s]);
    }
    
    return answer;
}
