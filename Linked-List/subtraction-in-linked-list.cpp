// https://practice.geeksforgeeks.org/problems/subtraction-in-linked-list/1

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

int getLength(Node *head)
{
    int length = 0;

    while (head)
    {
        ++length;
        head = head->next;
    }

    return length;
}

Node *removeLeadingZeros(Node *head)
{
    while (head && head->data == 0)
        head = head->next;

    return head;
}

Node *reverseList(Node *head)
{
    if (!head || !head->next)
        return head;

    Node *curr = head, *prev = nullptr;

    while (curr)
    {
        Node *temp = curr;
        curr = curr->next;
        temp->next = prev;
        prev = temp;
    }

    return prev;
}

Node *subLinkedList(Node *l1, Node *l2)
{

    l1 = removeLeadingZeros(l1);
    l2 = removeLeadingZeros(l2);

    int l1_length = getLength(l1);
    int l2_length = getLength(l2);

    if (l1_length < l2_length)
        swap(l1, l2);
    else if (l1_length == l2_length)
    {
        Node *curr1 = l1, *curr2 = l2;

        while (curr1 && curr2)
        {
            if (curr1->data == curr2->data)
            {
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
            else if (curr2->data > curr1->data)
            {
                swap(l1, l2);
                break;
            }
            else
                break;
        }
    }

    l1 = reverseList(l1);
    l2 = reverseList(l2);

    Node dummy(0);
    Node *curr = &dummy;

    int borrow = 0;

    while (l1)
    {
        int l2_val = l2 ? l2->data : 0;
        int sum = l1->data - l2_val - borrow;

        if (sum < 0)
        {
            sum += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        curr->next = new Node(sum);
        curr = curr->next;

        l1 = l1->next;

        if (l2)
            l2 = l2->next;
    }

    Node *head = reverseList(dummy.next);
    head = removeLeadingZeros(head);

    if (!head)
        return new Node(0);

    return head;
}