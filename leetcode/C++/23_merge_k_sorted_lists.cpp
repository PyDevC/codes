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
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.empty())
      return nullptr;
    auto it =
        std::min_element(lists.begin(), lists.end(), [](auto *a, auto *b) {
          if (a && b)
            return a->val > b->val;
          else
            return a ? true : false;
        });
    ListNode *head = *it;
    ListNode *temp = head;
    if ((*it) == nullptr || it == lists.end()) {
      return nullptr;
    }
    *it = (*it)->next;

    while (true) {
      auto min =
          std::min_element(lists.begin(), lists.end(), [](auto *a, auto *b) {
            if (a && b)
              return a->val > b->val;
            else
              return a ? true : false;
          });

      if (min == lists.end() || (*min) == nullptr) {
        break;
      }

      temp->next = *min;
      temp = temp->next;
      *min = (*min)->next;
    }
    return head;
  }
};
