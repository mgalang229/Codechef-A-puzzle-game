#include <bits/stdc++.h>

using namespace std;

map<int, int> my_list;
queue<int> q;
int b[9];
int is_prime[] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1};

void Compute(int x, int y, int cur, int distance) {
	int first = (cur / b[x]) % 10;
	int second = (cur / b[y]) % 10;
	if (!is_prime[first + second]) {
		return;
	}
	cur += (second - first) * b[x] + (first - second) * b[y];
	if (my_list.find(cur) == my_list.end()) {
		my_list[cur] = distance + 1;
		q.push(cur);
	}
}

void Preprocess() {
	b[8] = 1;
	for (int i = 7; i >= 0; i--) {
		b[i] = b[i + 1] * 10;
	}
	int puzzle = 123456789;
	my_list[puzzle] = 0;
	q.push(puzzle);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		int prev_dist = my_list[cur];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i < 2) { 	
					Compute(3 * i + j, 3 * (i + 1) + j, cur, prev_dist);
				}
				if (j < 2) {
					Compute(3 * i + j, 3 * i + 1 + j, cur, prev_dist);
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	Preprocess();
	cin >> tt;
	while (tt--) {
		int puzzle = 0;
		// watch the video in the link in this repository
		for (int i = 0; i < 9; i++) {
			int x;
			cin >> x;
			puzzle = (puzzle * 10) + x;
		}
		if (my_list.find(puzzle) == my_list.end()) {
			cout << -1;
		} else {
			cout << my_list[puzzle];
		}
		cout << '\n';
	}
	return 0;
}
