#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

// Fast exponentiation: computes base^exp % MOD in O(log exp)
long long modPow(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;  // number of test cases

    while (T--) {
        long long L, R;
        cin >> L >> R;
        // f(N) = 2^(N-1), so sum_{n=L..R} f(n) = sum_{n=L..R} 2^(n-1)
        // = 2^(R) - 2^(L-1), all mod 1e9+7

        long long pR = modPow(2, R);       // 2^R
        long long pLm1 = modPow(2, L - 1); // 2^(L-1)

        long long ans = pR - pLm1;
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }
    return 0;
}
