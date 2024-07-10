#include <iostream>
#include <vector>
#include <climits>

#define ALL(x) x.begin(), x.end()
#define FIRST(x) x.begin()
#define LAST(x) prev(x.end())

using namespace std;

using ll = long long;

bool is_prime(ll n){
  vector<bool> primes(n+1, true);

  for (ll num = 2; num * num <= n; ++num){
	if (primes[num]){
	  for (ll ix = num * num; ix <= n; ix += num){
		primes[ix] = false;
	  }
	}
  }

  return primes[n];
}

int main(){
  cout << (is_prime(30) ? "+" : "-") << '\n';
  cout << (is_prime(11) ? "+" : "-") << '\n';
  vector<bool> vec1;
  cout << (is_prime(1000000000) ? "+" : "-") << '\n';
//  cout << (is_prime(static_cast<ll>(vec1.max_size()) - 1) ? "+" : "-") << '\n';
}