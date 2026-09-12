class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }
        sort(a.begin(), a.end());
        vector<long long> starts(n);
        for (int i = 0; i < n; i++) {
            starts[i] = a[i][0];
        }
        vector<vector<State>> dp(5, vector<State>(n + 1));
        auto better = [](const State& x, const State& y) {
            if (x.score != y.score)
                return x.score > y.score;
            return x.ids < y.ids;
        };

        for (int k = 1; k <= 4; k++) {

            for (int i = n - 1; i >= 0; i--) {
                State skip = dp[k][i + 1];
                int nxt = upper_bound(
                    starts.begin(),
                    starts.end(),
                    a[i][1]
                ) - starts.begin();

                State take = dp[k - 1][nxt];

                take.score += a[i][2];
                take.ids.push_back((int)a[i][3]);
                sort(take.ids.begin(), take.ids.end());

                dp[k][i] = better(take, skip) ? take : skip;
            }
        }

        return dp[4][0].ids;
    }
};