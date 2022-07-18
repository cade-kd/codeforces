#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <limits>
using namespace std;
const int N = 200005, SQ = sqrt(N);
void maintain(int* arr, int pos, int& minval) {
  minval = numeric_limits<int>::max();
  for (int i = pos * SQ; i < (pos + 1) * SQ; i++) {
    minval = min(minval, arr[i]);
  }
}
int getmin(int* arr, int* amin, int left, int right) {
  int minval = arr[left];
  for (; left <= right && left % SQ; left++) {
    minval = min(minval, arr[left]);
  }
  if (minval == 0) return minval;
  int x = left / SQ;
  while (right - left + 1 >= SQ) {
    minval = min(minval, amin[x++]);
    left += SQ;
  }
  if (minval == 0) return minval;
  for (; left <= right; left++) {
    minval = min(minval, arr[left]);
  }
  return minval;
}


int row[N], col[N], rmin[SQ], cmin[SQ];
void solve() {
  int n, q, t;
  cin >> n >> q;
  memset(row, 0, sizeof(row));
  memset(col, 0, sizeof(col));
  memset(rmin, 0, sizeof(rmin));
  memset(cmin, 0, sizeof(cmin));
  while (q--) {
    cin >> t;
    int x, y, x2, y2;
    if (t == 1) {
      cin >> x >> y;
      x--; y--;
      row[x]++;
      col[y]++;
    }
    else if (t == 2) {
      cin >> x >> y;
      x--; y--;
      row[x]--;
      col[y]--;
    }
    else {
      cin >> x >> y >> x2 >> y2;
      x--; y--; x2--; y2--;
      if (getmin(row, rmin, x, x2) || getmin(col, cmin, y, y2)) {
        cout << "Yes\n";
      }
      else {
        cout << "No\n";
      }
    }
    if (t < 3) {
      maintain(row, x / SQ, rmin[x / SQ]);
      maintain(col, y / SQ, cmin[y / SQ]);
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

}