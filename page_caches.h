#ifndef PAGE_CACHES_H
#define PAGE_CACHES_H

// Define color escape codes
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"

// ANSI colors
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define BOLD "\033[1m"
#define ORANGE "\033[38;5;208m"

#define MAX_FRAMES 3
#define MAX_PAGES 12

struct PageCacheStats
{
    int hits;
    int misses;
};

void simulate_lru(int pages[], struct PageCacheStats *stats);

void simulate_clock(int pages[], struct PageCacheStats *stats);

void simulate_arc(int pages[], struct PageCacheStats *stats);

#endif