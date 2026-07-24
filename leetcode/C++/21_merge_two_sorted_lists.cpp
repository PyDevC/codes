#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int val) : val(val), next(nullptr) {}
  void print() {
    auto temp = this;
    while (temp) {
      std::cout << temp->val << ", ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }
};

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
class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    ListNode dummy(0);
    auto curr = &dummy;
    while (list1 && list2) {
      if (list1->val <= list2->val) {
        curr->next = list1;
        list1 = list1->next;
      } else {
        curr->next = list2;
        list2 = list2->next;
      }
      curr = curr->next;
    }
    curr->next = list1 ? list1 : list2;
    return dummy.next;
  }
};

int main() {
  ListNode *list1 = new ListNode(0);
  list1->next = new ListNode(2);
  list1->next->next = new ListNode(4);
  list1->next->next->next = new ListNode(6);

  ListNode *list2 = new ListNode(1);
  list1->next = new ListNode(3);
  list1->next->next = new ListNode(5);
  list1->next->next->next = new ListNode(6);
  list1->next->next->next->next = new ListNode(8);

  Solution sol;
  auto mergedList = sol.mergeTwoLists(list1, list2);
  mergedList->print();
  return 0;
}
