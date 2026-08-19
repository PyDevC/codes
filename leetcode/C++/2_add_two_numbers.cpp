#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode listHead(0);
        ListNode* iterator = &listHead;
        int carry{};
        while(l1 || l2 || carry != 0) {
            int sum = carry;
            if(l1) { sum += l1->val; l1 = l1->next;}
            if(l2) { sum += l2->val; l2 = l2->next;}
            
            carry = sum / 10;
            sum = sum % 10;
            iterator->next = new ListNode(sum);
            iterator = iterator->next;
        }

        return listHead.next;
    }
};

int main() {
  Solution sol;
  ListNode *node1_1 = new ListNode(2);
  ListNode *node1_2 = new ListNode(4, node1_1);
  ListNode *node1_3 = new ListNode(3, node1_2);

  ListNode *node2_1 = new ListNode(5);
  ListNode *node2_2 = new ListNode(6, node2_1);
  ListNode *node2_3 = new ListNode(4, node2_2);

  auto answer = sol.addTwoNumbers(node1_1, node2_1);
  auto temp = answer;
  while (temp) {
    std::cout << temp->val << " ";
    temp = temp->next;
  }
  std::cout << std::endl;
  return 0;
}
