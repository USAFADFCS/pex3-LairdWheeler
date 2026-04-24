/** pagequeue.c
 * ===========================================================
 * Name: Laird Wheeler, 4 23 2026
 * Section: CS483 / M3
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue *pq = malloc(sizeof(PageQueue));

    if (pq == NULL) {
        fprintf(stderr, "pqInit: malloc failed\n");
        exit(1);
    }

    pq->head    = NULL;
    pq->tail    = NULL;
    pq->size    = 0;
    pq->maxSize = maxSize;

    return pq;

}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
    long depth = 0;
    PqNode *cur = pq->tail;
 
    while (cur != NULL) {
        if (cur->pageNum == pageNum) {

            //HIT (Removes the node and reinserts at eh tail)
            if (cur != pq->tail) {
                
                if (cur->prev != NULL) {
                    cur->prev->next = cur->next;
                } else {
                    pq->head = cur->next;
                }
                if (cur->next != NULL) {
                    cur->next->prev = cur->prev;
                }
 
                cur->prev       = pq->tail;
                cur->next       = NULL;
                pq->tail->next  = cur;
                pq->tail        = cur;
            }
 
            return depth;
        }
        depth++;
        cur = cur->prev;
    }
 
    //MISS
    //Mallocs new node and appends to the tail
    PqNode *nn = malloc(sizeof(PqNode));
    if (nn == NULL) {
        fprintf(stderr, "malloc fialed\n");
        exit(1);
    }
    nn->pageNum = pageNum;
    nn->next    = NULL;
    nn->prev    = pq->tail;
 
    if (pq->tail == NULL) {
        pq->head = nn;
        pq->tail = nn;
    } else {
        pq->tail->next = nn;
        pq->tail       = nn;
    }
    pq->size++;
 
    //Evicts if larger than max size
    if (pq->size > pq->maxSize) {
        PqNode *evict = pq->head;
        pq->head = evict->next;
        if (pq->head != NULL) {
            pq->head->prev = NULL;
        } else {
            pq->tail = NULL;
        }
        free(evict);
        pq->size--;
    }
 
    return -1;

}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.

    PqNode *cur = pq->head;
    while (cur != NULL) {

        PqNode *next = cur->next;
        free(cur);
        cur = next;
    }

    free(pq);
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.

    
}
