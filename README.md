# Emulator

# Emulator Program

## Overview
This program is an emulator that executes instructions from a binary file. It simulates a machine with a basic instruction set architecture (ISA), registers, and memory. The emulator can trace the execution of the program, show the ISA, reset registers, dump memory, and display memory read/write operations.

## Author Information
- **Name**: Chaitanya Saagar
- **Roll Number**: 2301CS77

## Features
1. **Instruction Tracing**: Displays the execution flow, including program counter (PC), stack pointer (SP), and general-purpose registers `A` and `B`.
2. **Instruction Set Architecture (ISA)**: Shows the available opcodes and their meanings.
3. **Register Reset**: Resets all registers to their initial values.
4. **Memory Dumps**:
   - Before execution
   - After execution
5. **Memory Operations**:
   - Displays all memory read operations.
   - Displays all memory write operations.
6. **Interactive Menu**: Provides an easy-to-use interface to explore the features.

## ISA (Instruction Set Architecture)
The following table lists the available instructions:

| Opcode | Mnemonic | Operand        |
|--------|----------|----------------|
| 0      | `ldc`    | value          |
| 1      | `adc`    | value          |
| 2      | `ldl`    | value          |
| 3      | `stl`    | value          |
| 4      | `ldnl`   | value          |
| 5      | `stnl`   | value          |
| 6      | `add`    |                |
| 7      | `sub`    |                |
| 8      | `shl`    |                |
| 9      | `shr`    |                |
| 10     | `adj`    | value          |
| 11     | `a2sp`   |                |
| 12     | `sp2a`   |                |
| 13     | `call`   | offset         |
| 14     | `return` |                |
| 15     | `brz`    | offset         |
| 16     | `brlz`   | offset         |
| 17     | `br`     | offset         |
| 18     | `halt`   |                |

## How to Use
1. **Compile the Program**:
   ```bash
   g++ -o emulator emu.cpp
   ```

2. **Run the Emulator**:
   ```bash
   ./emulator
   ```

3. **Provide Input File**: Enter the file name (with extension) containing the binary instructions when prompted.

4. **Choose Menu Options**:
   - **1**: Get trace of execution.
   - **2**: Display ISA.
   - **3**: Reset registers.
   - **4**: Memory dump before execution.
   - **5**: Memory dump after execution.
   - **6**: Show memory reads.
   - **7**: Show memory writes.
   - **8 or greater**: Exit the program.

## Code Structure
- **`dechex` Function**: Converts a decimal value to its hexadecimal representation.
- **`trace` Function**: Executes the instructions from the binary file and provides a trace.
- **`showisa` Function**: Displays the instruction set architecture.
- **Main Function**:
  - Reads the binary file and stores machine codes.
  - Displays an interactive menu to perform various tasks.

## Memory and Registers
- **Memory**: An array (`mem`) to store memory contents.
- **Registers**:
  - `PC` (Program Counter): Tracks the current instruction.
  - `SP` (Stack Pointer): Points to the stack location.
  - `A` and `B`: General-purpose registers.

## Notes
- Ensure the input file contains valid binary instructions compatible with the defined ISA.
- The program stops execution if a segmentation fault or other errors are detected.

## Example Input
Binary file containing machine instructions:
```binary
00000000 01020304 0A0B0C0D
...
```

## Example Output
```
Enter the file name (with extension) to run the emulator:
input.o

MENU
1: Get trace
2: Display ISA(Instruction set architecture)
3: Reset registers
4: Memory dump before execution
5: Memory dump after execution
6: Show memory reads
7: Show memory writes
8 or greater: Exit

Enter your choice: 1
PC= 00000001 SP= 00000000 A= 00000004 B= 00000003
...
Total instructions ran are
10
```

