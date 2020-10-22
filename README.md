# Assembly-type code translator and SPU-executor

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0ef56e0968ad4689a264716b9becbd09)](https://app.codacy.com/gh/AlexRoar/SPUAsm?utm_source=github.com&utm_medium=referral&utm_content=AlexRoar/SPUAsm&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/alexroar/spuasm/badge)](https://www.codefactor.io/repository/github/alexroar/spuasm)

## Description
This project implements code translations to uneven bytecode, disassembly tool for generated bytecode, bytecode executor (Soft Processor Unit).

In addition, I implemented code analyser that checks for syntax mistakes. Analyser output is in clang format, so most IDEs highlight wrong expressions and provide descriptions of errors as well as possible solutions when possible.

<img style="max-height: 100px" src="https://github.com/AlexRoar/SPUAsm/raw/main/Images/errors.png">

During the translation,  .lst file is generated. It provides information about how bytecode was generated and at what offset in binary file every command is located.

<img style="max-height: 250px" src="https://github.com/AlexRoar/SPUAsm/raw/main/Images/generalview.png">

[**Docs**](https://alexroar.github.io/SPUAsm/html/)

## Installation

Enter project's directory and execute:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```
Three files will be created: 
-  **SPU** - Soft Processor Unit, executes created programs 
-  **SPUAsm** - translates source file (.spus) to binary file (.spub) that can be executed by SPU
-  **SPUDisAsm** - disassembly for generated binary files

## Usage

**SPUAsm**
```bash
$ SPUAsm <source file>
        -E                          - generate preprocessed file
        --verbose                   - output assembly debug information
        --lst <filename.lst>        - listing file of generated code (assembly.lst by default) 
        --input <filename.spus>     - source file (can be specified without --input)
        --output <filename.spub>    - binary assembled file
        -h, --help                  - show help message
```

**SPUDisAsm**
```bash
$ SPUDisAsm <binary file>
        --verbose                   - output assembly debug information
        --input <filename.spub>     - binary assembled file
        --output <filename.spus>    - source file (if not specified, stdout selected)
        -h, --help                  - show help message
```

**SPU**
```bash
$ SPU <binary file>
        --verbose                   - output assembly debug information
        --input <filename.spub>     - binary assembled file
        --output <filename.spus>    - source file (if not specified, stdout selected)
        -h, --help                  - show help message
```

## Algorithm description

Binary generation can be splitted to several parts:

- Cleanup
- Analysis
- Final cleanup
- Translation
- Final checks

If process fails on any part, the nest parts are not executed.

### Cleanup
Just double whitespaces, trailing/leading whitespaces removed. Operations that does not change code structure, lines number etc.

### Analysis
Analyses code for syntax errors, builds temporary code to calculate labels offsets. Prints errors descriptions in clang format.

### Final cleanup
All unnecessary indent symbols removed (comments, blank lines, unneded whitespaces). Code structure will be altered, line numbers are not preserved. 

### Translation
Code is translated using labels table generated on analysis step. At this point, all errors must be catched by analysis, but still some can make thir way to this point. In this case, generation will fail, dumping wrong instruction and its number.

### Final checks
Check that all operations completed correctly, that labels table is complete and not redundant.


## Examples

All examples are available [in this dir](https://github.com/AlexRoar/SPUAsm/tree/main/Examples/SPUAsm/SPUAsm).

### Squares of first n numbers

```asm
;
; Squares
;

in rbx  ; rbx as counter

push 0
pop rax

loop:
dec rbx  ; decrease counter

; Calculating square
push rax
push rax
mul
out

; Prepare for the next loop
pop
inc rax

jm mondayOnly ; exit if it is monday

; Insert conditional jump operands
push 0
push rbx

jne loop

mondayOnly:
```


### Square equation solutions

```asm
;
; Data input
; (a, b, c)
;
in      rax
in      rbx
in      rcx

;
; D calculation
;
push    rbx
push    2
pow

push    4
push    rax
mul
push    rcx
mul
sub
sqrt
pop     rdx


;
; First x
;
clear
push    -1
push    rbx
mul
push    rdx
sub
push    2
div
push    rax
div
pop     rcx

;
; Second x
;
clear
push    -1
push    rbx
mul
push    rdx
add
push    2
div
push    rax
div
pop     rax

;
; Output
;
out     rax
out     rcx

```

## Links

- [SPUAsm code](https://github.com/AlexRoar/SPUAsm/blob/main/SoftProcessorUnit/Assembly/SPUAssembly.cpp)
- [SPUDisAsm code](https://github.com/AlexRoar/SPUAsm/blob/main/SoftProcessorUnit/Disassembly/SPUDisAssembly.cpp)
- [SPU code](https://github.com/AlexRoar/SPUAsm/blob/main/SoftProcessorUnit/SPU/SPU.cpp)
- [Examples](https://github.com/AlexRoar/SPUAsm/tree/main/Examples/SPUAsm/SPUAsm)
