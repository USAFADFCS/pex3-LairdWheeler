/** 
 * ================================================================
 * Name: Laird Wheeler
 * Section: T4
 * Project: Implementation of Double-Linked List Library
 * =================================================================
 */
#include "listAsDoubleLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

DoubleLinkedList* createLinkedList() {

    DoubleLinkedList* newDLL = malloc(sizeof(DoubleLinkedList));
    newDLL->head = NULL;
    newDLL->tail = NULL;
    newDLL->numberOfElements = 0;

    return newDLL;
}

void deleteLinkedList(DoubleLinkedList* list) {

    Node* tmp = malloc(sizeof(Node));

    tmp = list->head->next;
    while (tmp != list->tail) {

        free(tmp->prev);
        tmp->prev->next = NULL;
        tmp->prev->prev = NULL;

        tmp = tmp->next;
    }

    free(tmp);
    tmp->next = NULL;
    tmp->prev = NULL;
}

void appendElementLinkedList(DoubleLinkedList* list, int element) {

    Node* nn = malloc(sizeof(Node));
    nn->data = element;
    Node* tmp = malloc(sizeof(Node));

    if (list->numberOfElements == 0) {

        list->tail = nn;
        list->head = nn;
        free(tmp);
    }
    else if (list->numberOfElements == 1) {

        list->tail = nn;
        list->tail->prev = list->head;
        list->head->next = list->tail;
        free(tmp);
    }
    else {

        list->tail->next = nn;
        nn->prev = list->tail;
        list->tail = nn;
        free(tmp);
    }

    list->numberOfElements++;
}

int lengthOfLinkedList(DoubleLinkedList* list) {

    return list->numberOfElements;
}

void printLinkedList(DoubleLinkedList* list) {

    Node* tmp = malloc(sizeof(Node));
    tmp = list->head;

    for (int i = 0; i < list->numberOfElements; i++) {

        printf("%d ", tmp->data);
        tmp = tmp->next;
    }

    printf("\n");
    free(tmp);
}

int getElementLinkedList(DoubleLinkedList* list, int position) {

    if (position >= list->numberOfElements) {
        return -1;
    }

    Node* tmp = malloc(sizeof(Node));
    tmp = list->head;

    for (int i = 0; i < position; i++) {

        tmp = tmp->next;
    }

    return tmp->data;
    free(tmp);
    tmp->next = NULL;
    tmp->prev = NULL;
}

void deleteElementLinkedList(DoubleLinkedList* list, int position) {

    Node* tmp = malloc(sizeof(Node));

    if (position >= list->numberOfElements) {
        printf("Index is out of bounds\n");
    }
    else if (position == 0) {
        
        list->head = list->head->next;
        free(list->head->prev);
        list->head->prev = NULL;
        free(tmp);

        list->numberOfElements--;
    }
    else if (position == (list->numberOfElements)-1) {

        list->tail = list->tail->prev;
        free(list->tail->next);
        list->tail->next = NULL;
        free(tmp);

        list->numberOfElements--;
    }
    else {

        tmp = list->head;
        for (int i = 0; i < position; i++) {
            tmp = tmp->next;
        }

        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
        list->numberOfElements--;
    }

}

void insertElementLinkedList(DoubleLinkedList* list, int position, int element) {

    Node* nn = malloc(sizeof(Node));
    nn->data = element;
    Node* tmp = malloc(sizeof(Node));

    if (position == 0) {

        list->head->prev = nn;
        nn->next = list->head;
        list->head = nn;

        list->numberOfElements++;
    }
    else if (position == list->numberOfElements) {

        list->tail->next = nn;
        nn->prev = list->tail;
        list->tail = nn;    

        list->numberOfElements++;
    }
    else {

        tmp = list->head;
        for (int i = 0; i < position; i++) {

            tmp = tmp->next;
        }

        nn->prev = tmp->prev;
        nn->next = tmp->prev->next;
        tmp->prev->next = nn;
        tmp->prev = nn;

        list->numberOfElements++;
    }
    //free(tmp);
}

void changeElementLinkedList(DoubleLinkedList* list, int position, int newElement) {

    Node* tmp = malloc(sizeof(Node));
    tmp = list->head;
    for (int i = 0; i < position; i++) {
        tmp = tmp->next;
    }

    tmp->data = newElement;
}

int findElementLinkedList(DoubleLinkedList* list, int element) {

    Node* tmp = malloc(sizeof(Node));
    tmp = list->head;
    for (int i = 0; i < list->numberOfElements; i++) {

        if (tmp->data == element) {

            return i;
        }
        tmp = tmp->next;
    }
    return -1;
}