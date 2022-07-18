#include<bits/stdc++.h>
using namespace std;
template<typename T1, typename T2>
istream& operator>>(istream& ins,
    pair<T1, T2>& v) {
    ins >> v.first >> v.second;
    return ins;
}

template<typename T, size_t N>
istream& operator>>(istream& ins,
    array<T, N>& v) {
    for (int i = 0; i < int(N); i++) cin >> v[i];
    return ins;
}

template<typename T>
istream& operator>>(istream& ins,
    vector<T>& v) {
    for (int i = 0; i < int(v.size()); i++) ins >> v[i];
    return ins;
}

const int N = 200005;


void solve() {
    int n;
    cin >> n;

    vector<vector<int>> a(4, vector<int>(n));
    cin >> a;

    vector<int> cnt(4);
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            ans += cnt[j];
            if (a[j][i]) cnt[j]++;
        }

        for (int j = 0; j < 2; j++) {
            if (cnt[j] && cnt[j + 2]) {
                int x = min(cnt[j], cnt[j + 2]);
                cnt[j] -= x;
                cnt[j + 2] -= x;
            }
        }

        for (int j = 0; j < 2; j++) {
            int x = min(cnt[j], cnt[3 - j]);
            ans += x;
            cnt[j] -= x;
            cnt[3 - j] -= x;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (cnt[i]) {
            cout << -1 << endl;
            return;
        }
    }

    cout << ans << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}