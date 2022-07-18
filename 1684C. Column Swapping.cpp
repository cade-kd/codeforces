#include<bits/stdc++.h>
using namespace std;

bool isSorted(const vector<int>& a) {
  for (int i = 1; i < a.size(); i++) {
    if (a[i] < a[i - 1]) return false;
  }
  return true;
}

bool check(vector<vector<int>>& a, int x, int y) {
  bool res = true;
  for (int i = 0; i < int(a.size()) && res; i++) {
    swap(a[i][x], a[i][y]);
    if (!isSorted(a[i])) res = false;
    swap(a[i][x], a[i][y]);
  }

  return res;
}

void solve() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n, vector<int>(m));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }

  if (check(a, 0, 0)) {
    cout << "1 1\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    vector<int>& arr = a[i];
    for (int j = 0; j < m - 1; j++) {
      if (arr[j] > arr[j + 1]) {

        int x = 0, y = j + 1;
        for (int k = j; k > 0; k--) {
          if (arr[y] >= arr[k - 1]) {
            x = k;
            break;
          }
        }
        if (check(a, x, y)) {
          cout << x + 1 << " " << y + 1 << "\n";
          return;
        }

        x = j; y = m - 1;
        for (int k = m - 1; k > j; k--) {
          if (arr[k] < arr[k - 1] ||
            arr[x] >= arr[k - 1] && arr[k] <= arr[x + 1]) {
            y = k;
            break;
          }
        }

        if (check(a, x, y)) {
          cout << x + 1 << " " << y + 1 << "\n";
          return;
        }

        cout << "-1\n";
        return;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}