#include<stdio.h>
#include<stdlib.h>
#include<unordered_map>

using namespace std;

typedef struct node {
    int val;
    struct node * next;
    struct node * random;
}node;

node * create_node(int val) {
    node * n = (node *)malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    n->random = NULL;
    return n;
}

void print_rand_list(node * list) {
    node * t = list;
    while(t != NULL) {
        printf("%d %d\n", t->val, t->random != NULL ? t->random->val : -1);
        t = t->next;
    }
    printf("\n");
    return;
}

node * clone_list(node * head) {
    node * temp = head;
    node * newlist_head;
    int first = 1;

    while(temp != NULL) {
        node * newnode = create_node(temp->val);
        if (first) {
            newlist_head = newnode;
            first = 0;
        }
        newnode->next = temp->next;
        temp->next = newnode;
        temp = newnode->next;
    }

    node * prev = head;
    node * newnode = head->next;

    while(newnode != NULL) {
        newnode->random = prev->random != NULL ? prev->random->next : NULL;
        prev->next = newnode->next; //reverses the changes
        prev = newnode->next;
        newnode = prev != NULL ? prev->next : NULL;
    }
    print_rand_list(head);
    print_rand_list(newlist_head);
    return newlist_head;
}

//hash map old key, new val
//new.random = map(old.random)

node * clone_list_hashed(node * head) {
    unordered_map<node *, node *> map;
    node * temp = head, *prev;
    node * newlist_head;
    int first = 1;

    while(temp != NULL) {
        node * newnode = create_node(temp->val);
        map[temp] = newnode;
        if (first) {
            newlist_head = newnode;
            first = 0;
            prev = newnode;
        } else {
            prev->next = newnode;
            prev = newnode;
        }
        temp = temp->next;
    }

    node * new_temp = newlist_head;
    node * old_temp = head;

    while(new_temp != NULL) {
        new_temp->random = map[old_temp->random];
        new_temp = new_temp->next;
        old_temp = old_temp->next;
    }

    print_rand_list(newlist_head);
    return newlist_head;
}

int main() {
    node * a1= create_node(1);
    node * a2= create_node(2);
    node * a3= create_node(3);
    node * a4= create_node(4);
    node * a5= create_node(5);
    node * a6= create_node(6);

    a1->next = a2;
    a2->next = a3;
    a3->next = a4;
    a4->next = a5;
    a5->next = a6;
    a6->next = NULL;

    a1->random = a3;
    a2->random = a5;
    a5->random = a2;
    a6->random = a4;

    print_rand_list(a1);

    clone_list_hashed(a1);

    return 0;
}