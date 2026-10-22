
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        if (is_sorted(nums.begin(), nums.end())) {
            return 0;
        }

        int start = nums[0];

        // Check ascending cyclic rotation
        bool ascending = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (start + i) % n) {
                ascending = false;
                break;
            }
        }

        if (ascending) {
            return min(n - start, start + 2);
        }

        // Check descending cyclic rotation
        bool descending = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (start - i + n) % n) {
                descending = false;
                break;
            }
        }

        if (descending) {
            int k = (n - 1 - start + n) % n;
            return min(k, n - k) + 1;
        }

        return -1;
    }
};
