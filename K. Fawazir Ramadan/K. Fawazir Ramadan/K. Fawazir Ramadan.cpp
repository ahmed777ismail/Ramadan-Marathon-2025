#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long A, B;
        cin >> A >> B;
        // Ensure A is not greater than B.
        if (A > B) swap(A, B);

        long long ans = 0;
        // Check for every odd digit length.
        for (int d = 1; d <= 19; d += 2) {
            long long lo, hi;
            if (d == 1) {
                lo = 0;  // include 0 in one-digit numbers
                hi = 9;
            }
            else {
                lo = (long long)pow(10, d - 1);
                hi = (long long)pow(10, d) - 1;
            }
            // Find the intersection with [A, B]
            long long L = max(A, lo);
            long long R = min(B, hi);
            if (L <= R)
                ans += (R - L + 1);
        }
        cout << ans << "\n";
    }
    return 0;
}
