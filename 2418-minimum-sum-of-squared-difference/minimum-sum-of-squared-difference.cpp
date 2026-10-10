
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = 1LL * k1 + k2;
        vector<int> diff;
        long long total = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            total += d;
        }

        if (total <= k) return 0;

        sort(diff.begin(), diff.end(), greater<int>());

        int low = 0, high = diff[0];

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long operations = 0;

            for (int d : diff) {
                if (d > mid) {
                    operations += d - mid;
                }
            }

            if (operations <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long ans = 0;
        long long used = 0;

        for (int d : diff) {
            int reduced = min(d, level);
            ans += 1LL * reduced * reduced;

            if (d > level) {
                used += d - level;
            }
        }

        long long remaining = k - used;

        // Reduce 'remaining' differences from level to level - 1.
        for (int d : diff) {
            if (remaining == 0) break;

            if (d >= level && level > 0) {
                ans -= 2LL * level - 1;
                remaining--;
            }
        }

        return ans;
    }
};
