// https://leetcode.com/problems/lru-cache/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int key;
    int value;
    Node *next;
    Node *prev;

    Node(int _key, int _value) : key(_key), value(_value), next(nullptr), prev(nullptr) {}
};

class LRUCache
{
private:
    int capacity;
    Node *head;
    Node *tail;
    int size;
    unordered_map<int, Node *> nodes;

public:
    LRUCache(int _capacity)
    {
        capacity = _capacity;
        head = tail = new Node(0, 0);
        size = 0;

        // Link head and tail
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {

        if (nodes.find(key) == nodes.end())
            return -1; // Not found

        Node *node = deleteNode(nodes[key]);

        insert_after_head(node);

        return nodes[key]->value;
    }

    void put(int key, int value)
    {

        if (get(key) != -1)
        {
            Node *node = nodes[key];
            node->value = value;
            node = nullptr;
            return;
        }

        if (size == capacity)
        {
            Node *lru_node = tail->prev;
            nodes.erase(lru_node->key);
            // cout << lru_node->key << endl;
            deleteNode(lru_node);
            delete lru_node;
            lru_node = nullptr;
            --size;
        }

        Node *new_node = new Node(key, value);
        insert_after_head(new_node);
        nodes[key] = new_node;
        new_node = nullptr;
        ++size;
    }

private:
    Node *deleteNode(Node *node)
    {
        Node *prev = node->prev;

        // Link node's prev with node's next
        prev->next = node->next;
        node->next->prev = prev;

        return node;
    }
    void insert_after_head(Node *node)
    {
        Node *next = head->next;

        // Link with head and node
        head->next = node;
        node->prev = head;

        // Link with node and node after
        node->next = next;
        next->prev = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */