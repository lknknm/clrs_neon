# Vectorisable algorithms

Algorithms from *Introduction to Algorithms* (CLRS), 4th edition, that suit NEON SIMD. Chapter numbers refer to that edition.

## Strong candidates

| Ch. | Algorithm | NEON idea | Status |
|---|---|---|---|
| 2 | [Linear search](../include/clrs/linear_search.hxx) | Compare 4 at once, early exit on mask | done (~6.35×) |
| 2 | Insertion sort | Replace small sorts with a [sorting network](#sorting-networks) | next ideas |
| 2 | Merge (merge sort) | [Bitonic merge network](#sorting-networks) | |
| 4 | Matrix multiplication | Broadcast + FMA, register blocking | |
| 9 | Simultaneous min/max | `vminq`/`vmaxq` with several accumulators, like the [`sum` port](../include/clrs/sum.hxx) | |
| 18 | B-tree node search | Compare all keys in a node, count matches | |
| 23 | Floyd–Warshall | `min(d[i][j], d[i][k] + d[k][j])` with a broadcast | |
| 28 | LUP decomposition | Row updates are vector multiply-adds | |
| 30 | FFT | Complex butterflies with FMA | |
| 32 | Naive string matching | Compare first and last byte, 16 positions at once | |
| 33 | k-means | Distance computations | |

### Sorting networks

Background for the insertion sort and merge rows. The numbers are the entries in the [README references](../README.md#references).

- Knuth, TAOCP vol. 3, §5.3.4 "Networks for sorting" [4]: the theory of sorting networks.
- Wikipedia, "Sorting network" [5]: lists the optimal networks for small *n*.
- Inoue & Taura, VLDB 2015 [6]: the full pipeline of sorting columns, transposing, then merging.

## Partial: only part of the algorithm vectorises

| Ch. | Algorithm | What vectorises |
|---|---|---|
| 2 | Binary search | Little as written; a SIMD-friendly layout helps |
| 6 | Heaps | A 4-ary heap: find the largest of 4 children at once |
| 7 | Quicksort partition | Partitioning, but it needs table-driven shuffles (hard) |
| 8 | Counting / radix sort | Histograms and prefix sums; not the scatter |
| 9 | Randomized select | Reuses the quicksort partition |
| 11 | Hash tables | Probing 16 slots at once (SwissTable-style) |
| 14 | LCS / edit distance | Anti-diagonals, or many sequence pairs at once |
| 21–22 | Prim / Dijkstra (dense) | Finding the minimum key |
