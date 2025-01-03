# LMC

---

Author : Bredariol Francesco SM3201379

This LMC is the Python Project for the "Programmazione Avanzata e Parallela"'s final exam (year 2024/2025).

---

This project aims to implement both the assembler and the architecture of the so called "Little Man Computer". The LMC is well explained in the Exam's PDF. Here is explained the main usage.

1. Use *py main.py* to run the main
    **Note**
    The main has 2 optional parameters:
    a. ***verbose*** : Boolean that tells if using verbose mode
    b. ***path*** : String representing where the assembly code is located
    c. ***input_q*** : List of int representing the input queue for the LMC (passed by string of integers comma separated)

It is important to have the input queue that does not conflict with the assembly code to obtain logic results. Results are stored in the output queue of the LMC and can be seen by activating verbose mode. Programmer has the responsability to know this a priori.