# NEON glossary

## How to read the names

Every intrinsic follows the pattern `v` + operation + modifiers + `_` + type:

| Part | Meaning | Example |
|---|---|---|
| `v` | vector intrinsic | all of them |
| `q` | full 128-bit register; without it, a 64-bit half | `vaddq` vs `vadd` |
| `v` before `q` | across the vector: reduces all lanes to one scalar | `vaddvq`, `vmaxvq` |
| `l` | long: the result has lanes twice as wide | `vaddlvq`, `vpaddlq` |
| `p` | pairwise: combines neighbouring lanes | `vpaddlq`, `vpadalq` |
| `a` | accumulate: adds into an existing register | `vpadalq` |
| `_n` | the input is a scalar, not a vector | `vdupq_n_s32` |
| `_s32`, `_u32`, `_s64` | lane type: signed/unsigned, bit width | `vceqq_s32` |

## The intrinsics used so far 

| Intrinsic | Read as | What it does | Instruction |
|---|---|---|---|
| `vdupq_n_s32(x)` | duplicate scalar into 4 × int32 | `[x, x, x, x]` | `DUP` |
| `vdupq_n_s64(x)` | duplicate scalar into 2 × int64 | `[x, x]` | `DUP` |
| `vld1q_s32(p)` | load 1 structure, 4 × int32 | `[p[0], p[1], p[2], p[3]]` | `LD1` (often printed `LDR q`) |
| `vaddq_s32(a, b)` | add, 4 × int32 | lane-wise `a + b`; wraps on overflow | `ADD` |
| `vaddq_s64(a, b)` | add, 2 × int64 | lane-wise `a + b` | `ADD` |
| `vaddvq_s32(a)` | add across vector | `a0 + a1 + a2 + a3`, as int32 | `ADDV` |
| `vaddlvq_s32(a)` | add long across vector | same sum, but as int64 | `SADDLV` |
| `vaddvq_s64(a)` | add across vector, 2 × int64 | `a0 + a1` | `ADDP` |
| `vpaddlq_s32(a)` | pairwise add long | `[a0+a1, a2+a3]` as int64 | `SADDLP` |
| `vpadalq_s32(acc, a)` | pairwise add and accumulate long | `acc + [a0+a1, a2+a3]` as int64 | `SADALP` |
| `vceqq_s32(a, b)` | compare equal | lane = `0xFFFFFFFF` if `a == b`, else `0` | `CMEQ` |
| `vmaxvq_u32(m)` | max across vector | largest lane; nonzero means "any lane set" | `UMAXV` |

## References

[1] Arm Ltd., "Arm Intrinsics," Arm Developer. Accessed: Nov. 24, 2026. [Online]. Available: https://developer.arm.com/architectures/instruction-sets/intrinsics
