# Simple Shell
  
  ## Description
  
  A simple UNIX command line interpreter built as a project for Holberton School.
  The shell currently supports:
  
  * Displaying a prompt and waiting for the user to enter a command
  * Executing commands passed as a direct path (e.g. `/bin/ls`)
  * Executing commands with arguments
  * Handling errors when a command cannot be run
  * Handling end of file (Ctrl + D) to exit cleanly
  * Running in both interactive and non-interactive mode
  
  Written by Shirleen Asre and Sean Sabino
  
  ---
  
  ## Compilation
  
  ```
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
  ```
  
  ---
  
  ## Requirements
  
  * Allowed editors: vi, vim, emacs
  * Compiled on Ubuntu 20.04 LTS using gcc with `-Wall -Werror -Wextra -pedantic -std=gnu89`
  * All files end with a new line
  * Code follows the Betty style
  * No memory leaks
  * No more than 5 functions per file
  * All header files are include guarded
  * System calls are only used when necessary
  
  ---
  
  ## Progress on the project tasks
  
  | Task | Requirement | Status | Notes |
  |---|---|---|---|
  | 0. README / man / AUTHORS | All three files at root | Done | `README.md`, `man_1_simple_shell`, `AUTHORS` present |
  | 0.1 Simple shell 0.1 | Prompt, single-word command, EOF, errors | Done | Works in interactive and non-interactive mode |
  | 0.2 Simple shell 0.2 | Handle command arguments | Done | Tokenised with `strtok` inside `main.c` |
  | 0.3 Simple shell 0.3 | Use PATH; do not fork if command not found | Partial | `find_path()` exists in `path.c` but `main.c` still calls `execve(argv[0], …)` directly and forks every time |
  | 0.4 Simple shell 0.4 | `exit` built-in | Not done | Header declares `handle_builtin` but `builtins.c` is missing |
  | 1.0 Simple shell 1.0 | `env` built-in | Not done | |
  | Error format | `./hsh: 1: cmd: not found` (argv[0] + line number) | Not done | Currently uses `perror(av[0])` only — no line counter |
  
  ---
  
  ## File Overview
  
  | File | What it does |
  |---|---|
  | `main.h` | Header included by every other file. Holds standard library includes, `MAX_ARGS`, `extern char **environ`, and prototypes for `print_prompt`, `find_path`, `get_env`, `handle_builtin`, `execute_command`, `trim_line`, `split_line`, and `print_error`. Note: several of these are declared but not yet implemented. |
  | `main.c` | Entry point and REPL loop. Reads input with `getline`, trims spaces and newline, splits with `strtok` into `argv`, forks unconditionally, the child runs `execve(argv[0], …)`, and the parent calls `wait`. EOF prints a newline and exits 0. No line counter, PATH lookup, or built-ins yet. |
  | `shell.c` | Contains `print_prompt()` which prints `($) ` and flushes stdout so the prompt shows immediately. |
  | `path.c` | PATH-lookup helpers (written in preparation for task 0.3). `get_env(name)` scans `environ` for a variable. `find_path(cmd)` returns `cmd` directly if it contains `/` and is executable, otherwise splits `$PATH` on `:` and checks each directory with `access(X_OK)`. Defined but not yet wired into `main.c`. |
  | `man_1_simple_shell` | Man page for the shell. |
  | `AUTHORS` | List of contributors. |
  
  ---
  
  ## How to Use
  
  ### Interactive mode
  
  Run the shell after compiling:
  
  ```
  ./hsh
  ```
  
  The prompt will appear:
  
  ```
  ($)
  ```
  
  Commands must currently be entered as a full path:
  
  ```
  ($) /bin/ls
  ($) /bin/echo hello
  ```
  
  The input is tokenised, so `/bin/ls -la` becomes:
  
  ```
  argv[0] = "/bin/ls"
  argv[1] = "-la"
  argv[2] = NULL
  ```
  
  The shell forks a child and runs the command with `execve`. The parent waits using `wait` until the child exits, then the prompt appears again.
  
  ### Non-interactive mode
  
  Commands can also be piped in:
  
  ```
  echo "/bin/ls" | ./hsh
  ```
  
  No prompt is printed in this mode.
  
  ### Exiting
  
  Press **Ctrl + D** at the prompt. The shell catches the end-of-file signal from `getline` and exits.
  
  ---
  
  ## Authors
  
  * Shirleen Asre — https://github.com/bumble-beed
  * Sean Sabino — https://github.com/SSabin0
  
