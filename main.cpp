#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using Adj = vector<vii>;

constexpr auto inf = int{ 987'654'321 };

int n, m, x;
Adj adj;
int ans;

int dijk(int beg, int end) {
	auto dist = vi(n + 1, inf);
	dist[beg] = 0;

	auto q = priority_queue<pii, vii, greater<pii>>{};
	q.push({ 0, beg });

	while (!q.empty()) {
		const auto& [_, a] = pii{ q.top() };
		q.pop();

		if (end == a) {
			break;
		}

		for (const auto& [b, c] : adj[a]) {
			const auto& newDist = dist[a] + c;
			if (newDist < dist[b]) {
				dist[b] = newDist;
				q.push({ dist[b], b });
			}
		}
	}

	return dist[end];
}

void solve() {
	ans = 0;

	for (auto i = 1; i <= n; ++i) {
		const auto& d1 = dijk(i, x);
		const auto& d2 = dijk(x, i);
		const auto& d = d1 + d2;
		
		ans = max(ans, d);
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m >> x;
	adj = Adj(n + 1, vii{});
	for (auto i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({ b, c });
	}

	solve();
	cout << ans;

	return 0;
}