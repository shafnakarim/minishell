*This project has been created as part of the 42 curriculum by srayees, jaa-s.*

# Minishell Project

## Description

Minishell is a project from the 42 curriculum that consists of creating a simplified Unix shell written in C.

The goal of this project is to understand how a shell works internally by implementing command parsing, process creation, execution, environment management, file descriptor handling, pipes, redirections, and signal management.

Minishell provides a command-line interface similar to Bash, allowing users to execute commands, use built-in commands, manage environment variables, handle input/output redirections, and connect commands using pipelines.

This project focuses on understanding low-level system programming concepts such as:

* Process creation using `fork()`
* Program execution using `execve()`
* Process synchronization using `waitpid()`
* File descriptor management
* Pipes and redirections
* Signal handling
* Memory management

# Project Structure

```
minishell-42/
|
├── include/                 # Header files
│   ├── minishell.h          # Main header with data structures
│   ├── parser.h             # Parser/lexer declarations
│   ├── executor.h           # Executor declarations
│   ├── builtins.h           # Built-in commands declarations
│   ├── utils.h              # Utility functions declarations
│   └── signals.h            # Signal handling declarations
|
├── src/                     # Source code
│   ├── lexer/               # Lexical analysis
│   │   ├── lexer.c          # Main tokenizer
│   │   ├── lexer_init.c     # Tokenizer initialization
│   │   ├── token.c          # Token management
│   │   ├── token_utils.c    # Token utilities
│   │   └── quote_handler.c  # Quote processing
|
│   ├── parser/              # Syntax analysis
│   │   ├── parser_main.c
│   │   ├── parser_commands.c
│   │   ├── parser_redirections.c
│   │   ├── parser_pipeline.c
│   │   ├── parser_memory.c
│   │   └── error.c
|
│   ├── executor/            # Command execution
│   │   └── executor.c
|
│   ├── builtins/            # Built-in commands
│   │   ├── ft_echo.c
│   │   ├── ft_cd.c
│   │   ├── ft_pwd.c
│   │   ├── ft_export.c
│   │   ├── ft_unset.c
│   │   ├── ft_env.c
│   │   └── ft_exit.c
|
│   └── utils/               # Utility functions
│       ├── utils.c
│       ├── signals.c
│       └── my_prompt.c
|
├── libft/                   # Custom C library
├── obj/                     # Generated object files
├── Makefile                 # Build configuration
├── main.c                   # Program entry point
└── README.md
```

# Features

## Command Processing

* Lexical analysis:

  * Tokenizes input into words, operators, and redirections.
  * Handles quotes and special characters.

* Parsing:

  * Builds command structures.
  * Validates command syntax.

## Command Execution

Supported features:

* Execute external commands
* Search commands using the `PATH` environment variable
* Pass arguments
* Handle command return values using `$?`

## Built-in Commands

Implemented built-ins:

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

## Redirections

Supported:

* Input redirection:

```
<
```

* Output redirection:

```
>
```

* Append mode:

```
>>
```

* Here-document:

```
<<
```

## Pipes

Supports pipelines between commands:

Example:

```bash
cat file.txt | grep hello | wc -l
```

## Signal Handling

Implemented handling for:

* `SIGINT` (Ctrl+C)

  * Clears the current input.
  * Displays a new prompt.

* `SIGQUIT` (Ctrl+)

  * Ignored by the interactive shell.
  * Correctly handled by child processes.

* EOF (Ctrl+D)

  * Exits minishell when used on an empty prompt.

# Instructions

## Compilation

Clone the repository and enter the project directory:

```bash
git clone <repository_url>
cd minishell-42
```

Compile the project:

```bash
make
```

Additional Make commands:

```bash
make clean
make fclean
make re
```

## Execution

Run minishell:

```bash
./minishell
```

Example:

```bash
🤖 minishell➤ ls -la

🤖 minishell➤ echo Hello World

🤖 minishell➤ cat < input.txt > output.txt

🤖 minishell➤ ls | grep minishell
```

# Architecture

## Lexer (Tokenization)

The lexer converts user input into tokens.

Responsibilities:

* Splitting commands into words.
* Detecting operators.
* Handling quotes.
* Creating token streams for the parser.

## Parser (Syntax Analysis)

The parser converts tokens into executable command structures.

Main responsibilities:

* Command creation.
* Argument handling.
* Redirection processing.
* Pipeline validation.
* Syntax error detection.

## Executor (Command Execution)

The executor handles:

* Process creation.
* Pipe setup.
* Redirection handling.
* External command execution.
* Built-in command execution.
* Process cleanup.

# Error Handling

Minishell provides error handling for:

* Invalid syntax.
* Unclosed quotes.
* Invalid pipes.
* Missing files.
* Permission errors.
* Command not found.

# Memory Management

The project includes:

* Cleanup functions for allocated memory.
* Resource management for files and processes.
* Memory checks using Valgrind.

Testing is performed to ensure there are no invalid memory accesses or leaks during normal execution.

# Resources

## Documentation

* Bash Reference Manual:
  https://www.gnu.org/software/bash/manual/

* Linux Manual Pages:
  https://man7.org/linux/man-pages/

* POSIX Shell Command Language:
  https://pubs.opengroup.org/onlinepubs/9699919799/

* GNU Readline Documentation:
  https://tiswww.case.edu/php/chet/readline/rltop.html

## AI Usage

AI tools were used as a support resource during the development of this project.

AI was used for:

* Understanding Unix shell concepts and system calls.
* Learning about process management (`fork`, `execve`, `waitpid`).
* Debugging compilation errors and runtime issues.
* Reviewing C code logic and improving implementation understanding.
* Creating additional test cases for:

  * Pipes.
  * Redirections.
  * Signals.
  * Exit status handling.
  * Memory testing.

AI was not used to generate the complete project implementation. The architecture, design decisions, coding, integration, and debugging were performed by the project developers.

# Testing

The project was tested through:

* Manual comparison with Bash behavior.
* Different command combinations.
* Pipe and redirection tests.
* Signal handling tests.
* Invalid input tests.
* Valgrind memory checks.

Example:

```bash
valgrind --leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--track-fds=yes \
./minishell
```

