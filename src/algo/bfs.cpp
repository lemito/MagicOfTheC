/**
 * BFS
 * Input: n (count of vertex), m (count of edges), st (start vertex); matrix of adjust
 * Output: length from st to all another vertexes
 */
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#define all(x) x.begin(), x.end()

using ll = long long;
using namespace std;
using vll = vector<ll>;
using graph = vector<vll>;
using pll = pair<ll, ll>;

const ll inf = LLONG_MAX;

void bfs(queue<pll> &q, vll &path, const graph& G){
  while(!q.empty()){
	auto [u, w] = q.front();
	q.pop();
	if (path[u] != w)
	  continue;
	for (auto &v: G[u]){
	  if (path[v] > w+1){
		path[v] = w+1;
		q.emplace(v, path[v]);
	  }
	}
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n,m,st;
  cin >> n >> m >> st;
  st -= 1;
  graph G(n);

  for (ll j = 0; j < m; ++j){
	ll u, v;
	cin >> u >> v;
	u -= 1;
	v -= 1;
	//// Неорграф
	G[u].push_back(v);
	G[v].push_back(u);
	/////////////
  }

  // веса вершин (уровень)
  vll path(n, inf);
  path[st] = 0;
  // q = [точка, её вес(уровень)]
  queue<pll> q;
  q.emplace(st, 0);

  bfs(q, path, G);

  for (auto &elem: path) {
	if (elem == inf){
	  cout << -1 << ' ';
	}
	else {
	  cout << elem << ' ';
	}
  }
  return 0;
}