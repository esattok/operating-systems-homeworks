#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

void freeMemory(struct Node* head);
void printLinkedList(struct Node* head);
struct Node* generateLinkedList(const int linkedListSize);
void sortedInsert(struct Node** headRef, struct Node* newNode);

int main() {
    struct timeval start_time;
    struct timeval end_time;
    const int NODE_COUNT = 10000;
    struct Node* head = NULL;

    srand(time(0));
    gettimeofday(&start_time, NULL);
    head = generateLinkedList(NODE_COUNT);
    gettimeofday(&end_time, NULL);

    printf("Elapsed Time (microseconds): %ld\n", (end_time.tv_usec - start_time.tv_usec));
    printLinkedList(head);
    freeMemory(head);
    return 0; 
}

 // Helper Functions
void freeMemory(struct Node* head) {
    while (head != NULL) {
        struct Node* newNode = head->next;
        free(head);
        head = newNode;
    } 
}

void printLinkedList(struct Node* head) {
    struct Node* tail = NULL;
    while (head != NULL) {
        struct Node* newNode = head->next;
        printf("value = %d\n", head->value);
        head = newNode;
    }
}

struct Node* generateLinkedList(const int linkedListSize) {
    struct Node* head = NULL;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = rand();
    newNode->next = NULL;
    newNode->prev = NULL;

    for (int i = 1; i < linkedListSize; i++) {
        sortedInsert(&head, newNode);
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->value = rand();
        newNode->next = NULL;
        newNode->prev = NULL;
    }

    return head;
}

void sortedInsert(struct Node** headRef, struct Node* newNode)  {
    struct Node* current;
    
    if (*headRef == NULL || (*headRef)->value >= newNode->value) {
        if (*headRef != NULL) {
            (*headRef)->prev = newNode;
        }
        newNode->next = *headRef;
        *headRef = newNode;
    }

    else {
        current = *headRef;
        while (current->next != NULL && current->next->value < newNode->value) {
            current = current->next;
        }
        newNode->next = current->next;
        if (current->next != NULL) {
            current->next->prev = newNode;
        }
        newNode->prev = current;
        current->next = newNode;
    }
}