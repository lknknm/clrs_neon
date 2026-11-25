#!/usr/bin/env python3
"""Print a Markdown table of median throughput from a Google Benchmark JSON file.
 
Usage: bench_table.py results.json
Rows are sizes, columns are benchmark families (BM_SumScalar, BM_SumNeon, ...).
The last column compares the last family against the first one.
"""
import json
import sys
from collections import defaultdict
 
 
def main(path: str) -> None:
    with open(path) as f:
        data = json.load(f)
 
    # median items/s, keyed by family then size
    table: dict[str, dict[int, float]] = defaultdict(dict)
    for b in data["benchmarks"]:
        if b.get("aggregate_name") != "median":
            continue
        family, size = b["run_name"].split("/")
        table[family][int(size)] = b["items_per_second"] / 1e9
 
    families = list(table)
    sizes = sorted({s for f in families for s in table[f]})
    base, cand = families[0], families[-1]
 
    ctx = data["context"]
    print(f"Run: {ctx.get('date', '?')}, {ctx.get('num_cpus', '?')} CPUs, "
          f"library build: {ctx.get('library_build_type', '?')}\n")
    print("| Size | " + " | ".join(f"{f} (G el/s)" for f in families)
          + f" | {cand} vs {base} |")
    print("|---:|" + "---:|" * len(families) + "---:|")
    for s in sizes:
        cells = [f"{table[f][s]:.2f}" if s in table[f] else "–" for f in families]
        ratio = table[cand].get(s, 0) / table[base].get(s, float("inf"))
        print(f"| {s} | " + " | ".join(cells) + f" | {ratio:.2f}× |")
 
 
if __name__ == "__main__":
    main(sys.argv[1])
 
