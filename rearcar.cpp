//https://school.programmers.co.kr/learn/courses/30/lessons/250134
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
bool movable(pair<int,int> a, pair<int, int> b, int n, int m);
  
int solution(vector<vector<int>> maze) {
    int answer = 0;
    vector<pair<int,int>> direction = {{-1,0}, {1,0}, {0,1}, {0,-1}}; //이동할 수 있는 방향
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<int>> init_rvisit(n, vector<int>(m, 0)); //초기 빨간 수레의 방문행렬
    vector<vector<int>> init_bvisit(n, vector<int>(m, 0)); //초기 파란 수레의 방문행렬
    
    pair<int, int> rstart, bstart, rend, bend; //각 수레의 시작, 도착지점 
    
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
    
    queue<vector<pair<int,int>>> candidate; //가능한 빨간수레와 파란수레의 위치를 저장하는 큐
    queue<vector<vector<vector<int>>>> visitedcandidate; //위 큐의 노드 위치에 각 수레가 있을때의 방문 행렬을 저장하는 큐
    //방문행렬이지만, 거리를 알아야하므로 0은 방문x 다른 숫자는 시작지점에서 해당위치까지 이동한 거리를 의미
    candidate.push({rstart, bstart});
    visitedcandidate.push({init_rvisit, init_bvisit});
    vector<vector<int>> rvisit, bvisit;
    bool r = false, b = false; //수레가 도착했는지 여부
    
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
        
        if(r and b) break; // 두 수레가 모두 도착했으면 끝
        
        else if(!r and !b){둘다 도착하지 못한 경우
            for(auto dir: direction){ 
                int rnexti = rcur.first + dir.first;
                int rnextj = rcur.second + dir.second;
                pair<int, int> rnext = make_pair(rnexti, rnextj); //빨간 수레의 다음 위치
                if(!movable(dir, rcur, n, m)) continue; //수레가 판을 넘어서는 경우 제외
                if(maze[rnexti][rnextj] == 5) continue; //수레가 벽으로 가는 경우 제외
                if(rvisit[rnexti][rnextj] != 0) continue; //수레가 이미 왔던곳으로 가는 경우 제외
                for(auto dir2: direction){
                    int bnexti = bcur.first + dir2.first;
                    int bnextj = bcur.second + dir2.second;
                    pair<int, int> bnext = make_pair(bnexti, bnextj); //파란 수레의 다음 위치
                    if(!movable(dir2, bcur, n, m)) continue; //수레가 판을 넘어서는 경우 제외
                    if (maze[bnexti][bnextj] == 5) continue; //수레가 벽으로 가는 경우 제외
                    if (bvisit[bnexti][bnextj] != 0) continue; //수레가 이미 왔던곳으로 가는 경우 제외
                    if (rnext == bnext) continue; //두 수레가 같은 곳으로 향하는 경우 제외
                    if ((rcur == bnext) and (bcur == rnext)) continue; //두 수레가 위치를 서로 바꾸는 경우 제외
                    //bfs를 위해 상태를 큐에 저장
                    candidate.push({rnext,bnext});
                    rvisit[rnexti][rnextj] = rvisit[rcur.first][rcur.second] + 1;
                    bvisit[bnexti][bnextj] = bvisit[bcur.first][bcur.second] + 1;
                    visitedcandidate.push({rvisit, bvisit});
                    //저장후에는 다른 방향을 찾기 위해 원상 복구
                    rvisit[rnexti][rnextj] = 0;
                    bvisit[bnexti][bnextj] = 0;
                }
            }
        }
        else if(!r){ //파란수레만 도착한 경우 -> 파란 수레는 위치 고정
            for(auto dir: direction){
                int rnexti = rcur.first + dir.first;
                int rnextj = rcur.second + dir.second;
                pair<int, int> rnext = make_pair(rnexti, rnextj); //빨간 수레의 다음 위치
                if(!movable(dir, rcur, n, m)) continue; //수레가 판을 넘어서는 경우 제외
                if(maze[rnexti][rnextj] == 5) continue; //수레가 벽으로 가는 경우 제외
                if(rvisit[rnexti][rnextj] != 0) continue; //수레가 이미 왔던곳으로 가는 경우 제외
                if(rnext == bcur) continue; //빨간 수레가 파란수레의 위치로 가는 경우
                //bfs를 위해 상태를 큐에 저장
                candidate.push({rnext, bcur});
                rvisit[rnexti][rnextj] = rvisit[rcur.first][rcur.second] + 1;
                visitedcandidate.push({rvisit, bvisit});
                //저장후에는 다른 방향을 찾기 위해 원상 복구
                rvisit[rnexti][rnextj] = 0;
            }
        }
        else{ //빨간 수레만 도착한 경우 -> 빨간 수레는 위치 고정
            for(auto dir: direction){
                int bnexti = bcur.first + dir.first;
                int bnextj = bcur.second + dir.second;
                pair<int, int> bnext = make_pair(bnexti, bnextj); //파란 수레의 다음 위치
                if(!movable(dir, bcur, n, m)) continue; //수레가 판을 넘어서는 경우 제외
                if(maze[bnexti][bnextj] == 5) continue; //수레가 벽으로 가는 경우 제외
                if(bvisit[bnexti][bnextj] != 0) continue; //수레가 이미 왔던곳으로 가는 경우 제외
                if(make_pair(bnexti, bnextj) == rcur) continue; //파란수레가 빨간 수레의 위치로 가는 경우
                //bfs를 위해 상태를 큐에 저장
                candidate.push({rcur, bnext});
                bvisit[bnexti][bnextj] = bvisit[bcur.first][bcur.second] + 1;
                visitedcandidate.push({rvisit, bvisit});
                //저장후에는 다른 방향을 찾기 위해 원상 복구
                bvisit[bnexti][bnextj] = 0;
            }
        }
    } 
    if(r and b) answer = max(rvisit[rend.first][rend.second], bvisit[bend.first][bend.second]) - 1; // 두 수레 모두 도착했다면, 두 수레가 도착할 때까지 필요한 거리중 최대값 -1(시작지점을 1로 놓고 시작했으므로)
    else answer = 0;
    return answer;
}
//수레가 판을 넘어가는지 확인하는 함수
bool movable(pair<int,int> a, pair<int, int> b, int n, int m){
    if(a.first + b.first < 0) return false;
    if(a.first + b.first >= n) return false;
    if(a.second + b.second < 0) return false;
    if(a.second + b.second >= m) return false;
    return true;
}
