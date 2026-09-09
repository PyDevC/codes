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
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    // distance between these should be n
    ListNode *left{head}, *right{head};
    auto *prev{left};
    int idx{};
    ListNode *temp = head;
    while (temp) {
      if (idx == n) {
        prev = left;
        left = left->next;
        right = right->next;
      } else {
        right = right->next;
        idx++;
      }
      temp = temp->next;
    }

    // left == node we have to delete
    if (left == head) {
      head = head->next;
      delete left;
    } else {
      prev->next = left->next; // broken the connection
      delete left;
    }

    return head;
  }
};
