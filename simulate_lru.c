#include <stdio.h>
#include "page_caches.h"

struct LRU
{
    int page;
    int time;
};

struct LRU buffer_LRU[MAX_PAGES];

int findPage(int page)
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (buffer_LRU[i].page == page)
            return i;
    }
    return -1;
}
void initBuffer()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        buffer_LRU[i].page = -1;
        buffer_LRU[i].time = -1;
    }
}

void simulate_lru(int pages[], struct PageCacheStats *stats)
{
    initBuffer();

    int hits = 0, misses = 0, counter = 0;

    printf("\n" COLOR_BOLD COLOR_CYAN);
    printf("-------------------------------------------------------------\n");
    printf("| %-16s |  %10s | %-8s | %-14s|\n", "Current Frame", "Requested", "Result", "Updated Frame");
    printf("-------------------------------------------------------------\n" COLOR_RESET);

    for (int i = 0; i < MAX_PAGES; i++)
    {
        int page = pages[i];
        int index = findPage(page);

        printf("|");
        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (buffer_LRU[j].page != -1)
                printf("%3d ", buffer_LRU[j].page);
            else
                printf("  - ");
        }
        printf("      | ");

        const char *color;
        const char *status;

        if (index != -1)
        {
            // HIT
            hits++;
            color = COLOR_GREEN;
            status = "HIT";
            buffer_LRU[index].time = ++counter;
        }
        else
        {
            // MISS
            misses++;
            color = COLOR_RED;
            status = "MISS";

            if (i < MAX_FRAMES)
            {
                buffer_LRU[i].page = page;
                buffer_LRU[i].time = ++counter;
            }
            else
            {
                int lru = 0;
                for (int j = 1; j < MAX_FRAMES; j++)
                {
                    if (buffer_LRU[lru].time > buffer_LRU[j].time)
                        lru = j;
                }
                buffer_LRU[lru].page = page;
                buffer_LRU[lru].time = ++counter;
            }
        }

        printf("     %s%-5d%s  | %s%-8s%s | ", color, page, COLOR_RESET, color, status, COLOR_RESET);

        for (int k = 0; k < MAX_FRAMES; k++)
        {
            if (buffer_LRU[k].page != -1)
                printf("%2d ", buffer_LRU[k].page);
            else
                printf("-  ");
        }
        printf("     |\n");
    }

    printf(COLOR_CYAN);
    printf("-------------------------------------------------------------\n");
    printf(COLOR_YELLOW "    Hits = %d   Misses = %d   Hit Ratio = %.2f\n" COLOR_RESET,
           hits, misses, (float)hits / (hits + misses));
    printf(COLOR_CYAN "-------------------------------------------------------------\n\n" COLOR_RESET);

    stats->hits = hits;
    stats->misses = misses;
}
