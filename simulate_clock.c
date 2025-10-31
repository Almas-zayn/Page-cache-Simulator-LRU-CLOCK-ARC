#include <stdio.h>
#include "page_caches.h"

void simulate_clock(int pages[], struct PageCacheStats *stats)
{
    int buffer[MAX_FRAMES];
    int refBit[MAX_FRAMES];
    int pointer = 0, hits = 0, misses = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        buffer[i] = -1;
        refBit[i] = 0;
    }

    printf("\n" COLOR_BOLD COLOR_CYAN);
    printf("----------------------------------------------\n");
    printf("%10s | %-8s | %-20s\n", "Requested", "Result", "Frame State");
    printf("----------------------------------------------\n" COLOR_RESET);

    for (int i = 0; i < MAX_PAGES; i++)
    {
        int page = pages[i];
        int found = 0;

        // Check if page exists (HIT)
        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (buffer[j] == page)
            {
                found = 1;
                refBit[j] = 1;
                hits++;
                break;
            }
        }

        // If not found → MISS, replace using Clock logic
        if (!found)
        {
            misses++;
            while (1)
            {
                if (refBit[pointer] == 0)
                {
                    buffer[pointer] = page;
                    refBit[pointer] = 1;
                    pointer = (pointer + 1) % MAX_FRAMES;
                    break;
                }
                else
                {
                    refBit[pointer] = 0;
                    pointer = (pointer + 1) % MAX_FRAMES;
                }
            }
        }

        // Print row
        const char *color = found ? COLOR_GREEN : COLOR_RED;
        const char *status = found ? "HIT" : "MISS";

        printf("  %s%-8d%s | %s%-8s%s | ", color, page, COLOR_RESET, color, status, COLOR_RESET);

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (buffer[j] != -1)
                printf("%2d ", buffer[j]);
            else
                printf("-  ");
        }
        printf("\n");
    }

    printf(COLOR_CYAN);
    printf("----------------------------------------------\n");
    printf(COLOR_YELLOW "Hits = %d   Misses = %d   Hit Ratio = %.2f\n" COLOR_RESET,
           hits, misses, (float)hits / (hits + misses));
    printf(COLOR_CYAN "----------------------------------------------\n\n" COLOR_RESET);

    stats->hits = hits;
    stats->misses = misses;
}
