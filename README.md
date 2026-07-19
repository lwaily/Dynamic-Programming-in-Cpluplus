# Dynamic-Programming-in-Cpluplus
This repo shares examples of programs written with the algorithmic-design paradigm called "[Dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming)." It is an approach at optimizing mainly recursive algorithms by transforming a complex problem into a sequence of simpler iterative steps. Many of the examples will be implemented in code that was inspired by classes I've taken.

---

**As Dasgupta et. al explain:**
> Dynamic programming is a very powerful algorithmic paradigm in which a problem is solved by identifying a collection of subproblems and tackling them one by one, smallest first, using the answers to small problems to help figure out larger ones, until the whole lot of them is solved (Algorithms 170).

---

### **There are seven main steps to follow in designing an algorithm with Dynamic Programming:**
1. Define sub-problems and corresponding array (What are the array values supposed to mean?).
2. What are the base cases.
3. Give the recurrence for sub-problems (case analysis).
4. Order the subproblems (*example: For a certain problem, it may be the case that each subproblem is dependent on subproblems of a smaller index so you would order the subproblems from 0 up to n* (see the Fibonacci program as an example)).
5. What is the final output (usually the last computed value)?
6. Put it all together into an iterative algorithm that fills in the array step-by-step (typically pseudo-code).
7. Offer a Correctness Proof and Runtime Analysis.
> (The steps written in this order and wording were mainly taken from Professor Miles Jones' CSE 101 lectures at UCSD.)

---

Most (if not all) of the programs in this repo will be based off of problems from *Algorithms* by Dasgupta, Papadimitriou, and Vazirani.

---

### **List of contents of this repo:**
- Fibonacci Sequence
- Coin Denominations
- Edit Distance
- _Coming soon!_
