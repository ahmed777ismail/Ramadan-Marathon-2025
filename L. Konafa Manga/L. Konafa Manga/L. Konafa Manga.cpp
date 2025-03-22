#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;
ll inv2 = (MOD + 1) / 2;

// Function to reverse an integer
ll reverseNum(ll x) {
    ll rev = 0;
    ll temp = x;
    while (temp > 0) {
        int digit = temp % 10;
        rev = rev * 10 + digit;
        temp /= 10;
    }
    return rev;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<ll> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }

        map<ll, ll> freq;
        for (int i = 0; i < N; i++) {
            ll rev_i = reverseNum(arr[i]);
            ll diff = arr[i] - rev_i;
            freq[diff]++;
        }

        ll total = 0;
        for (auto& pair : freq) {
            ll m = pair.second;
            if (m >= 2) {
                ll pairs = (m % MOD) * ((m - 1) % MOD) % MOD;
                pairs = (pairs * inv2) % MOD;
                total = (total + pairs) % MOD;
            }
        }

        cout << total << endl;
    }

    return 0;
}