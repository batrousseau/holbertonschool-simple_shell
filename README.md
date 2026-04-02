# Simple Shell

A minimal UNIX command interpreter written in C as part of the Holberton School curriculum.

## Description

This project implements a very small shell that:

- displays a custom prompt: `Bat2mort$`
- reads a command line from standard input
- removes the trailing newline
- tokenizes the input on spaces
- searches for the executable in the directories listed in `PATH`
- creates a child process with `fork()`
- runs the program with `execve()`
- waits for the child process to finish before reading the next command

The current implementation is intentionally simple and focused on core process management.

## Features

- Interactive prompt
- Basic command parsing with space-separated arguments
- Executable lookup through the `PATH` environment variable
- Process creation with `fork()`
- Program execution with `execve()`
- Parent/child synchronization with `wait()`

## Current limitations

This shell is functional but very limited in its current state:

- it only supports commands with at most **two tokens** (`command arg`)
- it does **not** implement shell builtins such as `cd`, `exit`, `env`, etc.
- it does **not** handle pipes, redirections, quotes, separators, or environment expansion
- it only looks up executables through `PATH`
- it executes commands with `execve(path, prompt, NULL)`, so the child is launched with a `NULL` environment
- error handling and memory management are still very minimal

## Repository structure

- `0-shell_tools.c` - input reading, line cleanup, tokenization, and `PATH` splitting
- `1-main_shell.c` - main shell loop and executable lookup
- `2-debug_tools.c` - debug helper for printing arrays
- `3-general_tools.c` - utility functions (`_strdup`, length helpers, array helpers)
- `4-fork_and_exec.c` - process launch and grouped memory cleanup
- `5-little_ifs.c` - small guard/exit helper functions
- `shell.h` - function prototypes and required headers
- `AUTHORS` - repository contributor list
- `man_1_simple_shell` - man page placeholder

## Requirements

- Ubuntu / Linux environment
- GCC compiler
- Standard C library and POSIX system calls

## Compilation

Compile the project with:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

## Usage

Run the shell:

```bash
./hsh
```

You should then see:

```text
Bat2mort$
```

Example session:

```bash
$ ./hsh
Bat2mort$ ls
AUTHORS  shell.h  0-shell_tools.c  1-main_shell.c  2-debug_tools.c  3-general_tools.c  4-fork_and_exec.c  5-little_ifs.c
Bat2mort$ pwd
/home/user/holbertonschool-simple_shell
```

## How it works

1. `clean_getline()` displays the prompt and reads a line from standard input.
2. `no_new_line()` removes the trailing `\n`.
3. `stroke_getline()` splits the command into tokens.
4. `get_clean_path_directories()` gets the directories from `PATH`.
5. The main loop rebuilds candidate executable paths such as `/bin/ls`.
6. `stat()` checks whether the executable exists.
7. `fork_and_launch()` forks the process and runs the command with `execve()`.
8. The parent waits for the child before prompting again.

## Example supported commands

Commands with zero or one argument are the safest match for the current implementation, for example:

```bash
ls
pwd
whoami
ls -l
```

## Example unsupported cases

The following are outside the scope of the current codebase:

```bash
cd /tmp
exit
env
ls -l /tmp
ls | wc -l
echo "hello world"
cat file > out.txt
```

## Learning goals

This project is a good introduction to:

- command parsing
- process creation
- executable lookup
- system calls in C
- basic shell architecture
- memory allocation and cleanup

## Authors

- batrousseau

## Possible improvements

- support more than two arguments
- add builtins (`exit`, `env`, `cd`)
- support non-interactive mode
- preserve and pass the environment to `execve()`
- improve error messages
- improve memory management
- add proper man page documentation
- add tests

## License

No license is specified in this repository.