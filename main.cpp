#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Use 1-indexed array with padding (a[0] and a[n+1] = 1 for convenience)
    vector<long long> a(n + 2);
    a[0] = 1;
    a[n + 1] = 1;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // dp[i][j] represents the maximum value obtainable by burning all cards
    // in the interval [i, j], assuming cards i-1 and j+1 still exist
    vector<vector<long long>> dp(n + 2, vector<long long>(n + 2, 0));

    // Interval DP: try all interval lengths
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;

            // Try burning each card k in [i, j] as the LAST card to burn
            for (int k = i; k <= j; k++) {
                // When k is the last card to burn in [i, j]:
                // - All cards in [i, k-1] have been burned (value: dp[i][k-1])
                // - All cards in [k+1, j] have been burned (value: dp[k+1][j])
                // - Card k is now adjacent to cards i-1 and j+1
                // - Burning k gives: a[i-1] * a[k] * a[j+1]
                long long value = dp[i][k - 1] + dp[k + 1][j] + a[i - 1] * a[k] * a[j + 1];
                dp[i][j] = max(dp[i][j], value);
            }
        }
    }

    cout << dp[1][n] << endl;

    return 0;
}
