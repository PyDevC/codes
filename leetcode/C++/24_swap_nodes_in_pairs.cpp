/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  ListNode *swapPairs(ListNode *head) {
    auto swapNodes = [](ListNode *a, ListNode *b) {
      if (a && b) {
        a->next = b->next;
        b->next = a;
        return true;
      }
      return false;
    };

    auto dummy = new ListNode(0);
    dummy->next = head;

    auto prev = dummy;
    while (prev->next && prev->next->next) {
      auto a = prev->next;
      auto b = a->next;
      swapNodes(a, b);
      prev->next = b;
      prev = a;
    }
    return dummy->next;
  }
};
