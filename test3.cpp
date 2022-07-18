#include <bits/stdc++.h>
using namespace std;

int n;

int query(string s) {
  cout << s << endl;
  cout.flush();
  int x; cin >> x;
  if (x == n) exit(0);
  return x;
}

int main() {
  int lims;
  cin >> n >> lims;

  //query true count
  string all_T(n, 'Y'), ans(n, '?');
  int cnt_T = query(all_T);

  //query TF
  string all_TF(n, 'Y');
  for (int i = 1; i < n; i += 2) all_TF[i] = 'N';
  int cnt_TF = query(all_TF);

  //begin the loop
  int l = 0, r = n - 1;
  while (r >= l) {
    if (r == l) { //only l is undetermined
      string s(all_T);
      s[l] = 'N';
      int k = query(s);

      if (k > cnt_T) {
        ans[l] = 'N';
      }
      else {
        ans[l] = 'Y';
      }
      l++; r--;
    }
    else {
      string s(all_T);
      s[l] = 'N'; s[l + 1] = 'N';
      int k = query(s) - cnt_T;

      if (k == 2) {
        ans[l] = 'N'; ans[l + 1] = 'N';
        l += 2;
      }
      else if (k == -2) {
        ans[l] = 'Y'; ans[l + 1] = 'Y';
        l += 2;
      }
      else {
        if (r == l + 1) { //only l and l+1 left; figure out the order
          string s(all_T);
          s[l] = 'N';
          int k = query(s);

          if (k > cnt_T) {
            ans[l] = 'N'; ans[l + 1] = 'Y';
          }
          else {
            ans[l] = 'Y'; ans[l + 1] = 'N';
          }
          l += 2;
        }
        else { //determine l, l+1, r
          string s(all_TF);
          s[l] = 'N'; s[l + 1] = 'Y';

          if (s[r] == 'N') s[r] = 'Y';
          else s[r] = 'N';

          int k = query(s) - cnt_TF;
          if (k == 3) {
            ans[l] = 'N'; ans[l + 1] = 'Y'; ans[r] = s[r];
          }
          else if (k == 1) {
            ans[l] = 'N'; ans[l + 1] = 'Y'; ans[r] = all_TF[r];
          }
          else if (k == -1) {
            ans[l] = 'Y'; ans[l + 1] = 'N'; ans[r] = s[r];
          }
          else {
            ans[l] = 'Y'; ans[l + 1] = 'N'; ans[r] = all_TF[r];
          }
          l += 2; r--;
        }
      }
    }
  }
  query(ans);
}