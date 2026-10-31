
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // memo[i][j][dir]
        // dir = 0 means entered while moving right
        // dir = 1 means entered while moving down
        vector<vector<array<int, 2>>> memo(
            m, vector<array<int, 2>>(n, {-2, -2})
        );

        // Returns the flattened index of the first empty cell.
        // Returns -1 if the path goes outside the grid.
        function<int(int, int, int)> resolve =
            [&](int i, int j, int dir) -> int {

            if (i >= m || j >= n) {
                return -1;
            }

            if (memo[i][j][dir] != -2) {
                return memo[i][j][dir];
            }

            // Empty cell: reflection stops.
            if (grid[i][j] == 0) {
                return memo[i][j][dir] = i * n + j;
            }

            // Mirror: change direction and move one cell.
            if (dir == 0) {
                return memo[i][j][dir] =
                    resolve(i + 1, j, 1);
            }
            else {
                return memo[i][j][dir] =
                    resolve(i, j + 1, 0);
            }
        };

        vector<vector<long long>> dp(m, vector<long long>(n, 0));

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0) continue;

                if (i == m - 1 && j == n - 1) {
                    continue;
                }

                long long ways = dp[i][j];

                // Try moving right.
                int right = resolve(i, j + 1, 0);

                if (right != -1) {
                    int x = right / n;
                    int y = right % n;

                    dp[x][y] = (dp[x][y] + ways) % MOD;
                }

                // Try moving down.
                int down = resolve(i + 1, j, 1);

                if (down != -1) {
                    int x = down / n;
                    int y = down % n;

                    dp[x][y] = (dp[x][y] + ways) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
