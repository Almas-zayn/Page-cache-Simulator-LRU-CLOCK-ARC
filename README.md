

# 🧠 Page Cache Simulator — LRU | CLOCK | ARC

A **C-based page replacement simulator** that compares the behavior of three popular cache/page replacement algorithms:
- **LRU (Least Recently Used)**
- **CLOCK (Second-Chance)**
- **ARC (Adaptive Replacement Cache)**

It prints **step-by-step colored output** and **comparison tables** for each access order (random, sequential, looping).

---

## 📂 Repository Structure
.
├── page_caches.h # Common definitions, structs, color codes
├── simulate_lru.c # LRU implementation
├── simulate_clock.c # CLOCK (Second-Chance) implementation
├── simulate_arc.c # ARC implementation
└── page_caches_simulator.c # Main driver - runs all algorithms & compares


---

## ⚙️ Compilation

Compile all source files together:

```bash
gcc page_caches_simulator.c simulate_lru.c simulate_clock.c simulate_arc.c -o page_cache_simulator

or (for standard C11):
gcc -std=c11 page_caches_simulator.c simulate_lru.c simulate_clock.c simulate_arc.c -o page_cache_simulator
```

▶️ Run

Execute the compiled simulator:
```bash
./page_cache_simulator
```

It will display:

Step-by-step frame states for each algorithm

Hits, Misses, and Hit Ratios

Colored comparison tables for each access pattern
## 📊 Input Access Sequences (from `page_caches_simulator.c`)

The simulator tests **three access patterns** with cache capacity = **3 frames** (`MAX_FRAMES = 3`):

| 🔹 **Access Type** | 🧱 **Array Name** | 📄 **Sequence** |
|--------------------|------------------|-----------------|
| 🔸 Random | `pages1` | `{1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}` |
| 🔹 Sequential | `pages2` | `{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}` |
| 🔁 Looping | `pages3` | `{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}` |

---

## 📈 Results Summary

The following tables show the **Hit**, **Miss**, and **Hit Ratio** values computed by the simulator (based on its exact logic):

### 🔸 Random Order (`pages1`)

| 🧩 **Algorithm** | ✅ **Hits** | ❌ **Misses** | 📊 **Hit Ratio** |
|------------------|-------------|---------------|------------------|
| 🟠 **LRU** | 2 | 10 | 16.67% |
| 🔵 **CLOCK** | 3 | 9 | 25.00% |
| 🟢 **ARC** | 4 | 8 | 33.33% |

---

### 🔹 Sequential Order (`pages2`)

| 🧩 **Algorithm** | ✅ **Hits** | ❌ **Misses** | 📊 **Hit Ratio** |
|------------------|-------------|---------------|------------------|
| 🟠 **LRU** | 0 | 12 | 0.00% |
| 🔵 **CLOCK** | 0 | 12 | 0.00% |
| 🟢 **ARC** | 0 | 12 | 0.00% |

---

### 🔁 Looping Order (`pages3`)

| 🧩 **Algorithm** | ✅ **Hits** | ❌ **Misses** | 📊 **Hit Ratio** |
|------------------|-------------|---------------|------------------|
| 🟠 **LRU** | 9 | 3 | 75.00% |
| 🔵 **CLOCK** | 9 | 3 | 75.00% |
| 🟢 **ARC** | 9 | 3 | 75.00% |

---

## 🧩 Algorithm Overview

| 🔹 **Algorithm** | ⚙️ **Description** |
|------------------|--------------------|
| 🟠 **LRU (Least Recently Used)** | Evicts the page that was least recently accessed. Maintains a timestamp for each page access. Works well for workloads with strong temporal locality. |
| 🔵 **CLOCK (Second-Chance Algorithm)** | Uses a circular buffer and reference bit per frame. The clock hand gives a “second chance” to pages with ref-bit = 1 before eviction. Efficient approximation of LRU. |
| 🟢 **ARC (Adaptive Replacement Cache)** | Balances between recency (T1) and frequency (T2) using adaptive parameter `p`. Maintains ghost lists (B1, B2) to learn from past evictions and adapt dynamically. |

---

## 🧮 Color Codes (used in terminal output)

| 🎨 **Color** | 💻 **ANSI Code** | 🧠 **Meaning** |
|--------------|------------------|----------------|
| 🟢 **Green** | `\033[0;32m` | Cache **Hit** |
| 🔴 **Red** | `\033[0;31m` | Cache **Miss** |
| 🟠 **Orange** | `\033[0;33m` | Labels / Highlights |
| ⚪ **Reset** | `\033[0m` | Reset terminal color |

---


🧪 Modify / Extend

You can easily extend the simulator:

Add new access patterns to page_caches_simulator.c

Change frame count (MAX_FRAMES in page_caches.h)

Add new algorithms or modify policies

🚀 Future Enhancements

Add command-line arguments for custom input arrays or frame count

Support CSV export of results for plotting

Implement graphical visualization of cache states

Benchmark ARC parameter tuning (p) dynamically

📜 License

This project is open for educational and research use.
Feel free to fork and improve it!

👨‍💻 Author

Almas-zayn

📧 For suggestions or collaboration — feel free to reach out!


