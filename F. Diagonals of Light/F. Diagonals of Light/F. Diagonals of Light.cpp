#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        // Read the grid as strings
        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];  // each line is e.g. "010"
        }

        // Prepare diagonal markers
        // main diagonal index = (i - j) + offset
        // anti diagonal index = (i + j)
        // For an n×m grid:
        //   i ranges [0..n-1], j ranges [0..m-1]
        //   (i - j) can go from -(m-1) to (n-1).
        //   We'll use offset = (m - 1) so array index = i-j+(m-1) is always >= 0.
        //   max possible i-j+(m-1) = (n-1) - 0 + (m-1) = n + m - 2
        //   i + j can go up to (n-1)+(m-1) = n + m - 2
        // So size n+m is safe for both.
        vector<bool> mainDiagUsed(n + m, false);
        vector<bool> antiDiagUsed(n + m, false);

        // Mark diagonals from the originally lit cells
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    mainDiagUsed[i - j + (m - 1)] = true;
                    antiDiagUsed[i + j] = true;
                }
            }
        }

        // Build the output grid
        vector<string> result(n, string(m, '0'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mainDiagUsed[i - j + (m - 1)] || antiDiagUsed[i + j]) {
                    result[i][j] = '1';
                }
            }
        }

        // Print each row with NO spaces
        for (int i = 0; i < n; i++) {
            cout << result[i] << "\n";
        }
    }
    return 0;
}
