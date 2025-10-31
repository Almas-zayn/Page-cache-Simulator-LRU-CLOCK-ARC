#include <stdio.h>
#include "page_caches.h"
#define STATS 3

//  random order
int pages1[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

// sequential order
int pages2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// looping order
int pages3[] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};

struct PageCacheStats lruStats[STATS];
struct PageCacheStats clockStats[STATS];
struct PageCacheStats arcStats[STATS];

void printOrderName(const char *ordername)
{
    printf("-----------> %s <---------\n\n", ordername);
}
void printCacheName(const char *cacheName)
{
    printf("\n\n-----------------------------------------------------------------------\n");
    printf("----------->%10s %s %10s<---------\n", " ", cacheName, " ");
    printf("-----------------------------------------------------------------------\n");
}
void simulateAllOrdersLRU()
{
    printCacheName(" LRU CACHE ");
    printOrderName("Simulating LRU cache with Random order");
    simulate_lru(pages1, &lruStats[0]);
    printOrderName("Simulating LRU cache with Sequential order");
    simulate_lru(pages2, &lruStats[1]);
    printOrderName("Simulating LRU cache with Looping order");
    simulate_lru(pages3, &lruStats[2]);
}
void simulateAllOrdersClock()
{
    printCacheName(" CLOCK CACHE ");
    printOrderName("Simulating Clock cache with Random order");
    simulate_clock(pages1, &clockStats[0]);
    printOrderName("Simulating Clock cache with Sequential order");
    simulate_clock(pages2, &clockStats[1]);
    printOrderName("Simulating Clock cache with Looping order");
    simulate_clock(pages3, &clockStats[2]);
}

void simulateAllOrdersARC()
{
    printCacheName(" ARC CACHE ");
    printOrderName("Simulating ARC cache with Random order");
    simulate_arc(pages1, &arcStats[0]);
    printOrderName("Simulating ARC cache with Sequential order");
    simulate_arc(pages2, &arcStats[1]);
    printOrderName("Simulating ARC cache with Looping order");
    simulate_arc(pages3, &arcStats[2]);
}

void printComparisonOrderTable(const char *orderName, int index)
{
    float ratios[3];
    ratios[0] = (float)lruStats[index].hits / (lruStats[index].hits + lruStats[index].misses) * 100.0;
    ratios[1] = (float)clockStats[index].hits / (clockStats[index].hits + clockStats[index].misses) * 100.0;
    ratios[2] = (float)arcStats[index].hits / (arcStats[index].hits + arcStats[index].misses) * 100.0;

    // Find max and min ratios
    float max = ratios[0], min = ratios[0];
    for (int i = 1; i < 3; i++)
    {
        if (ratios[i] > max)
            max = ratios[i];
        if (ratios[i] < min)
            min = ratios[i];
    }

    printf("\n\n%s=======================================================================%s\n", ORANGE, RESET);
    printf("%30s %s ORDER COMPARISON %s\n", CYAN, orderName, RESET);
    printf("=======================================================================\n");
    printf("| %s%-10s%s | %s%-10s%s | %s%-10s%s | %s%-15s%s |\n", CYAN, "CACHE TYPE", RESET, GREEN, "HITS", RESET, RED, "MISSES", RESET, CYAN, "HIT RATIO (%)", RESET);
    printf("-----------------------------------------------------------------------\n");

// Helper macro to colorize ratio based on value
#define COLORIZE(ratio) (ratio == max ? GREEN : (ratio == min ? RED : YELLOW))

    // LRU
    printf("| %-10s | %-10d | %-10d | %s%-15.2f%s |\n",
           "LRU",
           lruStats[index].hits,
           lruStats[index].misses,
           COLORIZE(ratios[0]), ratios[0], RESET);

    // CLOCK
    printf("| %-10s | %-10d | %-10d | %s%-15.2f%s |\n",
           "CLOCK",
           clockStats[index].hits,
           clockStats[index].misses,
           COLORIZE(ratios[1]), ratios[1], RESET);

    // ARC
    printf("| %-10s | %-10d | %-10d | %s%-15.2f%s |\n",
           "ARC",
           arcStats[index].hits,
           arcStats[index].misses,
           COLORIZE(ratios[2]), ratios[2], RESET);

    printf("=======================================================================\n");

#undef COLORIZE
}

int main()
{

    simulateAllOrdersLRU();
    simulateAllOrdersClock();
    simulateAllOrdersARC();

    // Print comparison tables
    printComparisonOrderTable("RANDOM", 0);
    printComparisonOrderTable("SEQUENTIAL", 1);
    printComparisonOrderTable("LOOPING", 2);
    printf("\n");

    return 0;
}