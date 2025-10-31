#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_caches.h"

#define CAPACITY 3
#define MAX_PAGES 12

typedef struct Node
{
    int page;
    struct Node *next;
} Node;

// ARC state
static Node *T1 = NULL, *T2 = NULL, *B1 = NULL, *B2 = NULL;
static int size_T1 = 0, size_T2 = 0;
static int p = 1; // Adaptive balance parameter

//---------------------------------------------------
Node *newNode(int page)
{
    Node *n = malloc(sizeof(Node));
    if (!n)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    n->page = page;
    n->next = NULL;
    return n;
}

int search(Node *head, int page)
{
    for (; head; head = head->next)
        if (head->page == page)
            return 1;
    return 0;
}

void insert(Node **head, int page)
{
    Node *n = newNode(page);
    n->next = *head;
    *head = n;
}

void deleteLast(Node **head)
{
    if (!*head)
        return;
    Node *temp = *head, *prev = NULL;
    while (temp->next)
    {
        prev = temp;
        temp = temp->next;
    }
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;
    free(temp);
}

void freeList(Node **head)
{
    Node *temp;
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

//---------------------------------------------------
void resetARCState(void)
{
    freeList(&T1);
    freeList(&T2);
    freeList(&B1);
    freeList(&B2);
    size_T1 = 0;
    size_T2 = 0;
    p = 1;
}

//---------------------------------------------------
void replace(int page)
{
    if (size_T1 >= 1 && ((size_T1 > p) || (search(B2, page) && size_T1 == p)))
    {
        deleteLast(&T1);
        size_T1--;
        insert(&B1, page);
    }
    else
    {
        deleteLast(&T2);
        size_T2--;
        insert(&B2, page);
    }
}

//---------------------------------------------------
void listToString(Node *head, char *buffer, size_t size)
{
    buffer[0] = '\0';
    char temp[10];
    for (; head; head = head->next)
    {
        snprintf(temp, sizeof(temp), "%d ", head->page);
        strncat(buffer, temp, size - strlen(buffer) - 1);
    }
}

void simulate_arc(int pages[], struct PageCacheStats *stats)
{
    int hits = 0, misses = 0;

    resetARCState();

    printf("\n" COLOR_BOLD COLOR_CYAN);
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("%7s | %-6s | %-18s | %-18s | %-18s | %-18s\n",
           "Access", "Result", "T1 (Recent)", "T2 (Frequent)", "B1 (Ghost T1)", "B2 (Ghost T2)");
    printf("--------------------------------------------------------------------------------------------------\n" COLOR_RESET);

    for (int i = 0; i < MAX_PAGES; i++)
    {
        int page = pages[i];
        char result[16];
        const char *color;

        if (search(T1, page) || search(T2, page))
        {
            hits++;
            strcpy(result, "HIT");
            color = COLOR_GREEN;
            insert(&T2, page);
            size_T2++;
        }
        else
        {
            misses++;
            strcpy(result, "MISS");
            color = COLOR_RED;

            if ((size_T1 + size_T2) == CAPACITY)
                replace(page);

            if (search(B1, page))
                p = (p < CAPACITY) ? p + 1 : CAPACITY;
            else if (search(B2, page))
                p = (p > 0) ? p - 1 : 0;

            insert(&T1, page);
            size_T1++;
        }

        char sT1[64], sT2[64], sB1[64], sB2[64];
        listToString(T1, sT1, sizeof(sT1));
        listToString(T2, sT2, sizeof(sT2));
        listToString(B1, sB1, sizeof(sB1));
        listToString(B2, sB2, sizeof(sB2));

        printf("   %s%-4d%s | %s%-6s%s | %-18s | %-18s | %-18s | %-18s\n",
               color, page, COLOR_RESET, color, result, COLOR_RESET, sT1, sT2, sB1, sB2);
    }

    printf(COLOR_CYAN);
    printf("--------------------------------------------------------------------------------------------------\n");
    printf(COLOR_YELLOW "Hits = %d   Misses = %d   Hit Ratio = %.2f\n" COLOR_RESET,
           hits, misses, (float)hits / (hits + misses));
    printf(COLOR_CYAN "--------------------------------------------------------------------------------------------------\n\n" COLOR_RESET);

    stats->hits = hits;
    stats->misses = misses;

    resetARCState();
}
