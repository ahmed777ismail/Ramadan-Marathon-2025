#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

typedef vector<vector<long long>> Matrix;

// Function to multiply two matrices under modulo
Matrix multiply(Matrix& A, Matrix& B, int size) {
    Matrix result(size, vector<long long>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return result;
}

// Function to exponentiate matrix
Matrix power(Matrix base, long long exp, int size) {
    Matrix result(size, vector<long long>(size, 0));
    for (int i = 0; i < size; ++i) result[i][i] = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiply(result, base, size);
        }
        base = multiply(base, base, size);
        exp /= 2;
    }
    return result;
}

// Function to count valid binary strings
long long countBinaryStrings(int n, int x, int y) {
    int size = (1 << x); // Number of states
    Matrix transition(size, vector<long long>(size, 0));

    // Building transition matrix
    for (int mask = 0; mask < size; ++mask) {
        for (int bit = 0; bit < 2; ++bit) {
            int newMask = ((mask << 1) | bit) & (size - 1);
            int ones = __builtin_popcount(newMask);
            if (ones <= y) {
                transition[newMask][mask] = 1;
            }
        }
    }

    // Initial state vector
    vector<long long> dp(size, 0);
    dp[0] = 1; // Start with an empty string

    // Compute result using matrix exponentiation
    Matrix result = power(transition, n, size);
    long long answer = 0;

    for (int i = 0; i < size; ++i) {
        answer = (answer + result[i][0]) % MOD;
    }

    return answer;
}

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    cout << countBinaryStrings(n, x, y) << endl;
    return 0;
}