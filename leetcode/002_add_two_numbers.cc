/* 002_add_two_numbers.cc
 *
 * leetcode problem 002:
 * You are given two linked lists representing two non-negative numbers. The 
 * digits are stored in reverse order and each of their nodes contain a single
 * digit. Add the two numbers and return it as a linked list.

 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 *
 * History: 
 *  03/29/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"
typedef unordered_map<int, int> NumHash;                
typedef vector<int> IntVector;

// The singly-linked list definition used in leetcode online judge
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};

ListNode* add_two_numbers(ListNode* l1, ListNode* l2) {
    ListNode* added_list_cur = NULL;    // Cursor pointer for adding nodes
    ListNode* added_list_head = NULL;   // Save head of list 
    int carry_digit = 0;

    // Assign cursor pointers of l1 and l2
    ListNode* l1_cur = l1;      
    ListNode* l2_cur = l2;
    
    while (l1_cur && l2_cur) {  // Exit if any one of two nums ends
        int sum = l1_cur->val + l2_cur->val + carry_digit;
        int digit = sum % 10;
        carry_digit = sum / 10;
         
        ListNode* new_node = new ListNode(digit);
        if (!added_list_head) {  // First node: save head
            added_list_head = new_node;
            added_list_cur = new_node;
        } else {  // Not first node: insert to the list
            added_list_cur->next = new_node;
            added_list_cur = added_list_cur->next;
        }        
        // Move all pointers to next digit
        l1_cur = l1_cur->next;
        l2_cur = l2_cur->next;
    }
    
    // Pick the left number list
    ListNode* l_left_cur = ((l1_cur != NULL) ? l1_cur : l2_cur);
    while (l_left_cur) {    // If more digits in l1
        int sum = carry_digit + l_left_cur->val;
        int digit = sum % 10;
        carry_digit = sum / 10;

        ListNode* new_node = new ListNode(digit);
        // Still can be first node if one input is empty
        if (!added_list_head) { 
            added_list_head = new_node;
            added_list_cur = new_node;
        } else {
            added_list_cur->next = new_node;
            added_list_cur = added_list_cur->next;
        }
        // Move to next
        l_left_cur = l_left_cur->next;
    }
    
    if (carry_digit) {  // Add carry digit as last node if it exists
        added_list_cur->next = new ListNode(carry_digit);
    }
    return added_list_head; 
}

int main(int argc, char *argv[]) {
    // Test: Initialize two number lists 
    vector<int> l1_val = {2};
    vector<int> l2_val = {8, 9, 9};
    
    ListNode* l1 = new ListNode(l1_val[0]);
    ListNode* l2 = new ListNode(l2_val[0]);
    ListNode* l1_head = l1; 
    ListNode* l2_head = l2;
    
    for (size_t i = 1; i < l1_val.size(); i++) {
        l1->next = new ListNode(l1_val[i]);
        l1 = l1->next;
    }
    
    for (size_t i = 1; i < l2_val.size(); i++) {
        l2->next = new ListNode(l2_val[i]);
        l2 = l2->next;
    }
    ListNode* rslt = add_two_numbers(l1_head, l2_head);
   
    // Verify results and clear space
    while (rslt) {
        ListNode* p = rslt;
        cout << p->val << endl;
        rslt = p->next;
        delete p;
    }
    clear_list(l1_head);
    clear_list(l2_head);
    return 0;
}

