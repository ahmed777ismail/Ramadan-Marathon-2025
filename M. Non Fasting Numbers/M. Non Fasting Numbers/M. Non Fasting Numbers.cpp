#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        unordered_map<int, int> freq;
        for (int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            ++freq[a];
        }
        ll product = 1;
        ll num_distinct = freq.size();
        for (const auto& p : freq) {
            product = (product * (p.second + 1)) % MOD;
        }
        ll ans = (product - 1 - num_distinct) % MOD;
        if (ans < 0) ans += MOD;
        cout << ans << '\n';
    }
    return 0;
}