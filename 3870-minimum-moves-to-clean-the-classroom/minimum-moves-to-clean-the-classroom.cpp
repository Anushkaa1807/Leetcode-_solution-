class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        int litterCount = 0;

        vector<vector<int>> litterId(m, vector<int>(n, -1));

        // Find starting position and assign IDs to litter
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litterId[i][j] = litterCount++;
                }
            }
        }

        int fullMask = (1 << litterCount) - 1;

        if (fullMask == 0)
            return 0;

        // best[r][c][mask] = maximum energy seen for this state
        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(
                n,
                vector<int>(1 << litterCount, -1)
            )
        );

        // {row, column, collectedMask, remainingEnergy}
        queue<array<int, 4>> q;

        q.push({sr, sc, 0, energy});
        best[sr][sc][0] = energy;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                auto [r, c, mask, currEnergy] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                // No energy means we cannot move
                if (currEnergy == 0)
                    continue;

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    // Check boundaries
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Cannot enter obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        int id = litterId[nr][nc];
                        newMask |= (1 << id);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    // Skip if we have already reached this state
                    // with equal or more energy
                    if (best[nr][nc][newMask] >= newEnergy)
                        continue;

                    best[nr][nc][newMask] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};