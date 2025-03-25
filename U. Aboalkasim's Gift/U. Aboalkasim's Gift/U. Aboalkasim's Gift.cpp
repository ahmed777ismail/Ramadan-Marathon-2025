#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int inv12 = 83333334; // Modular inverse of 12 under MOD

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;
        if (n < 2) {
            cout << "0\n";
            continue;
        }
        long long n_sq = (n % MOD) * (n % MOD) % MOD;
        long long a = n_sq * (n_sq - 1 + MOD) % MOD;
        long long res = a * inv12 % MOD;
        cout << res << '\n';
    }

    return 0;
}