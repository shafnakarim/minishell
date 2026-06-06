# Minishell Project

A simple shell implementation in C, mimicking basic bash functionality.

## Project Structure

```
minishell-42/
|
├── include/                 # Header files
│   ├── minishell.h         # Main header with data structures
│   ├── parser.h            # Parser/lexer declarations
│   ├── executor.h          # Executor declarations
│   ├── builtins.h          # Built-in commands declarations
│   ├── utils.h             # Utility functions declarations
│   └── signals.h           # Signal handling declarations
├── src/                     # Source code
│   ├── lexer/              # Lexical analysis
│   │   ├── lexer.c         # Main tokenizer
│   │   ├── lexer_init.c    # Tokenizer initialization
│   │   ├── token.c         # Token management
│   │   ├── token_utils.c   # Token utilities
│   │   └── quote_handler.c # Quote processing
│   ├── parser/             # Syntax analysis
│   │   ├── parser_main.c       # Main parsing entry point
│   │   ├── parser_commands.c   # Command building functions
│   │   ├── parser_redirections.c # Redirection handling
│   │   ├── parser_pipeline.c   # Pipeline validation and building
│   │   ├── parser_memory.c     # Memory management for parser
│   │   └── error.c             # Error handling
│   ├── executor/           # Command execution
│   │   └── executor.c      # Process execution and pipes
│   ├── builtins/           # Built-in commands
│   │   ├── ft_echo.c       # echo command
│   │   ├── ft_cd.c         # cd command
│   │   ├── ft_pwd.c        # pwd command
│   │   ├── ft_export.c     # export command
│   │   ├── ft_unset.c      # unset command
│   │   ├── ft_env.c        # env command
│   │   └── ft_exit.c       # exit command
│   └── utils/              # Utility functions
│       ├── utils.c         # Environment and string utilities
│       ├── signals.c       # Signal handling
│       └── my_prompt.c     # Prompt display
├── libft/                   # Custom C library
├── obj/                     # Object files (generated)
├── Makefile                 # Build configuration
├── main.c                   # Program entry point
└── README.md               # This file
```

## Features

- **Lexical Analysis**: Tokenizes input into words, operators, and redirections
- **Parsing**: Builds command structures with proper syntax checking
- **Pipeline Support**: Handles command pipes (`|`)
- **Redirections**: Input (`<`, `<<`) and output (`>`, `>>`) redirections
- **Built-in Commands**: echo, cd, pwd, export, unset, env, exit
- **Signal Handling**: Proper handling of Ctrl+C, Ctrl+D, Ctrl+\
- **Memory Management**: Complete cleanup with no memory leaks

## Building

```bash
make          # Build the project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
```

## Usage

```bash
./minishell
🤖 minishell➤ ls -la | grep "minishell" > output.txt
🤖 minishell➤ cat < input.txt | sort | uniq
🤖 minishell➤ export PATH="/usr/bin:$PATH"
🤖 minishell➤ exit
```

## Architecture

### Lexer (Tokenization)
- Splits input into tokens (words, pipes, redirections)
- Handles quoted strings and escape sequences
- Returns token stream for parsing

### Parser (Syntax Analysis)
- **parser_main.c**: Main entry point with `parse_command()` function (1 function)
- **parser_commands.c**: Command building logic - token counting, command initialization, and simple command building (3 functions)
- **parser_redirections.c**: Input/output redirection handling and validation (3 functions)
- **parser_pipeline.c**: Pipeline syntax validation and command chain building (2 functions)
- **parser_memory.c**: Complete memory cleanup for all parser structures (4 functions)
- **error.c**: Syntax error reporting (1 function)

### Executor (Command Execution)
- Sets up pipes and redirections
- Executes built-in commands
- Forks processes for external commands
- Manages process cleanup

## Error Handling

The shell provides meaningful error messages for:
- Syntax errors (unclosed quotes, invalid pipes)
- File access errors (permission denied, file not found)
- Command execution errors (command not found)

## Memory Management

- Comprehensive cleanup functions for all data structures
- No memory leaks on normal or error conditions
- Proper resource management for files and processes
