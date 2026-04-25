# Superposition Theorem Verifier

## 📌 Project Overview
This repository contains a C-based verifier for the **Superposition Theorem**, developed for the Basic Electrical Engineering (BEE) course. The program calculates individual source contributions and verifies the theorem against the total circuit response.

## ⚡ Circuit Topology
The verifier is designed for a bridge-like T-network:
* **Sources:** Two Voltage Sources ($V_1$ and $V_2$)
* **Resistors:** Three Resistors ($R_1, R_2, R_3$) in a common node configuration.

## 📂 File Structure
* `main.c`: The core logic for circuit analysis, power calculation, and theorem verification.
* `BEE_CEP_Report_Group01.docx`: The formal project report containing manual calculations and circuit diagrams.

## 🛠 How to Run
1. Ensure you have a C compiler (like GCC) installed.
2. Compile the file: 
   `gcc main.c -o verifier -lm`
3. Run the program:
   `./verifier`

## 📊 Features
* Calculates Nodal Voltage ($V_a$) and branch currents.
* Performs **Power Analysis** to verify the Law of Conservation of Energy.
* Provides a step-by-step breakdown of each source's effect.
* ## 📊 Program Execution Output
Below is the screenshot of the C program successfully verifying the Superposition Theorem:

![Output Verification](Output%20verifier.png)
