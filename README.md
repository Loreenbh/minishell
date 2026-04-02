# Minishell (42) – Custom Shell Implementation

Implementation of a simple shell in C as part of the 42 curriculum.  
The project focuses on **process management, parsing, and Unix signals**.

## Skills Demonstrated

- Linux command line  
- Process creation and management (`fork`, `execve`)  
- Signal handling (`SIGINT`, `SIGQUIT`)  
- Parsing and handling of command-line inputs  
- Redirections (`>`, `<`, `>>`) and pipes (`|`)  

## Project Overview

Minishell is a simplified version of a Unix shell that supports:

1. Executing commands with arguments  
2. Handling built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)  
3. Redirections (`>`, `>>`, `<`)  
4. Pipes (`|`) to chain commands  
5. Signal handling for proper termination and interruption  

## Getting Started

Clone the repository:

```bash
git clone https://github.com/Loreenbh/minishell.git
```
Build the project and run the shell:
```bash
make
./minihell
```
