# CSC 308 Operating Systems Practical Assignments

## Student Information

- **Name:** Achusi Chukwuebuka Divine
- **Matric Number:** 2023934013
- **Department:** Software Engineering
- **Course:** Operating Systems
- **Course Code:** CSC 308
- **Institution:** Nnamdi Azikiwe University

---

## Description

This repository contains the practical assignments completed for the CSC 308 Operating Systems course. The programs demonstrate synchronization and inter-process communication concepts using the C programming language.

## Practical Files

### 1. mutex_demo.c
Demonstrates the use of mutex locks to synchronize multiple threads and safely access a shared counter.

### 2. producer_consumer.c
Implements the Producer-Consumer problem using semaphores and mutexes to coordinate access to a shared buffer.

### 3. semaphore_demo.c
Illustrates thread synchronization using POSIX semaphores to protect a shared resource.

### 4. shared_memory.c
Demonstrates inter-process communication (IPC) using shared memory and semaphores, where a parent process writes data and a child process reads it.

---

## Programming Language

- C

## Development Environment

- Linux
- GCC Compiler
- POSIX Threads (pthreads)
- System V Shared Memory
- POSIX Semaphores

---

## Compilation

```bash
gcc filename.c -o output -pthread
```

Example:

```bash
gcc mutex_demo.c -o mutex_demo -pthread
```

## Running the Program

```bash
./output
```

Example:

```bash
./mutex_demo
```
