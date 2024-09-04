//https://school.programmers.co.kr/learn/courses/30/lessons/250134
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
bool movable(pair<int,int> a, pair<int, int> b, int n, int m);
  
int solution(vector<vector<int>> maze) {
    int answer = 0;
    vector<pair<int,int>> direction = {{-1,0}, {1,0}, {0,1}, {0,-1}};
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<int>> init_rvisit(n, vector<int>(m, 0));
    vector<vector<int>> init_bvisit(n, vector<int>(m, 0));
    
    pair<int, int> rstart, bstart, rend, bend;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(maze[i][j] == 1) rstart = {i, j};
            else if(maze[i][j] == 2) bstart = {i, j};
            else if(maze[i][j] == 3) rend = {i, j};
            else if(maze[i][j] == 4) bend = {i, j};
        }
    }
    init_rvisit[rstart.first][rstart.second] = 1;
    init_bvisit[bstart.first][bstart.second] = 1;
    
    queue<vector<pair<int,int>>> candidate;
    queue<vector<vector<vector<int>>>> visitedcandidate;
    
    candidate.push({rstart, bstart});
    visitedcandidate.push({init_rvisit, init_bvisit});
    vector<vector<int>> rvisit, bvisit;
    bool r = false, b = false;
    
    while(!candidate.empty() and !visitedcandidate.empty()){
        r = false, b = false;
        pair<int, int> rcur = candidate.front()[0];
        pair<int, int> bcur = candidate.front()[1];
        
        rvisit = visitedcandidate.front()[0];
        bvisit = visitedcandidate.front()[1];
        
        candidate.pop();
        visitedcandidate.pop();
        
        if(rcur == rend) r = true;
        if(bcur == bend) b = true;
        
        if(r and b) break;
        
        else if(!r and !b){
            for(auto dir: direction){
                int rnexti = rcur.first + dir.first;
                int rnextj = rcur.second + dir.second;
                pair<int, int> rnext = make_pair(rnexti, rnextj);
                if(!movable(dir, rcur, n, m)) continue;
                if(maze[rnexti][rnextj] == 5) continue;
                if(rvisit[rnexti][rnextj] != 0) continue;
                for(auto dir2: direction){
                    int bnexti = bcur.first + dir2.first;
                    int bnextj = bcur.second + dir2.second;
                    pair<int, int> bnext = make_pair(bnexti, bnextj);
                    if(!movable(dir2, bcur, n, m)) continue;
                    if (maze[bnexti][bnextj] == 5) continue;
                    if (bvisit[bnexti][bnextj] != 0) continue;
                    if (rnext == bnext) continue;
                    if ((rcur == bnext) and (bcur == rnext)) continue;
                    candidate.push({rnext,bnext});
                    rvisit[rnexti][rnextj] = rvisit[rcur.first][rcur.second] + 1;
                    bvisit[bnexti][bnextj] = bvisit[bcur.first][bcur.second] + 1;
                    visitedcandidate.push({rvisit, bvisit});
                    rvisit[rnexti][rnextj] = 0;
                    bvisit[bnexti][bnextj] = 0;
                }
            }
        }
        else if(!r){
            for(auto dir: direction){
                int rnexti = rcur.first + dir.first;
                int rnextj = rcur.second + dir.second;
                pair<int, int> rnext = make_pair(rnexti, rnextj);
                if(!movable(dir, rcur, n, m)) continue;
                if(maze[rnexti][rnextj] == 5) continue;
                if(rvisit[rnexti][rnextj] != 0) continue;
                if(rnext == bcur) continue;
                candidate.push({rnext, bcur});
                rvisit[rnexti][rnextj] = rvisit[rcur.first][rcur.second] + 1;
                visitedcandidate.push({rvisit, bvisit});
                rvisit[rnexti][rnextj] = 0;
            }
        }
        else{
            for(auto dir: direction){
                int bnexti = bcur.first + dir.first;
                int bnextj = bcur.second + dir.second;
                pair<int, int> bnext = make_pair(bnexti, bnextj);
                if(!movable(dir, bcur, n, m)) continue;
                if(maze[bnexti][bnextj] == 5) continue;
                if(bvisit[bnexti][bnextj] != 0) continue;
                if(make_pair(bnexti, bnextj) == rcur) continue;
                candidate.push({rcur, bnext});
                bvisit[bnexti][bnextj] = bvisit[bcur.first][bcur.second] + 1;
                visitedcandidate.push({rvisit, bvisit});
                bvisit[bnexti][bnextj] = 0;
            }
        }
    } 
    if(r and b) answer = max(rvisit[rend.first][rend.second], bvisit[bend.first][bend.second]) - 1;
    else answer = 0;
    return answer;
}
bool movable(pair<int,int> a, pair<int, int> b, int n, int m){
    if(a.first + b.first < 0) return false;
    if(a.first + b.first >= n) return false;
    if(a.second + b.second < 0) return false;
    if(a.second + b.second >= m) return false;
    return true;
}
