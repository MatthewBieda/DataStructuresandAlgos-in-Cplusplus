#include <iostream>
#include <unordered_set>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for a singly linked list node
class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};

// Definition for a doubly linked list node with a child pointer
class DoublyListNode {
public:
    int val;
    DoublyListNode* next;
    DoublyListNode* child;

    DoublyListNode(int x) : val(x), next(nullptr), child(nullptr) {}
};

// 1. Reverse a Linked List (Iterative)
ListNode* reverseListIterative(ListNode* head) {
    ListNode* prev = nullptr;
    while (head != nullptr) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

// 2. Reverse a Linked List (Recursive)
ListNode* reverseListRecursive(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

// 3. Detect Cycle in a Linked List
bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) {
        if (slow == fast) return true;
        slow = slow->next;
        fast = fast->next->next;
    }
    return false;
}

// 4. Find Middle of a Linked List
ListNode* findMiddle(ListNode* head) {
    if (!head) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 5. Merge Two Sorted Linked Lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    if (l1) current->next = l1;
    if (l2) current->next = l2;
    return dummy.next;
}

// 6. Remove N-th Node from End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* first = &dummy;
    ListNode* second = &dummy;
    for (int i = 0; i <= n; ++i) {
        first = first->next;
    }
    while (first != nullptr) {
        first = first->next;
        second = second->next;
    }
    second->next = second->next->next;
    return dummy.next;
}

// 7. Check if Linked List is Palindrome
bool isPalindrome(ListNode* head) {
    if (!head) return true;
    ListNode* slow = head;
    ListNode* fast = head;
    stack<int> s;
    while (fast && fast->next) {
        s.push(slow->val);
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast) slow = slow->next;  // Odd number of nodes
    while (slow) {
        if (s.top() != slow->val) return false;
        s.pop();
        slow = slow->next;
    }
    return true;
}

// 8. Intersection of Two Linked Lists
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    ListNode* a = headA;
    ListNode* b = headB;
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

// 9. Copy List with Random Pointer
class RandomNode {
public:
    int val;
    RandomNode* next;
    RandomNode* random;

    RandomNode(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

RandomNode* copyRandomList(RandomNode* head) {
    if (!head) return nullptr;

    // Step 1: Clone nodes
    RandomNode* iter = head;
    while (iter) {
        RandomNode* newNode = new RandomNode(iter->val);
        newNode->next = iter->next;
        iter->next = newNode;
        iter = newNode->next;
    }

    // Step 2: Assign random pointers
    iter = head;
    while (iter) {
        if (iter->random) {
            iter->next->random = iter->random->next;
        }
        iter = iter->next->next;
    }

    // Step 3: Separate the lists
    RandomNode* newHead = head->next;
    RandomNode* copy = newHead;
    iter = head;
    while (iter) {
        iter->next = iter->next->next;
        if (copy->next) copy->next = copy->next->next;
        iter = iter->next;
        copy = copy->next;
    }

    return newHead;
}

// 10. Rotate Linked List by K places
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k == 0) return head;

    // Step 1: Compute the length of the list
    ListNode* oldTail = head;
    int length = 1;
    while (oldTail->next) {
        oldTail = oldTail->next;
        ++length;
    }

    // Step 2: Make it a circular list
    oldTail->next = head;

    // Step 3: Find the new head and tail
    k = k % length;
    ListNode* newTail = head;
    for (int i = 0; i < length - k - 1; ++i) {
        newTail = newTail->next;
    }
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;

    return newHead;
}

// 11. Reverse Nodes in k-Group
ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || k == 1) return head;

    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    ListNode* end = head;

    while (end) {
        for (int i = 1; i < k && end; ++i) {
            end = end->next;
        }
        if (!end) break;

        ListNode* next = end->next;
        ListNode* start = prev->next;
        end->next = nullptr;
        prev->next = reverseListIterative(start);

        start->next = next;
        prev = start;
        end = prev->next;
    }
    return dummy.next;
}

int main() {
    return 0;
}

