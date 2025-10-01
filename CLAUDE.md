# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a minishell implementation in C - a simplified bash shell that handles command execution, piping, redirections, heredocs, signal handling, and built-in commands. The project follows the 42 school coding standards (42 header comments, libft usage).

## Build Commands

```bash
# Standard build
make

# Clean object files and libft
make clean

# Full clean (removes executable)
make fclean

# Rebuild from scratch
make re

# Build with AddressSanitizer and UBSan for memory/undefined behavior checks
make asan

# Build with debug symbols and run with valgrind (uses readline.supp for suppressions)
make debug

# Run batch leak checks
make leaks
```

**Note on macOS**: The Makefile automatically detects macOS and adds readline include/lib paths from Homebrew (`/opt/homebrew/opt/readline`).

## Code Architecture

### Three-Phase Execution Flow

1. **Reading** (`src/reader.c`)
   - Uses GNU readline for input with history support
   - Entry point for user input

2. **Parsing** (`src/parsing/`)
   - **Lexer** (`lexer.c`): Tokenizes input into `t_token` linked list
     - Handles quotes (single/double), operators (pipes, redirections)
     - Token types: `TOKEN_PIPE`, `TOKEN_REDIRECT_OUT/IN/APPEND`, `TOKEN_HEREDOC`, `TOKEN_COMMAND`, `TOKEN_ARGUMENT`
   - **Parser** (`parser.c`): Converts tokens to `t_cmd` command structures
     - Each command has: name, args array, redirections list, next pointer (for pipelines)
   - **Variable Expansion** (`expand_variables.c`): Expands `$VAR` and `$?` in arguments
     - Respects quote context (no expansion in single quotes)

3. **Execution** (`src/execution/`)
   - **Pipeline handling** (`pipeline.c`): Manages multi-command pipelines with `pipe()` and `fork()`
   - **Redirections** (`execution_redirections.c`): Applies `<`, `>`, `>>` using `dup2()`
   - **Heredocs** (`consume_heredocs.c`): Pre-processes `<<` before command execution
   - **Builtins vs External**:
     - Built-in commands executed in-process (no fork for single builtin without pipes)
     - External commands resolved via `PATH` and executed with `execve()`

### Key Data Structures

```c
// Token (lexer output)
typedef struct s_token {
    t_token_type    type;
    char            *value;
    t_quote_type    quote_type;  // NO_QUOTE, SINGLE_QUOTE, DOUBLE_QUOTE
    struct s_token  *next, *prev;
} t_token;

// Redirection
typedef struct s_redir {
    t_token_type    type;        // TOKEN_REDIRECT_IN/OUT/APPEND/HEREDOC
    char            *file;       // filename or heredoc delimiter
    int             expand;      // for heredoc: 1 = expand vars, 0 = literal
    struct s_redir  *next;
} t_redir;

// Command
typedef struct s_cmd {
    char            *name;
    char            **args;      // NULL-terminated array
    t_redir         *redirections;
    struct s_cmd    *next;       // for pipelines
} t_cmd;
```

### Built-in Commands

Located in `src/builtins/`. Available: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

Built-ins are looked up by index using `is_builtin()` and executed via function pointer array.

### Signal Handling

- **Interactive mode** (`src/signals/signals.c`): SIGINT displays new prompt, SIGQUIT ignored
- **Heredoc mode**: SIGINT sets `g_exit_status = 130` and interrupts input
- **Child processes**: Restore default signal handlers

### Global State

- `g_exit_status`: Stores last command exit status (accessible via `$?`)
- Uses `extern char **environ` for environment variable access

### Memory Management

- All heap allocations must be freed before exit
- Each data structure has a corresponding `free_*` function
- Use `make debug` or `make asan` to verify no leaks
- `readline.supp` file suppresses known readline library leaks in valgrind

## Development Notes

- **libft dependency**: Custom C library in `libft/` directory, compiled with `make bonus`
- **Debugging**: Set `DEBUGGING 1` in `include/parsing.h` to enable `debug_print_cmd()` output
- **Heredoc handling**: Special case in `main.c` handles heredoc-only input (e.g., `<<eof <<eof2`) which must consume heredocs but not execute
- **Branch strategy**: Main development branch is `parsing` (not `main` or `master`)
