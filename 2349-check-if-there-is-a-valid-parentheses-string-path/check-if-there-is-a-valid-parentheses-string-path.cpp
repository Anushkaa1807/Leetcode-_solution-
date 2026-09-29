class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if ((m + n - 1) % 2 != 0)
            return false;

        int maxBalance = m + n;

        vector<vector<bool>> dp(n, vector<bool>(maxBalance + 1, false));
        if (grid[0][0] == ')')
            return false;

        dp[0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                vector<bool> current(maxBalance + 1, false);

                for (int balance = 0; balance <= maxBalance; balance++) {
                    if (i > 0 && dp[j][balance]) {
                        int newBalance = balance +
                            (grid[i][j] == '(' ? 1 : -1);

                        if (newBalance >= 0)
                            current[newBalance] = true;
                    }
                    if (j > 0 && dp[j - 1][balance]) {
                        int newBalance = balance +
                            (grid[i][j] == '(' ? 1 : -1);

                        if (newBalance >= 0)
                            current[newBalance] = true;
                    }
                }
                dp[j] = current;
            }
        }
        return dp[n - 1][0];
    }
};