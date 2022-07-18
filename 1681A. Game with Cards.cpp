#include<bits/stdc++.h>

using namespace std;

template<typename T, size_t N>
operator+(array<T, N>& a, array<T, N>& b) {
#if N == 2
  return { a[0] + b[0], a[1] + b[1] };
#else
  array<T, N> res;
  for (int i = 0; i < N; i++) {
    res[i] = a[i] + b[i];
  }
  return res;
#endif
}

template<size_t N>
class DJSeive {
protected:
  const int64_t PRECALUB;
  vector<int> primes;
  vector<int> vis;
#if N > 1
  vector<array<int64_t, N>> sumf;
  unordered_map<int64_t, array<int64_t, N>> w;
  vector<array<int64_t, N>> f;
  typedef array<int64_t, N> result_type;

  void test() {
    dskgk
  }

#else 
  vector<int64_t> sumf;
  unordered_map<int64_t, int64_t> w;
  vector<int64_t> f;
  typedef int64_t result_type;
#endif
public:
  DJSeive(int n) :
    PRECALUB(pow(n, 2.0 / 3)),
    f(PRECALUB + 1),
    sumf(PRECALUB + 1),
    vis(PRECALUB + 1) {
  }

  virtual void precal();
  inline virtual result_type gsum(int64_t l, int64_t r);
  inline virtual result_type hsum(int64_t n);

  // 杜教筛递归
  result_type fsum(int64_t x) {
    if (x <= PRECALUB) return sumf[x];
    if (w[x]) return w[x];
    result_type ans = hsum(x);
    for (int64_t l = 2, r;l <= x;l = r + 1) {
      r = x / (x / l);
      ans -= gsum(l, r) * fsum(x / l);
    }
    return w[x] = ans;
  }
};


class DJSeiveImpl : public DJSeive<2> {

public:
  DJSeiveImpl(int n) :DJSeive(n) {
  }

  // g的范围求和
  result_type gsum(int64_t l, int64_t r) {
    return { r - l + 1, r - l + 1 };
  }
  // h前置和
  result_type hsum(int64_t n) {
    return { 1, 1 };
  }

  void precal() {
    //mu phi
    f[0] = { 1, 1 };
    for (int i = 2;i <= PRECALUB;i++) {
      if (!vis[i]) {
        primes.push_back(i);
        f[i][0] = -1;
      }
      for (int p : primes) {
        if (p * i > PRECALUB) return;

        vis[i * p] = 1;
        if (i % p == 0) {
          f[i * p][1] = f[i][1] * p;
          //phi[i * p] = phi[i] * p;
          break;
        }
        else {
          //mu[i * p] = -mu[i];
          f[i * p][0] -= f[i][0];
          //phi[i * p] = phi[i] * (p - 1);
          f[i * p][1] = f[i][1] * (p - 1);
        }
      }
    }
    for (int i = 1;i <= PRECALUB;i++) {
      fsum[i] = fsum[i - 1] + f[i];
    }
  }

};


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif

  DJSeiveImpl seive(1 << 31);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    array<int64_t, 2> res = seive.fsum(n);
    printf("%lld %lld\n", res[1], res[0]);
  }
  return 0;
}
