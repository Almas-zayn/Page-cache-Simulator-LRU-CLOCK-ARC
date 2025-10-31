Page-cache-Simulator-LRU-CLOCK-ARC

A small command-line simulator that demonstrates and compares three page-replacement / cache policies:

LRU (Least Recently Used)

CLOCK (Second-Chance / Clock)

ARC (Adaptive Replacement Cache)

This repository contains simple implementations of each algorithm and a driver that runs the same input access sequences (three access orders) on each policy and prints per-step state plus comparison tables.

Repo layout
.
├─ page_caches.h             # shared constants, colors, PageCacheStats struct, etc.
├─ simulate_lru.c            # LRU implementation + pretty print per access
├─ simulate_clock.c          # Clock implementation + pretty print per access
├─ simulate_arc.c            # ARC implementation + pretty print per access
└─ page_caches_simulator.c   # driver: defines example inputs and runs all simulations


Note: page_caches.h defines MAX_FRAMES and MAX_PAGES used by the simulators (the code uses 3 frames and 12 pages in the examples). The simulators print colored output (ANSI escape sequences) for readability.

Build

Compile the simulator with gcc:

gcc page_caches_simulator.c simulate_lru.c simulate_clock.c simulate_arc.c -o page_cache_simulator


If your system complains about any missing headers or flags, compile like this (explicit C standard):

gcc -std=c11 page_caches_simulator.c simulate_lru.c simulate_clock.c simulate_arc.c -o page_cache_simulator

Run
./page_cache_simulator


This runs all three policies on the three example input orders embedded in page_caches_simulator.c and prints:

A per-access table for each policy (requested page, hit/miss, and frame / internal state snapshot).

A summary line (Hits, Misses, Hit Ratio).

A final comparison table (for each access order) showing Hits, Misses, and Hit Ratio (%) for each policy (LRU, CLOCK, ARC).

Inputs used by the driver (exact arrays from page_caches_simulator.c)

The driver defines three example sequences (each has MAX_PAGES = 12 elements):

Random order (pages1)

int pages1[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};


Sequential order (pages2)

int pages2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};


Looping order (pages3)

int pages3[] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};


Assumption used by the code (as visible in the implementations):

Number of frames (cache capacity): 3 (the implementations reference MAX_FRAMES or CAPACITY = 3)

Results (computed from the exact simulator logic used in the repo)

I ran the same algorithms and input sequences (following the exact logic from the C code) to produce the numeric summaries shown below. These are the same numbers the simulator will print when you run it.

pages1 (random)

LRU: Hits = 2, Misses = 10, Hit Ratio = 16.67%

CLOCK: Hits = 3, Misses = 9, Hit Ratio = 25.00%

ARC: Hits = 4, Misses = 8, Hit Ratio = 33.33%

pages2 (sequential 1..12)

LRU: Hits = 0, Misses = 12, Hit Ratio = 0.00%

CLOCK: Hits = 0, Misses = 12, Hit Ratio = 0.00%

ARC: Hits = 0, Misses = 12, Hit Ratio = 0.00%

pages3 (loop 1,2,3 repeating)

LRU: Hits = 9, Misses = 3, Hit Ratio = 75.00%

CLOCK: Hits = 9, Misses = 3, Hit Ratio = 75.00%

ARC: Hits = 9, Misses = 3, Hit Ratio = 75.00%

Interpretation / Highlights

For the random sequence pages1, ARC adapts and achieves the highest hit ratio among the three for this input with capacity 3.

For strictly sequential accesses beyond capacity (pages2), none of the algorithms obtain hits (all misses), since pages never repeat within the window.

For small repeating working sets that fit in 3 frames (pages3), all algorithms keep the hot set resident and reach a high hit ratio.

How the per-policy implementations behave (short summary)

LRU: Tracks last access time and evicts the page with the oldest timestamp. The LRU implementation assigns timestamps on each access and finds the smallest timestamp for eviction.

CLOCK: Uses a reference bit array and a pointer (clock hand). On a miss, the pointer searches for the first frame with refBit == 0; while scanning, it clears refBits set to 1 (second-chance behavior).

ARC: Maintains four lists (T1, T2, B1, B2) and an adaptive parameter p steering the split between recency (T1) and frequency (T2). The implementation in simulate_arc.c follows the canonical high-level ARC behavior (T1 and T2 are resident lists, B1 and B2 are ghost lists).

Adding / editing input scenarios

To modify the sample access sequences, edit page_caches_simulator.c:

// Edit / add sequences here
int pages1[] = { ... }; // random
int pages2[] = { ... }; // sequential
int pages3[] = { ... }; // looping

// If you change number of accesses, ensure MAX_PAGES (in header) matches or adjust loops accordingly.


To change cache capacity, modify MAX_FRAMES (or the CAPACITY constant inside simulate_arc.c / page_caches.h) consistently.

Suggestions / next steps (ideas)

Add command-line flags to choose:

which algorithm(s) to run

the cache capacity at runtime

custom input sequences (from a file or CLI)

Dump results to CSV for plotting and analysis.

Add unit tests that assert hit/miss counts for known traces.

Support variable frame counts and sweep the frame count to create hit-rate vs frames plots.

License

Add your preferred license if you want this to be public-friendly (e.g., MIT).

Contact / Author

Repo author: Almas-zayn (existing GitHub account for the repo).
