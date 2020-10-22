# Транслятор assembly-подобного кода и SPU-исполнитель

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0ef56e0968ad4689a264716b9becbd09)](https://app.codacy.com/gh/AlexRoar/SPUAsm?utm_source=github.com&utm_medium=referral&utm_content=AlexRoar/SPUAsm&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/alexroar/spuasm/badge)](https://www.codefactor.io/repository/github/alexroar/spuasm)

## Описание
В данном проекте реализован транслятор кода в неравномерный байткод, дизассемблер для байткода, исполнитель байткода (Soft Processor Unit).

В дополнение, присутствует анализатор кода, проверяющий синтаксические ошибки и выбрасывающий отчет в clang формате. Поэтому, XCode и другие IDE поддерживающие clang подсвечивают неверные выражения, отображают комментарии.

Во время трансляции генерируется .lst файл, содержащий информацию о трансляции, на каком offset бинарника какая команда и тд. Все доступно в примерах.

<img style="max-height: 250px" src="https://github.com/AlexRoar/SPUAsm/raw/main/Images/generalview.png">
<img style="max-height: 100px" src="https://github.com/AlexRoar/SPUAsm/raw/main/Images/errors.png">

## Ссылки

- [Документация](https://alexroar.github.io/SPUAsm/html/)
- [Основной код транслятора](https://github.com/AlexRoar/SPUAsm/blob/main/SoftProcessorUnit/Assembly/SPUAssembly.cpp)
- [Основной код дизассемблера](https://github.com/AlexRoar/SPUAsm/blob/main/SoftProcessorUnit/Disassembly/SPUDisAssembly.cpp)
- [Основной код SPU](https://github.com/AlexRoar/SPUAsm/blob/main/SoftProcessorUnit/SPU/SPU.cpp)
- [Примеры](https://github.com/AlexRoar/SPUAsm/tree/main/Examples/SPUAsm/SPUAsm)

## Установка

Перейти в директорию проекта и выполнить: 

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```
Создадутся 3 исполняемых файла: 
-  **SPU** - Soft Processor Unit, выполняет созданные программы
-  **SPUAsm** - транслирует программу в файл для исполнения SPU
-  **SPUDisAsm** - дизассемблер файлов сгенерированных SPUAsm

## Использование

**SPUAsm**
```bash
$ SPUAsm <source file>
        -E                          - generate preprocessed file
        --verbose                   - output assembly debug information
        --lst <filename.lst>        - listing file ofgenerated code 
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

## Примеры программ

Квадраты первых n чисел
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
