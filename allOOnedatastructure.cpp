#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class AllOne {
    struct ListNode {
        int count;
        unordered_set<string> keys;
        ListNode *prev, *next;
        ListNode(int c) : count(c), prev(nullptr), next(nullptr) {}
    };

    ListNode *head, *tail;
    unordered_map<string, ListNode*> keyNode;
    unordered_map<int, ListNode*> countNode;

    ListNode* addNodeAfter(ListNode *prevNode, int count) {
        ListNode *newNode = new ListNode(count);
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        prevNode->next->prev = newNode;
        prevNode->next = newNode;
        countNode[count] = newNode;
        return newNode;
    }

    void removeNodeIfEmpty(ListNode *node) {
        if (node->keys.empty()) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            countNode.erase(node->count);
            delete node;
        }
    }

public:
    AllOne() {
        head = new ListNode(0);
        tail = new ListNode(0);
        head->next = tail;
        tail->prev = head;
    }

    void inc(string key) {
        if (keyNode.find(key) == keyNode.end()) {
            if (head->next->count != 1) {
                addNodeAfter(head, 1);
            }
            head->next->keys.insert(key);
            keyNode[key] = head->next;
        } else {
            ListNode *curNode = keyNode[key];
            int curCount = curNode->count;
            ListNode *nextNode;
            if (curNode->next->count != curCount + 1) {
                nextNode = addNodeAfter(curNode, curCount + 1);
            } else {
                nextNode = curNode->next;
            }
            nextNode->keys.insert(key);
            keyNode[key] = nextNode;
            curNode->keys.erase(key);
            removeNodeIfEmpty(curNode);
        }
    }

    void dec(string key) {
        ListNode *curNode = keyNode[key];
        int curCount = curNode->count;
        if (curCount == 1) {
            keyNode.erase(key);
            curNode->keys.erase(key);
            removeNodeIfEmpty(curNode);
        } else {
            ListNode *prevNode;
            if (curNode->prev->count != curCount - 1) {
                prevNode = addNodeAfter(curNode->prev, curCount - 1);
            } else {
                prevNode = curNode->prev;
            }
            prevNode->keys.insert(key);
            keyNode[key] = prevNode;
            curNode->keys.erase(key);
            removeNodeIfEmpty(curNode);
        }
    }

    string getMaxKey() {
        return tail->prev == head ? "" : *tail->prev->keys.begin();
    }

    string getMinKey() {
        return head->next == tail ? "" : *head->next->keys.begin();
    }
};
