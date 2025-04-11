#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//평면의 정보를 저장하는 배열
int base[20][20];
//평면의 각 셀에 해당하는 index를 저장하는 배열
int baseidx[20][20];
//시간의 벽의 정보를 저장하는 배열
int cube[5][10][10];
//시간의 벽의 각 셀에 해당하는 index를 저장하는 배열
int cubeidx[5][10][10];

//이동하는 배열 좌우하상 순(이유: 시간의 벽이 동 서 남 북으로 들어옴 평면에서 시간의 벽이 있는 구간에 저 순서대로 진입하면 인덱스가 똑같아짐 
//dr[1], dc[1]로 이동해서 시간의 벽 구역에 들어가면 오른쪽 이동이므로 서쪽 벽에 진입함 -> cube[1][row][col] 에 진입하게 됨

int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

//갈 수 없는 곳을 표기
int INF = 1e9;

//그래프를 저장하는 인접리스트 배열
vector<vector<int>> adj(800, vector<int>());

int dist[800]; //타임머신에서부터 각 인덱스에 해당하는 지역까지 도달하기 위한 거리를 저장

struct Event { //이상현상의 정보를 저장하는 구조체
	int r;
	int c;
	int dir;
	int v;
	int is_alive = 1;
};

Event event[10]; //이상 현상을 저장하는 배열

int main() {

	int N, M, F;
	
	cin >> N >> M >> F;
	int index = 0;//각 셀에 번호를 매기기 위함

	int sr = -1 , sc = -1, er = -1, ec = -1, cr = -1, cc = -1; //순서대로 시작지점의 r, c좌표, 도착지점의 r, c좌표, 시간의 벽의 r, c좌표

  //평면도를 돌면서 입력을 받고, 시간의 벽 구간의 왼쪽 위 모서리를 찾으면 그 위치를 표기 -> 나중에 평면도와 시간의 벽을 연결할 때 좌표를 계산할 기준으로 삼기 위함
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> base[i][j];
			if (base[i][j] == 3) {
				if (cr == -1)cr = i, cc = j;
				else continue;
			}
			else {
				baseidx[i][j] = ++index; //시간의 벽위치가 아니면 인덱스 부여
				if (base[i][j] == 4) { //도착지점 메모
					er = i, ec = j;
				}
			}
		}
	}
  //시간의벽의 각 면을 돌면서 입력을 받아옴
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				
				cin >> cube[k][i][j]; 
				cubeidx[k][i][j] = ++index; //인덱스 부여
				if (cube[k][i][j] == 2) sr = i, sc = j; //출발지점 메모
			}
		}
	}
	//아래 -> 북 3
	//위 -> 남2
	//오른쪽 -> 서 1
	//왼쪽 -> 동 0
  //평면도를 돌면서 상하좌우 셀을 연결하는 간선을 저장함
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (base[r][c] == 3) continue;
			int idx = baseidx[r][c];
			for (int i = 0; i < 4; i++) {
				int newr = r + dr[i], newc = c + dc[i];
				if (newr < 0 or newr >= N or newc < 0 or newc >= N) continue; //평면도를 벗어나는 경우 넘어감
				if (base[newr][newc] == 3) { //시간의 벽과 만나는 곳인 경우
					if (i == 0) { // 왼쪽으로 이동해 시간의 벽과 만남 -> 벽의 동쪽 면과 만나는 것 
						adj[idx].push_back(cubeidx[0][M - 1][cr + M - 1 - r]); //평면과 벽을 연결
						adj[cubeidx[0][M - 1][cr + M - 1 - r]].push_back(idx); //벽과 평면을 연결
					} 
					else if (i == 1) { //오른쪽으로 이동해 시간의 벽과 만남 -> 벽의 서쪽면과 만나는 것
						adj[idx].push_back(cubeidx[1][M - 1][r - cr]); //평면과 벽을 연결
						adj[cubeidx[1][M - 1][r - cr]].push_back(idx); //벽과 평면을 연결
					}
					else if (i == 2) { //위로 이동해 시간의 벽과 만남 -> 벽의 남쪽 면과 만나는 것
						adj[idx].push_back(cubeidx[2][M - 1][c - cc]); //평면과 벽을 연결
						adj[cubeidx[2][M - 1][c - cc]].push_back(idx); //벽과 평면을 연결
					}
					else { //아래로 이동해 시간의 벽과 만남 -> 벽의 북쪽 면과 만나는 것
						adj[idx].push_back(cubeidx[3][M - 1][cc + M - 1 - c]); //평면과 벽을 연결
						adj[cubeidx[3][M - 1][cc + M - 1 - c]].push_back(idx); //벽과 평면을 연결
					}
				}
				else adj[idx].push_back(baseidx[newr][newc]); //시간의 벽과 만나는 곳이 아니고 평면도를 넘어가지 않으면 원래 칸과 연결
			}

		}
	}

	int cw[4] = { 2, 3, 1, 0 }; //각 면이 시계방향으로 돌았을 때 가는 면의 인덱스
	int ccw[4] = { 3, 2, 0, 1 }; //각 면이 반시계 방향으로 돌았을 때 가는 면의 인덱스

  //시간의 벽의 각 면(윗면 제외)를 돌면서 상하좌우 셀을 연결하는 간선을 저장함
	for (int k = 0; k < 4; k++) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				int idx = cubeidx[k][r][c];
				for (int i = 0; i < 4; i++) {
					int newr = r + dr[i], newc = c + dc[i];
					if (newr < 0 or newr >= M) continue; //위 아래로 이동하는 경우는 넘어감 윗면은 뒤에 연결하고, 평면도와는 이미 연결함

					if (newc < 0) {
						adj[idx].push_back(cubeidx[cw[k]][newr][M - 1]); //왼쪽으로 넘어가는 경우 시계방향으로 돌아서 만나는 면과 연결
					}
					else if (newc >= M) {
						adj[idx].push_back(cubeidx[ccw[k]][newr][0]); //오른쪽으로 넘어가는 경우, 반시계방향으로 돌아서 만나는 면과 연결
					}
					else adj[idx].push_back(cubeidx[k][newr][newc]); //면을 넘어가지 않으면 아니면 원래 셀과 연결
				}
			}
		}
	}
  //윗면을 돌면서 상하좌우 셀을 연결하는 간선을 추가
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			int idx = cubeidx[4][r][c];
			for (int i = 0; i < 4; i++) {
				int newr = r + dr[i], newc = c + dc[i];

				if (newc < 0) { //왼쪽으로 넘어가는 경우 서쪽면과 만남
					adj[idx].push_back(cubeidx[1][0][newr]); //서쪽면과 연결
					adj[cubeidx[1][0][newr]].push_back(idx);
				}
				else if (newc >= M) { //오른쪽으로 넘어가는 경우 동쪽면과 만남
					adj[idx].push_back(cubeidx[0][0][M - 1 - newr]);
					adj[cubeidx[0][0][M - 1 - newr]].push_back(idx);

				}
				else if (newr < 0) { //위로 넘어가는 경우 북쪽면과 만남
					adj[idx].push_back(cubeidx[3][0][M - 1 - newc]);
					adj[cubeidx[3][0][M - 1 - newc]].push_back(idx);
				}
				else if (newr >= M) { //아래로 넘어가는 경우 남쪽면과 만남
					adj[idx].push_back(cubeidx[2][0][newc]);
					adj[cubeidx[2][0][newc]].push_back(idx);
				}
				else adj[idx].push_back(cubeidx[4][newr][newc]); //면을 넘어가지 않으면 원래 셀과 연결
			}

		}
	}


	//북 3 
	//남 2 
	//서 1 
	//동 0 
	for (int i = 0; i < F; i++) { //이상현상의 정보를 받아옴
		cin >> event[i].r >> event[i].c >> event[i].dir >> event[i].v;
	}

	fill(dist, dist + index + 1, -1); //거리를 저장하는 배열을 -1로 초기화

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (base[r][c] == 1) dist[baseidx[r][c]] = INF; //장애물이 있는경우 갈 수 없는 곳으로 표기
		}
	}

	for (int k = 0; k < 5; k++) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				if (cube[k][r][c] == 1) dist[cubeidx[k][r][c]] = INF; //장애물이 있는경우 갈 수 없는 곳으로 표기
			}
		}
	}

	//이벤트가 움직이기 위한 방향 배열
	int edr[4] = { 0, 0, 1, -1 };
	int edc[4] = { 1,-1,0,0 };

	for (int i = 0; i < F; i++) { //이상현상이 있는경우 갈 수 없는 곳으로 표기
		int idx = baseidx[event[i].r][event[i].c];
		dist[idx] = INF;
	}
	int curidx = cubeidx[4][sr][sc]; //시작위치의 인덱스
	int endidx = baseidx[er][ec];  //도착위치의 인덱스
	queue<int> list; //이동할 셀의 인덱스들을 저장하는 리스트
	list.push(curidx);
	dist[curidx] = 0; //시작지점의 거리를 1로 초기화
	int run = 1;
	for (; ; run++) {
    //이상현상 업데이트
		for (int i = 0; i < F; i++) {
			if (event[i].is_alive == 0) continue; //비활성화된 경우 넘어감
			if ((run % event[i].v) == 0) { //확장 주기가 아닌 경우 넘어감
				int r = event[i].r, c = event[i].c, dir = event[i].dir; //정보를 가져옴
				int newr = r + edr[dir], newc = c + edc[dir]; //이상현상이 확장될 위치

				if (newr < 0 or newr >= N or newc < 0 or newc >= N) { //이상현상이 칸을 넘어서는 경우 비활성화
					event[i].is_alive = 0;
					continue;
				}

				int idx = baseidx[newr][newc]; //확장될 곳의 인덱스
				if (dist[idx] == INF) { //확장될 곳에 장애물이 있는 경우 비활성화함
					event[i].is_alive = 0;
					continue;
				}
				if (idx == endidx) { //도착지점으로는 못감 도착지점과 마주해도 비활성화
					event[i].is_alive = 0;
					continue;
				}
				dist[idx] = INF; //확장될 곳을 못가는 곳으로 표기
				event[i].r = newr, event[i].c = newc; //이상현상확장
			}
		}
		queue<int> next; 다음에 이동할 셀의 인덱스를 저장할 큐
		while (!list.empty()) {
			int idx = list.front();
			list.pop();
			for (int i = 0; i < adj[idx].size(); i++) {
				if (dist[adj[idx][i]] != -1) continue; //이미 거리가 계산된 셀인 경우 넘어감
				dist[adj[idx][i]] = dist[idx] + 1; //현재 위치에서 1증가된 거리로 저장
				next.push(adj[idx][i]); //이동할 셀을 저장하는 큐에 추가
			}
		}
		if (dist[baseidx[er][ec]] != -1) break; //도착지점에 도착한 경우 종료
		if (next.empty()) break; //더이상 이동할 셀이 없는 경우 종료

		while (!next.empty()){ //다음에 이동할 셀을 next에서 list로 옮김
      //이렇게 하는 이유: 한칸씩 이동후 이상현상이 확장되는 턴이 있어야 하므로 각 턴을 구분하기 위해서 큐를 두개 사용함
			list.push(next.front());
			next.pop();
		}
	}
	if (dist[baseidx[er][ec]] != -1) cout << dist[baseidx[er][ec]]; //도착지점에 도착한 경우 그 거리 출력
  else cout << -1; //도착하지 못한 경우
//디버깅을 위해 모든 셀의 정보를 출력하는 과정
	/*cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (dist[baseidx[i][j]] == INF) cout << " x" << ' ';
			else cout << dist[baseidx[i][j]] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if(dist[cubeidx[k][i][j]] == INF) cout << "x" << ' ';
				else cout << dist[cubeidx[k][i][j]] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}*/

	return 0;
}
