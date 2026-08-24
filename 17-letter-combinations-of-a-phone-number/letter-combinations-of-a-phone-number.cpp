class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;

        if (digits.empty())
            return ans;

        vector<string> phone = {
            "", "", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        string current;

        function<void(int)> backtrack = [&](int index) {
            // If we have processed all digits
            if (index == digits.size()) {
                ans.push_back(current);
                return;
            }

            // Get letters corresponding to current digit
            string letters = phone[digits[index] - '0'];

            for (char ch : letters) {
                current.push_back(ch);

                // Process next digit
                backtrack(index + 1);

                // Remove last character (backtracking)
                current.pop_back();
            }
        };

        backtrack(0);

        return ans;
    }
};