# Pre-test 02

## Objective

1. Design an LLVM module as input (`.ll`).
2. Implement a C++ tool using LLVM API to parse that module.
3. Print all functions found in the module.

## Files

- `input.ll`: LLVM IR module used as parser input.
- `func_lister.cpp`: LLVM-based parser and function lister.

## Build

```bash
clang++ -std=c++17 func_lister.cpp -o func_lister \
  $(llvm-config --cxxflags --ldflags --libs core irreader support --system-libs)
```

## Run

```bash
./func_lister input.ll
```

## Expected Output

```text
Functions found in module 'input.ll':
 [decl] i32 @puts(ptr)
 [decl] double @sqrt(double)
 [def] i32 @add(i32 %a, i32 %b)
 [def] i32 @mul(i32 %a, i32 %b)
 [def] double @sqrt_f64(double %x)
 [def] void @hello()
 [def] i32 @abs(i32 %x)
 [def] i32 @main()
```
