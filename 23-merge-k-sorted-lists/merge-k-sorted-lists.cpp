class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
                priority_queue<
            ListNode*,
            vector<ListNode*>,
            compare
        > pq;
        for (ListNode* node : lists) {
            if (node != nullptr) {
                pq.push(node);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        while (!pq.empty()) {
            ListNode* curr = pq.top();
            pq.pop();
            tail->next = curr;
            tail = curr;
            if (curr->next != nullptr) {
                pq.push(curr->next);
            }
        }

        return dummy->next;
    }

private:
    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };
};