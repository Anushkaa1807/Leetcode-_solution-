class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        long long start = 1000; 

        for (int commas = 1; start <= n; commas++) {
            long long end;
            if (start > LLONG_MAX / 1000)
                end = LLONG_MAX;
            else
                end = start * 1000 - 1;

            long long cnt = min(n, end) - start + 1;
            if (cnt > 0)
                ans += cnt * commas;

            if (start > LLONG_MAX / 1000)
                break;
            start *= 1000;
        }

        return ans;
    }
};