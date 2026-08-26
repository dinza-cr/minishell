*This project has been created as part of the 42 curriculum by dinza-cr, anbelose.*

# Minishell

## Description

Minishell is a small Unix shell written in C. Its goal is to reproduce the core
behaviour of Bash while providing a practical introduction to process creation,
file descriptors, pipes, signals, parsing, environment variables, and command
execution.

The program reads commands from an interactive prompt, parses them, expands
environment variables, then runs built-in commands or external executables.

## Features

- Interactive prompt and command history powered by GNU Readline
- Execution of programs found through `PATH` or specified by a relative or
  absolute path
- Pipes (`|`)
- Input and output redirections (`<`, `>`, and `>>`)
- Here-documents (`<<`)
- Single and double quotes
- Environment-variable expansion, including `$?`
- Signal handling for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`

## Instructions

### Requirements

The project requires:

- A C compiler such as `cc`, `gcc`, or `clang`
- GNU Make
- GNU Readline development files

On Debian or Ubuntu, install the dependencies with:

```sh
sudo apt update
sudo apt install build-essential libreadline-dev
```

On macOS with Homebrew:

```sh
brew install readline
```

### Compilation

From the repository root, run:

```sh
make
```

The resulting executable is named `minishell`. Other available Make targets
are:

```sh
make clean    # remove object files
make fclean   # remove object files and the executable
make re       # rebuild the entire project
```

### Execution

Start the shell with:

```sh
./minishell
```

Example commands:

```sh
echo "Hello $USER"
pwd
ls -la | grep minishell
cat < input.txt > output.txt
export PROJECT=minishell
echo $PROJECT
exit
```

## Project structure

```text
.
├── inc/          Header files
├── libft/        Utility library
├── src/
│   ├── builtins/ Shell built-ins
│   ├── exec/     Execution, pipes, and redirections
│   ├── pars/     Parsing, quotes, and expansion
│   └── utils/    Main loop, signals, and helpers
└── Makefile
```

## Resources

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html)
- [Linux manual pages](https://man7.org/linux/man-pages/) for system calls such
  as `fork`, `execve`, `pipe`, `dup2`, `open`, `waitpid`, and `signal`

### Use of AI

AI was used to help structure and proofread this README.
