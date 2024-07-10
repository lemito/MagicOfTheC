/**
 * Bellman–Ford algorithm
 * Input: n (count of vertex), m (count of edges), st (start vertex); matrix of adjust and weight edge u-v
 * Output: shortest paths from a single source vertex to all of the other vertices
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <array>

#define all(x) x.begin(), x.end()
#define FIRST(x) x.begin()

using ll = long long;
using namespace std;
using vll = vector<ll>;
using graph = vector<vll>;
using pll = array<ll, 2>;

const ll inf = LLONG_MAX;

// ребро
typedef struct edge_ {
  ll u = 0;
  ll v = 10;
  ll w = 0;

  friend ostream& operator<<(ostream& stream, const edge_ &elem){
	stream << elem.u << ' ' << elem.v << ' ' << elem.w;
	return stream;
  }

  friend istream& operator>>(istream& stream, edge_ &elem){
	stream >> elem.u >> elem.v >> elem.w;
	return stream;
  }
} edge;

using w_graph = vector<vector<pll>>;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n,m,start;
  cin >> n >> m >> start;
  start -= 1;

  //
  w_graph G(n);

  for (ll j = 0; j < m; ++j){
	ll u, v, w;
	cin >> u >> v >> w;
	u -= 1;
	v -= 1;
	//// орграф с длинами
	G[u].push_back({v, w});;
	/////////////
  }

  // вектор: n вершины: её вес (длина от 0 до неё)
  vll weight(n, inf);
  weight[start] = 0;

  vector<bool> visited(n, false);
  visited[start] = true;

  for (ll i = 1; i<=n; ++i){
	bool flag_i = false;
	for (ll u = 0; u < n; ++u){
	  if (!visited[u]) {
		continue;
	  }
	  for (auto [v, w]: G[u]){
		if (weight[v] > weight[u] + w){
		  visited[v] = true;
		  weight[v] = weight[u] + w;
		  flag_i = true;
		}
	  }
	}
	if (i == n && flag_i){
	  cout << "Negative cycle" << '\n';
	  return 0;
	}
  }


  for(auto &elem: weight){
	if (elem > inf / 10) {
	  cout << "inf" << ' ';
	}
	else {
	  cout << elem << ' ';
	}
  }

  return 0;
}