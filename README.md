# Analysis and Synthesis of Algorithms (ASA) Projects

This repository contains three academic projects developed for an **Analysis and Synthesis of Algorithms (ASA)** course. The projects cover advanced algorithmic paradigms including **Dynamic Programming**, **Graph Theory**, and **Linear Programming**.

Each project folder includes:
- Detailed academic reports (*relatórios*)
- Comprehensive test cases
- Performance graphs to validate efficiency and correctness

---

## Authors

- André Sá  
- Joana Melo  

---

## Repository Structure

| Folder              | Contents                                                                 |
|--------------------|-------------------------------------------------------------------------|
| `ASA-FirstProject` | Project 1: C++ source code, problem statement, report, test generator   |
| `ASA-SecondProject`| Project 2: C++ source code, problem statement, report, test generator   |
| `ASA-ThirdProject` | Project 3: Python source code, problem statement, report, test generator|

---

## Projects Overview

### Project 1: Amino Acid Chain Optimization

| Attribute            | Details                         |
|----------------------|---------------------------------|
| Language             | C++                             |
| Algorithmic Concept  | Dynamic Programming (DP)        |

This project calculates the **maximum potential energy** released by removing amino acids from a chain.

- Uses an affinity matrix based on biochemical classes:
  - Polar
  - Non-Polar
  - Acid
  - Base
- Applies dynamic programming over sub-intervals
- Ensures optimal removal sequence
- Outputs:
  - Maximum energy score
  - Lexicographically ordered sequence using a binary tree structure

---

### Project 2: Graph Path Distribution

| Attribute            | Details                                      |
|----------------------|----------------------------------------------|
| Language             | C++                                          |
| Algorithmic Concept  | Graph Theory & Directed Acyclic Graphs (DAGs)|

This project computes paths in a **Directed Acyclic Graph (DAG)**.

- Performs topological sorting
- Calculates number of paths between nodes
- Distributes paths among trucks (from *m1* to *m2*)
- Uses modulo arithmetic for distribution

**Output:**
- Assigned trucks
- Origin-destination pairs
- Properly sorted results

---

### Project 3: Tournament Winner Prediction

| Attribute            | Details                  |
|----------------------|--------------------------|
| Language             | Python                   |
| Algorithmic Concept  | Linear Programming (LP)  |

This project determines the **minimum number of wins** required for a team to win a tournament.

- Uses the `pulp` library for Linear Programming
- Considers:
  - Current standings
  - Remaining matches
- Optimizes match outcomes (wins, losses, draws)

**Output:**
- Minimum wins required
- `-1` if victory is mathematically impossible

---

## Compilation and Execution

### Project 1 & 2 (C++)

Compile with `g++`:

### Project 1

g++ -O3 -Wall -std=c++11 Project1.cpp -o p1
./p1 < input.txt

### Project 2

g++ -O3 -Wall -std=c++11 Project2.cpp -o p2
./p2 < input.txt

--- 

### Project 3 (Python)

### Install dependencies:

pip install pulp

### Run:
python3 Project3.py < input.txt

---

#### Additional Documentation

Detailed mathematical proofs, complexity analysis, and performance graphs are available in the respective Relatório (Report) PDF files inside each project folder.
This will render cleanly on GitHub with proper “windows” (code blocks).
