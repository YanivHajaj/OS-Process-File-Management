# Student Code Verifier and Calculator

This repository contains two main projects: a program checker for verifying the outputs of other students' programs and a calculator application, both developed in C and designed to run on Linux systems. The program checker extensively uses Linux system calls and processes to manage and automate the verification process, whereas the calculator project provides an interface for performing arithmetic operations.

## ProgramChecker

### Overview
`ProgramChecker` is a tool developed to assess the correctness of programs submitted by students, ensuring they meet predefined output criteria. It leverages the Linux environment to fork processes, manage permissions, and handle files efficiently.

### Features
- **Automated File Comparison**: Automatically compares the output of students' programs with expected outputs using system-level operations.
- **Process Control**: Utilizes Linux process management to handle multiple student programs simultaneously.
- **Detailed Error Logging**: Implements comprehensive error checking and logging to manage file and process-related errors effectively.

### Getting Started
- Navigate to the directory containing the program files:
  ```
  cd Desktop/OS
  ```
- Compile the verifier program using GCC:
  ```
  gcc comp.c -o comp.out
  ```
- Execute the program with the required file paths:
  ```
  ./comp.out /u/e2020/hajajya/Desktop/OS/1.txt /u/e2020/hajajya/Desktop/OS/2.txt
  ```

### Paths and Configuration
- The paths provided in the compilation and execution instructions are specific to my development environment. If you wish to use this tool in your environment, you will need to adjust the file paths according to where your files are located.

### Advanced Usage
- To handle multiple student submissions, configure the paths in `confFile.txt`:
  ```
  ./ex2.out /u/e2020/hajajya/Desktop/OS/confFile.txt
  ```
- The program assumes `main.exe` exists due to prior compilation as per the instructions.

## CalculatorBuilder

### Overview
`CalculatorBuilder` consists of a straightforward calculator application capable of basic arithmetic operations such as addition, subtraction, multiplication, and division, showcasing the use of command line arguments and basic I/O.

### Features
- **Basic Arithmetic Operations**: Supports the four fundamental arithmetic operations.
- **Command-Line Interface**: Operates entirely through the command line for input and output, enhancing its usability in educational settings.

### Getting Started
- Navigate to the project directory:
  ```
  cd Desktop/OSEX2
  ```
- Compile and run the server component:
  ```
  gcc ex2_srv.c -o ex2_srv.out
  ./ex2_srv.out &
  ```
- Compile and execute the client component, specifying operations and operands:
  ```
  gcc ex2_client.c -o ex2_client.out
  ./ex2_client.out <SPID> 30 1 40
  ```

### Paths and Configuration
- Similar to the `ProgramChecker`, the paths used in this project are specific to my setup. Ensure to modify the paths in the command lines to reflect the directories and files in your environment.

## Technologies Used
- **C Programming**: Utilized for both projects to interact directly with Linux system calls.
- **Linux**: Provides a robust environment for process and file management.
- **GCC**: Used to compile the source code into executable programs.

### Process Management
The core functionality of the `ProgramChecker` revolves around creating and managing processes using the fork system call. This creates a parent-child (father-son) process hierarchy, where the parent process forks multiple child processes to handle concurrent execution of student programs, thereby enabling efficient multitasking and resource management within the system.
