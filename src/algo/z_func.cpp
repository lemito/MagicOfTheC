/**
 * Z-function and Knuth–Morris–Pratt algorithm
 * Input: T - string in which the substring is searched for; s - searched substring (pattern)
 * Output: whether the substring occurs in the string (yes/no) and the number of occurrences
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <array>

#define all(x) x.begin(), x.end()
#define FIRST(x) x.begin()
#define LAST(x) prev(x.end())

using ll = long long;
using namespace std;
using vll = vector<ll>;
using graph = vector<vll>;
using pll = array<ll, 2>;

const ll inf = LLONG_MAX;

void zzz(const string& s, vll& res){
  ll l = 0, r = 0;
  ll n = (ll)s.size();
  res[0] = n;
  for (ll i = 1; i < n; ++i){
	// указатель не дошел до правой границы z-блока
	if (i < r){
	  res[i] = min(r-i+1, res[i-l]);
	}

	// пока не вышли за z-блок и поиск подходящего префикса
	while(i + res[i] < n && s[res[i]] == s[i + res[i]]){
	  ++res[i];
	}

	// подтягиваем границы, если перешли за правый край
	if(i + res[i]  > r){
	  r = i + res[i] - 1;
	  l = i;
	}
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string T, s;
  cin >> T >> s;
  string concat = s + '$' + T;
  ll n = (ll)concat.size();
  ll s_size = (ll)s.size();
  ll T_size = (ll)T.size();
  vll res(n, 0);
  zzz(concat, res);

  ll pre_res = 0;
  for (ll i = s_size + 1; i < T_size + s_size + 1; ++i){
	if (res[i] == s_size){
	  pre_res++;
	}
  }

  if(pre_res == 0){
	cout << "NO" << '\n';
  }
  else {
	cout << "YES" << '\n' << pre_res << '\n';
  }

  cout << '\n';
  return 0;
}