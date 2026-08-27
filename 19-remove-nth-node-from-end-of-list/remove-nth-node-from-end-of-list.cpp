class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Dummy node handles the case when we remove the head
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* slow = dummy;
        ListNode* fast = dummy;

        // Move fast n+1 steps ahead
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // Move both pointers until fast reaches the end
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        // Remove the nth node from the end
        ListNode* temp = slow->next;
        slow->next = slow->next->next;

        delete temp;

        return dummy->next;
    }
};