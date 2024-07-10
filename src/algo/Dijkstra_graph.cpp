/**
 * Dijkstra's algorithm
 * Input: n (count of vertex), m (count of edges); matrix of adjust and weight edge u-v
 * Output: shortest paths between nodes in a weighted graph (indexes)
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
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

  ll n,m;
  cin >> n >> m;

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
  weight[0] = 0;

  vll prev(n, -1);

  // множество пар: [(вес вершины), вершина]
  set<pll> st;
  st.insert({weight[0], 0});

  while(!st.empty()){
	auto [wu, u] = *FIRST(st);
	st.erase(FIRST(st));
	if (weight[u] != wu){
	  continue;
	}
	for (auto [v, w]: G[u]){
	  if (weight[v] > weight[u] + w){
		weight[v] = weight[u] + w;
		st.insert({weight[v], v});
		prev[v] = u;
	  }
	}
  }

  if (weight[n-1] == inf){
	cout << -1 << '\n';
	return 0;
  }

  vll res;
  ll end = n - 1;
  while (end != -1){
	res.push_back(end);
	end = prev[end];
  }

  reverse(all(res));

  for(auto &elem: res){
	cout << elem + 1 << ' ';
  }

  return 0;
}