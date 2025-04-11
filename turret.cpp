#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M, K;
int broken = 0; //파괴된 포탑의 수

int map[10][10]; //각 포탑의 인덱스를 저장하기 위한 배열

int visit[10][10]; //공격 대상 포탑으로부터 각 셀의 거리를 저장하는 배열

int INF = 1e9;

//우하좌상 순으로 움직이는 방향 배열
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

//8방향으로 이동하기 위한 방향배열
int ddr[8] = { -1,-1,-1,0,0,1,1,1 };
int ddc[8] = { -1,0,1,-1,1,-1,0,1 };

//포탑의 정보를 저장하는 구조체
struct Turret {
	//포탑의 좌표
  int r;
	int c;
	int att; //포탑의 공격력
	int is_damaged; //해당 턴에 공격을 하거나 받았는지 여부
	int attime; //포탑이 마지막으로 공격한 시점
};

struct attcmp { //공격자를 결정할 때 사용하는 비교 구조체
	bool operator()(const Turret* a, const Turret* b) {
		if (a->att != b->att) return a->att > b->att; //공격력이 다르면 이를 가지고 비교 낮은 쪽이 pq에서 우위
		if (a->attime != b->attime) return a->attime < b->attime; //마지막으로 공격한 시간이 다르면 이를 가지고 비교 최근일수록 pq에서 우위
		if ((a->r + a->c) != (b->r + b->c)) return (a->r + a->c) < (b->r + b->c); //열과 행의 합이 다르면 이를 가지고 비교 큰 쪽이 pq에서 우위
		else return a->c < b->c; //열의 대소관계를 가지고 비교 큰 쪽이 pq에서 우위
	}
};

struct demcmp { //공격 대상을 결정할 때 사용하는 비교 구조체
	bool operator()(const Turret* a, const Turret* b) {
		if (a->att != b->att) return a->att < b->att; //공격력이 다르면 이를 가지고 비교 높은 쪽이 pq에서 우위
		if (a->attime != b->attime) return a->attime > b->attime; //마지막으로 공격한 시간이 다르면 이를 가지고 비교 오래 되었을수록 pq에서 우위
		if ((a->r + a->c) != (b->r + b->c)) return (a->r + a->c) > (b->r + b->c); //열과 행의 합이 다르면 이를 가지고 비교 작은 쪽이 pq에서 우위
		else return a->c > b->c; //열의 대소관계를 가지고 비교 작은은 쪽이 pq에서 우위
	}
};

Turret* turret[100]; //터렛의 포인터를 저장하는 배열

int main() {

	cin >> N >> M >> K;
	int att, idx = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> att;
			turret[i * M + j] = new Turret{i, j, att, 0, 0 }; //새 포탑탑 할당
			map[i][j] = idx++; //맵에 인덱스 저장
			if (att == 0) broken++; //이미 부서진 포탑 확인
		}
	}


	
	for (int k = 1; k <= K; k++) {
		fill(&visit[0][0], &visit[0][0] + 100, -1); //방문배열 초기화
    //  공격자 선정
		priority_queue<Turret*, vector<Turret*>, attcmp> q; //pq를 이용해 비교
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (turret[map[i][j]]->att == 0) continue; //공격력이 0인 경우 넘어감
				q.push(turret[map[i][j]]); //아니면 pq에 삽입
			}
		}

		auto attacker = q.top(); //가장 위에 있는 것이 공격자
		attacker->is_damaged = 1; //공격에 관여했음을 표시
		attacker->attime = k; //공격 시점 갱신
		attacker->att += (N + M); //공격자의 공격력 보정
		int atk = attacker->att;
		//공격자의 공격
		//대상 선정
		priority_queue<Turret*, vector<Turret*>, demcmp> q2; //pq를 이용해 비교
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (turret[map[i][j]]->att == 0) visit[i][j] = INF; //공격력이 0인 경우 레이저가 지나갈 수 없게 거리를 무한대로 설정
				else if (i == attacker->r and j == attacker->c) continue; //공격자는 제외
				else q2.push(turret[map[i][j]]); //pq에 삽입
			}
		}

		auto demager = q2.top(); //가장 위에 있는 것이 공격 대상상


		//레이저 공격
		int sr = attacker->r, sc = attacker->c, er = demager->r, ec = demager->c; //공격자와 공격대상의 좌표

		queue<pair<int, int>> qq; //공격대상으로부터 공격자까지의 거리를 구하는 bfs를 위한 q
		qq.push({ er, ec });
		visit[er][ec] = 1;


		while (!qq.empty()) {
			auto cur = qq.front();
			qq.pop();

			int r = cur.first, c = cur.second;

			for (int i = 0; i < 4; i++) {
				int newr = (r + dr[i] + N) % N, newc = (c + dc[i] + M) % M; //칸을 넘어가면 반대쪽으로 순회하도록 %연산 활용, 음수가 되지 않도록 N, M을 더함

				if (visit[newr][newc] != -1) continue; //이미 계산된 곳이면 넘어감
				qq.push({ newr, newc }); //q에 삽입입
				visit[newr][newc] = visit[r][c] + 1; //현재 칸에서 거리 한 칸 추가
			}
		}
		//레이저가 도달할 수 있는 경우 -> 레이저 공격
		if (visit[sr][sc] != -1) {
			queue<pair<int, int>> qq2; //공격자부터 공격대상까지 가는 경로를 찾기 위한 q
			qq2.push({ sr, sc });

			while (!qq2.empty()) {
				auto cur = qq2.front();
				qq2.pop();

				int r = cur.first, c = cur.second;

				for (int i = 0; i < 4; i++) {
					int newr = (r + dr[i] + N) % N, newc = (c + dc[i] + M) % M; //칸을 넘어가면 반대쪽으로 순회하도록 %연산 활용, 음수가 되지 않도록 N, M을 더함

					if (visit[newr][newc] < visit[r][c]) { //현재 칸보다 공격 대상에 가까운 곳이면 레이저가 이동함
						turret[newr * M + newc]->is_damaged = 1; //공격당했음을 표시
						if (newr == demager->r and newc == demager->c) { //공격대상이라면 공격력만큼의 데미지를 주고 끝냄
							turret[map[newr][newc]]->att = max(0, turret[map[newr][newc]]->att - atk);
						}
						else { //공격 대상이 아니라면 공격력의 절반의 데미지를 주고 q에 추가
							qq2.push({ newr, newc });
							turret[map[newr][newc]]->att = max(0, turret[map[newr][newc]]->att - atk / 2);
						}
						if (turret[map[newr][newc]]->att == 0) broken++; //공격으력
		atk = max(turret[i]->att, atk);
	}
	cout << atk;

	return 0;
}
