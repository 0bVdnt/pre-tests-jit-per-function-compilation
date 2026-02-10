# WasmEdge LFX Mentorship Pre-tests - JIT Per-function Compilation

This repository contains my submission materials for the **WasmEdge LFX Mentorship pre-test** for the project:

**Enable JIT mode support for per-function compilation**  
https://github.com/WasmEdge/WasmEdge/issues/4516

## Directory Structure

```
Pre-test-01/
  README.md
Pre-test-02/
  input.ll
  func_lister.cpp
```

---

## Pre-test 01

**Location:** `Pre-test-01/README.md`

Contains:

- The computed final value for the given C++ loop snippet
- A step-by-step execution trace

---

## Pre-test 02

**Goal:** Prove basic understanding of LLVM by:

1. Designing an LLVM IR module (`.ll`) as input
2. Implementing a C++ tool using LLVM APIs that parses the module and prints all functions

### Files

- **LLVM module input:** `Pre-test-02/input.ll`
- **LLVM API tool:** `Pre-test-02/func_lister.cpp`

### What the tool prints

For each function in the module, it prints:

- Whether it is a **declaration** or a **definition**
- The **return type**
- The **function name**
- The **argument types** (and argument names when present)
- `...` for varargs

---

## Requirements

- LLVM installed with development headers and `llvm-config` available in PATH.
- A C++ compiler (e.g., `clang++` or `g++`).

### LLVM Version Note

The IR uses opaque pointers (`ptr`). This is the default in modern LLVM releases (LLVM 15+).  
If you are using an older LLVM toolchain that does not support `ptr`, you may need to replace `ptr` with `i8*` in `input.ll`.

---

## Build & Run (Pre-test 02)

From the repository root:

```bash
clang++ -std=c++17 Pre-test-02/func_lister.cpp -o Pre-test-02/func_lister \
  $(llvm-config --cxxflags --ldflags --libs core irreader support --system-libs)

./Pre-test-02/func_lister Pre-test-02/input.ll
```

### Example Output

```text
Functions found in module 'Pre-test-02/input.ll':
 [decl] i32 @puts(ptr)
 [decl] double @sqrt(double)
 [def] i32 @add(i32 %a, i32 %b)
 [def] i32 @mul(i32 %a, i32 %b)
 [def] double @sqrt_f64(double %x)
 [def] void @hello()
 [def] i32 @abs(i32 %x)
 [def] i32 @main()
```

---

## Notes

- The tool uses LLVM’s `SMDiagnostic` for parse errors, which prints helpful messages if the IR is invalid or the file is missing.
- The sample module includes both declarations and definitions, and exercises common IR constructs (calls, branches, phi nodes, and GEP) to make function inventory output meaningful.
