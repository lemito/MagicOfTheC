/**
 * DFS
 * Input: n (count of vertex), m (count of edges), st (start vertex)
 * Output: dfs path from st to st
 */
#include <algorithm>
#include <iostream>
#include <vector>

#define all(x) x.begin(), x.end()

using ll = long long;
using namespace std;
using vll = vector<ll>;
using graph = vector<vll>;

void dfs(ll u, ll prev,  graph& g, vll& path, ll &cnt) {
  if (path[u] != -1){
	return;
  }
  path[u] = cnt;
  ++cnt;
  for (auto v: g[u]){
	if (v == prev)
	  continue;
	dfs(v, u, g, path, cnt);
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

  vll path(n, -1);
  ll cnt = 0;

  dfs(st, st, G, path, cnt);

  for (auto &elem: path) {
	cout << elem << ' ';
  }

  return 0;
}