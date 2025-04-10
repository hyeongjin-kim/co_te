#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, sr, sc, er, ec;

//기사의 정보
struct Knight {
	int idx; //디버그상 편의를 위한 인덱스
	//기사의 좌표
  int r;
	int c;
  //생존 여부
	int is_alive = 1;
  //기절 여부
	int is_stun = 0;
};

//기사 구조체 배열
Knight knight[300];

//메두사의 시선을 결정하고 나서 다시 기사의 기절여부를 보지 않기 위해 특정 방향을 봤을 때의 기절 여부를 저장함
//추후에 알게되었는데 그냥 자기 위치가 시선에 포함되면 기절하는 쪽으로 해도 됨 굳이 이 배열이 필요하지 않음
int is_stun[4][300];

//움직임을 위한 방향 배열(상하좌우)
//좌우상하로 움직이기 위해서는 dir을 2 ~ 6으로 두고 dr[dir%4]로 접근
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

//메두사가 사용하는 지도 도로 여부만 저장함
int mmap[50][50] = {};
//메두사가 이동할 경로를 구하기 위한 방문 배열
//이동이 불가능한 경우 0, 가능한 경우 도착지점까지의 거리를 저장
//추후에 알게 되었는데 초기화를 INF로 두고 이동이 불가능 한 경우를 제외하는 식으로 하면 if문을 줄일 수 있음
int mvisit[50][50] = {};
//기사들의 위치를 기록한 배열 이 위에서 따로 이동을 표시하지는 않고 그저 턴이 시작되었을 때의 위치를 표시함
int kmap[50][50] = {};
//기사들이 메두사까지 이동할 경로를 구하기 위한 방문배열
//메두사의 시선이 닿는 경우 0, 이동이 가능한 경우 메두사까지의 거리를 저장
int kvisit[50][50] = {};

//메두사가 특정 방향을 보았을 때의 시야를 저장
//시선은 1, 기사에 가려져 보이지 않는 사각지대는 2 그외 0
//이를 3차원 배열로 만들어 저장했다면 뒤에 결정된 시야을 복사할 때 더 편했을 듯
int usight[50][50] = {}; //위를 보았을 때
int rsight[50][50] = {}; //오른쪽을 보았을 때
int dsight[50][50] = {}; //아래를 보았을 때
int lsight[50][50] = {}; //왼쪽을 보았을 때

//위 네가지 방향을 확인하고 가장 많은 기사를 돌로 만드는 방향을 고름
//결정된 방향의 시야를 저장해 실제 기사의 움직임을 구할 때 사용할 배열
int sight[50][50] = {};


//메두사의 이동 경로를 구하는 bfs
void mbfs() {

	queue<pair<int, int>> q;
  //공원에서부터 출발해 각 셀까지의 거리를 저장
  //출발지인 공원 위치를 큐에 삽입
	q.push({ er, ec });
	mvisit[er][ec] = 1;
	while (!q.empty()) {
		
		pair<int, int> cur = q.front();
		q.pop();
		int r = cur.first, c = cur.second;
    //4가지 방향을 돌면서 확인
		for (int i = 0; i < 4; i++) {
			int newr = r + dr[i], newc = c + dc[i]; //이동한 이후의 위치
			if (newr < 0 or newr >= N or newc < 0 or newc >= N) continue; //맵을 벗어나면 넘어감
			if (mmap[newr][newc] == 1) continue; //도로가 아니면 넘어감
			if (mvisit[newr][newc] != 0) continue; //이미 방문한 곳이면 넘어감
			q.push({ newr, newc }); //큐에 삽입
			mvisit[newr][newc] = mvisit[r][c] + 1; //셀의 거리 업데이트
		}
	}

}

//기사가 메두사까지 가는 경로를 구하기 위한 bfs
//메두사의 위치에서부터 출발해 각 셀까지의 거리를 저장
void kbfs(int rpos, int cpos) {
	queue<pair<int, int>> q;
  //방문배열 초기화 메두사의 경우 한번만 경로를 결정하면 되지만,
  //메두사는 매 턴 움직이기 때문에 매턴 다시 계산해야함
	fill(&kvisit[0][0], &kvisit[0][0] + 50 * 50, 0);
  //시작 위치인 메두사의 위치 삽입
	q.push({ rpos, cpos });
	kvisit[rpos][cpos] = 1;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		int r = cur.first, c = cur.second;

		for (int i = 0; i < 4; i++) {
			int newr = r + dr[i], newc = c + dc[i]; //이동한 이후의 위치
			if (newr < 0 or newr >= N or newc < 0 or newc >= N) continue; //맵을 벗어나면 넘어감
			if (kvisit[newr][newc] != 0) continue; //이미 방문한 곳이면 넘어감
      //시선체크를 여기서 하지 않는 이유: 메두사의 시야에 갇혀 메두사까지 닿을 수 없더라도 사각지대 내에서 움직일 수 있기 때문에
      //모든 셀의 거리를 구한 뒤, 추후에 벽을 세우듯 시야를 설정함
			q.push({ newr, newc }); //큐에 삽입
			kvisit[newr][newc] = 1 + kvisit[r][c]; //셀의 거리 업데이트
		}
		
	}
  //메두사의 시선이 닿는 곳이라면 못가게 하기 위해 0으로 설정
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (sight[i][j] == 1) kvisit[i][j] = 0;
		}
	}
}
//메두사가 위를 바라봤을 때의 시야 계산
int lookup(int r, int c) {
  //시야배열 초기화
	fill(&usight[0][0], &usight[0][0] + 50 * 50, 0);
	//돌로 만든 기사의 수
  int result = 0;
  //위로 올라가면서 체크
	for (int rpos = r - 1 ; rpos >=0 ; rpos--) {
    //시야가 닿는 곳의 범위, 메두사의 위치에서 위로 한 칸 움직일 때마자 좌우로 한칸씩 추가되는데, 맵의 크기와 비교해 맵을 넘어가지 않게 함
		int left = max(0, c - (r - rpos) ), right = min(N - 1, c + (r - rpos));
		for (int cpos = left; cpos <= right; cpos++) {
			if (usight[rpos][cpos] == 2) continue; //이미 사각지대로 처리한 경우 넘어감
			
			if (kmap[rpos][cpos] == 1) { //기사가 현재 칸에 있는 경우
				
				for (int k = 0; k < M; k++) { //모든 기사를 돌면서 이 칸에 있는 경우 돌이 되었다고 표시
					if (knight[k].is_alive == 1 and knight[k].r == rpos and knight[k].c == cpos) {
						result++;
						is_stun[0][k] = 1;
					}
				}
				usight[rpos][cpos] = 1; //이 칸까지는 메두사의 시야에 닿는 곳이므로 1로 표시
				if (cpos == c) { //같은 열에 있는 경우, 맵의 위쪽 끝까지 가면서 이 열에만 2로 사각지대 표시
					for (int row = rpos - 1; row >= 0; row--) usight[row][cpos] = 2;
				}
				else if (cpos < c) { //메두사보다 왼쪽 인 경우
					for (int row = rpos - 1; row >= 0; row--) { 
						int lshadow = max(0, cpos - (rpos - row)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 오른쪽으로는 늘어나지 않음
						for (int col = lshadow; col<= cpos; col++) {
							usight[row][col] = 2;
						}
					}
				}
				else {
					for (int row = rpos - 1; row >= 0; row--) { 
						int rshadow = min(N - 1, cpos + (rpos - row)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 왼쪽으로는 늘어나지 않음
						for (int col = cpos; col <= rshadow; col++) {
							usight[row][col] = 2;
						}
					}
				}

			}
			else usight[rpos][cpos] = 1; //기사가 없고 사각지대가 아니면 시야에 닿는 곳으로 표시
		}
	}
	return result;
}
//메두사가 오른쪽을 바라봤을 때의 시야 계산
int lookright(int r, int c) {
  //시야배열 초기화
	fill(&rsight[0][0], &rsight[0][0] + 50 * 50, 0);
  //돌로 만든 기사의 수
	int result = 0;
  //오른쪽으로 가면서 체크
	for (int cpos = c + 1; cpos < N; cpos++) {
    //시야가 닿는 곳의 범위, 메두사의 위치에서 오른쪽으로 한 칸 움직일 때마자 위아래로 한칸씩 추가되는데, 맵의 크기와 비교해 맵을 넘어가지 않게 함
		int left = max(0, r - (cpos - c)), right = min(N - 1, r + (cpos - c));
		for (int rpos = left; rpos <= right; rpos++) {
			if (rsight[rpos][cpos] == 2) continue; //이미 사각지대로 처리한 경우 넘어감
			if (kmap[rpos][cpos] == 1 ) { //기사가 현재 칸에 있는 경우

				for (int k = 0; k < M; k++) { //모든 기사를 돌면서 이 칸에 있는 경우 돌이 되었다고 표시
					if (knight[k].is_alive == 1 and knight[k].r == rpos and knight[k].c == cpos) {
						result++;
						is_stun[3][k] = 1;
					}
				}

				rsight[rpos][cpos] = 1; //이 칸까지는 메두사의 시야에 닿는 곳이므로 1로 표시

				if (rpos == r) { //같은 행에 있는 경우, 맵의 오른쪽 끝까지 가면서 이 행에만 2로 사각지대 표시
					for (int col = cpos + 1; col < N; col++) rsight[rpos][col] = 2; 
				}
				else if (rpos < r) { //메두사보다 위쪽 인 경우
					for (int col = cpos + 1; col < N; col++) {
						int lshadow = max(0, rpos - (col - cpos)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 아래쪽으로는 늘어나지 않음
						for (int row = lshadow; row <= rpos; row++) {
							rsight[row][col] = 2;
						}
					}
				}
				else {
					for (int col = cpos + 1; col < N; col++) {
						int rshadow = min(N - 1, rpos + (col - cpos));  //메두사의 시야를 체크하던 방식과 같지만, 범위가 위쪽으로는 늘어나지 않음
						for (int row = rpos; row <= rshadow; row++) {
							rsight[row][col] = 2;
						}
					}
				}

			}
			else rsight[rpos][cpos] = 1; //기사가 없고 사각지대가 아니면 시야에 닿는 곳으로 표시
		}

	}
	return result;
}
//메두사가 아래쪽을 바라봤을 때의 시야 계산
int lookdown(int r, int c) {
  //돌로 만든 기사의 수
	int result = 0;
  //시야배열 초기화
	fill(&dsight[0][0], &dsight[0][0] + 50 * 50, 0);
  //아래쪽으로 가면서 체크
	for (int rpos = r + 1; rpos < N; rpos++) {
    //시야가 닿는 곳의 범위, 메두사의 위치에서 아래쪽으로 한 칸 움직일 때마자 좌우로 한칸씩 추가되는데, 맵의 크기와 비교해 맵을 넘어가지 않게 함
		int left = max(0,c - (rpos - r)), right = min(N-1, c + (rpos - r));
		for (int cpos = left; cpos <= right; cpos++) {
			if (dsight[rpos][cpos] == 2) continue; //이미 사각지대로 처리한 경우 넘어감
			if (kmap[rpos][cpos] == 1) { //기사가 현재 칸에 있는 경우
				for (int k = 0; k < M; k++) {
					if (knight[k].is_alive == 1 and knight[k].r == rpos and knight[k].c == cpos) {  //모든 기사를 돌면서 이 칸에 있는 경우 돌이 되었다고 표시
						result++;
						is_stun[1][k] = 1;
					}
				}
				dsight[rpos][cpos] = 1; //이 칸까지는 메두사의 시야에 닿는 곳이므로 1로 표시

				if (cpos == c) {
					for (int row = rpos + 1; row < N; row++) dsight[row][cpos] = 2; //같은 열에 있는 경우, 맵의 아래쪽 끝까지 가면서 이 열에만 2로 사각지대 표시
				}
				else if (cpos < c) { //메두사보다 왼쪽 인 경우
					for (int row = rpos + 1; row < N; row++) {
						int lshadow = max(0, cpos - (row - rpos)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 오른쪽으로는 늘어나지 않음
						for (int col = lshadow; col <= cpos; col++) {
							dsight[row][col] = 2;
						}
					}
				}
				else {
					for (int row = rpos + 1; row < N; row++) {
						int rshadow = min(N - 1, cpos + (row - rpos)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 왼쪽으로는 늘어나지 않음
						for (int col = cpos ; col <= rshadow; col++) {
							dsight[row][col] = 2;
						}
					}
				}


			}
			else dsight[rpos][cpos] = 1; //기사가 없고 사각지대가 아니면 시야에 닿는 곳으로 표시
		}
	}

	return result;
}
//메두사가 왼쪽을 바라봤을 때의 시야 계산
int lookleft(int r, int c) {
  //돌로 만든 기사의 수
	int result = 0;
  //시야배열 초기화
	fill(&lsight[0][0], &lsight[0][0] + 50 * 50, 0);
  //왼쪽으로 가면서 체크
	for (int cpos = c - 1; cpos >= 0; cpos--) {
    //시야가 닿는 곳의 범위, 메두사의 위치에서 왼쪽으로 한 칸 움직일 때마자 위아래로 한칸씩 추가되는데, 맵의 크기와 비교해 맵을 넘어가지 않게 함
		int left = max(0, r - (c - cpos)), right = min(N - 1, r + (c - cpos));
		for (int rpos = left; rpos <= right; rpos++) {
			if (lsight[rpos][cpos] == 2) continue; //이미 사각지대로 처리한 경우 넘어감
			if (kmap[rpos][cpos] == 1) { //기사가 현재 칸에 있는 경우

				for (int k = 0; k < M; k++) {
					if (knight[k].is_alive == 1 and knight[k].r == rpos and knight[k].c == cpos) { //모든 기사를 돌면서 이 칸에 있는 경우 돌이 되었다고 표시
						result++;
						is_stun[2][k] = 1;
					}
				}

				lsight[rpos][cpos] = 1; //이 칸까지는 메두사의 시야에 닿는 곳이므로 1로 표시

				if (rpos == r) {
					for (int col = cpos - 1; col >= 0; col--) lsight[rpos][col] = 2; //같은 행에 있는 경우, 맵의 왼쪽 끝까지 가면서 이 행에만 2로 사각지대 표시
				}
				else if (rpos < r) { //메두사보다 위쪽 인 경우
					for (int col = cpos - 1; col >= 0; col--) {
						int lshadow = max(0, rpos - (cpos - col)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 아래쪽으로는 늘어나지 않음
						for (int row = lshadow; row <= rpos; row++) {
							lsight[row][col] = 2;
						}
					}
				}
				else {
					for (int col = cpos - 1; col >= 0; col--) { //메두사보다 아래쪽 인 경우
						int rshadow = min(N - 1, rpos + (cpos - col)); //메두사의 시야를 체크하던 방식과 같지만, 범위가 위쪽으로는 늘어나지 않음
						for (int row = rpos; row <= rshadow; row++) {
							lsight[row][col] = 2;
						}
					}
				}
			}
			else lsight[rpos][cpos] = 1; //기사가 없고 사각지대가 아니면 시야에 닿는 곳으로 표시
		}
	}
	return result;
}

int main() {
  //빠른 입출력을 위한 처리
	ios::sync_with_stdio(false);
	cin.tie(NULL);
  //맵의 크기, 기사 수, 메두사 집과 공원의 위치 입력
	cin >> N >> M >> sr >> sc >> er >> ec;

  //기사 정보 입력
	for (int i = 0; i < M; i++){
		cin >> knight[i].r >> knight[i].c;
		knight[i].idx = 1 + i;
	}
  //맵 정보 입력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> mmap[i][j];
		}
	}
  //메두사의 경로를 결정하기 위한 bfs
	mbfs();
  //만약 도착할 수 없다면 그냥 종료
	if (mvisit[sr][sc] == 0) {
		cout << -1;
		return 0;
	}
  //현재 위치 설정
	int rpos = sr, cpos = sc;
  
	while (1) { //메두사가 공원에 도착할 때까지 반복
    //기사위치 업데이트 맵을 싹 지우고 위치를 다시 표시
		fill(&kmap[0][0], &kmap[0][0] + 50 * 50, 0);
		for (int i = 0; i < M; i++) {
			if (knight[i].is_alive == 1) { //살아있는 기사만 표시
				knight[i].is_stun = 0; //모든 기사들이 돌에서 원래대로 돌아옴
				kmap[knight[i].r][knight[i].c] = 1;
			} 
		}

		int ans[3] = {0,0,0}; //(매턴마다 출력할 답을 저장하는 배열 기사가 움직인 칸, 돌이 된 기사 수, 메두사를 공격한 기사의 수)

		for (int dir = 0; dir < 4; dir++) { //4방향을 상하좌우 순으로 돌며 이동할 곳을 찾음
			int newr = rpos + dr[dir], newc = cpos + dc[dir];

			if (newr < 0 or newr >= N or newc < 0 or newc >= N) continue; //범위를 넘어가는 경우 넘어감
			if (mvisit[newr][newc] == 0) continue; //갈 수 없는 곳이라면 넘어감
			if (mvisit[newr][newc] < mvisit[rpos][cpos]) { //현재 위치보다 공원에 더 가깝다면, 이동
				rpos = newr, cpos = newc;
				break;
			}
		}
		if (rpos == er and cpos == ec) { //공원에 도착했으면 종료
			cout << 0;
			break;
		}
		for (int i = 0; i < M; i++) { //메두사가 이동한 위치에 기사가 있다면 사망
			if (knight[i].is_alive == 1 and knight[i].r == rpos and knight[i].c == cpos) {
				knight[i].is_alive = 0;
			}
		}

		fill(&is_stun[0][0], &is_stun[0][0] + 4 * 300, 0); //각 방향별로 기사가 돌이 되었는지를 저장하는 배열 초기화

		int result[4]; //각 방향별로 메두사가 쳐다봤을 때 돌이 되는 기사 수를 저장하는 배열

		result[0] = lookup(rpos, cpos);
		result[1] = lookdown(rpos, cpos);
		result[2] = lookleft(rpos, cpos);
		result[3] = lookright(rpos, cpos);

		int stone = -1; //돌이 된 기사의 수
		int dir; //돌을 최대로 많이 만드는 방향
		//상하좌우 순으로 봄
    for (int i = 0; i < 4; i++) {
			if (stone < result[i]) { //더 큰 경우에만 반영 -> 같으면 이 방향보다 우선 순위가 높은 방향이어야 함
				dir = i;
				stone = result[i];
			}
		}

		ans[1] = result[dir]; //돌로 만든 기사의 수 저장
    //각 방향에 맞게 메두사의 시야를 실제 시야 배열에 저장함
		if (dir == 0) {
			for (int i = 0; i < 50; i++) {
				memcpy(sight[i], usight[i], sizeof(int) * 50);
			}
		}
		else if (dir == 1) {
			for (int i = 0; i < 50; i++) {
				memcpy(sight[i], dsight[i], sizeof(int) * 50);
			}
		}
		else if (dir == 2) {
			for (int i = 0; i < 50; i++) {
				memcpy(sight[i], lsight[i], sizeof(int) * 50);
			}
		}
		else {
			for (int i = 0; i < 50; i++) {
				memcpy(sight[i], rsight[i], sizeof(int) * 50);
			}
		}

		for (int i = 0; i < M; i++) {
			if (is_stun[dir][i] == 1)knight[i].is_stun = 1;
		}

		kbfs(rpos, cpos); //기사가 메두사를 향해 움직이는 경로를 알기 위한 bfs

		for (int i = 0; i < M; i++) {
			if (knight[i].is_alive == 0 or knight[i].is_stun == 1) continue; //돌이 되었거나 죽은 경우 넘어감
			int moved = false; //움직임 여부
			int r = knight[i].r, c = knight[i].c;
			for (int k = 0; k < 4; k++) { //상하좌우 순으로 봄
				int newr = r + dr[k], newc = c + dc[k];
				if (newc < 0 or newc >= N or newr < 0 or newr >= N) continue; //범위를 넘어서면 넘어감
				if (kvisit[newr][newc] == 0) continue; //이동할 수 없는 곳 (= 메두사의 시선이 닿는 곳)이면 넘어감
				if (kvisit[newr][newc] < kvisit[r][c]) { //현재 위치보다 메두사에 더 가깝다면 이동
					knight[i].r = newr, knight[i].c = newc;
					moved = true; //이동했다고 표시
					if (newr == rpos and newc == cpos) { //이동한 곳이 메두사가 있는 곳이면 메두사를 공격하고 사망
						ans[2]++; //공격한 기사수 증가
						moved = false; //더 이동하지 않을 것이므로 false
						knight[i].is_alive = 0; // 기사 사망
					}
					
					ans[0]++; //기사가 움직인 칸 증가
					break;
				}
			}
			if (moved) { //이전에 움직였고, 메두사를 공격하지 않은 경우 한 번 더 움직임을 시도함
				r = knight[i].r, c = knight[i].c;
				for (int k = 2; k < 6; k++) { //좌우상하 순으로 봄
					int newr = r + dr[k%4], newc = c + dc[k%4]; 
					if (newc < 0 or newc >= N or newr < 0 or newr >= N) continue; //범위를 넘어서면 넘어감
					if (kvisit[newr][newc] == 0) continue; //이동할 수 없는 곳 (= 메두사의 시선이 닿는 곳)이면 넘어감
					if (kvisit[newr][newc] < kvisit[r][c]) { //현재 위치보다 메두사에 더 가깝다면 이동
						knight[i].r = newr, knight[i].c = newc;
						if (newr == rpos and newc == cpos) { //이동한 곳이 메두사가 있는 곳이면 메두사를 공격하고 사망
							ans[2]++; //공격한 기사수 증가
							knight[i].is_alive = 0; // 기사 사망
						}
						ans[0]++; //기사가 움직인 칸 증가
						break;
					}
				}
			}
		}
		cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n'; //결과 출력
	}

	return 0;
}
