## Summary

In this project, you are required to build a feature-rich shell that emulates many functionalities of a standard UNIX shell. The "Minishell" program should provide a command prompt where users can enter commands and execute programs. The shell should handle various advanced features such as environment variable expansion, input/output redirection, pipes, signal handling, command execution, and more.

## Skills to Learn

- Advanced Command-Line Interpretation
- Environment Variables
- I/O Redirection
- Pipes
- Signal Handling
- Command Execution
- Built-in Commands

## The "Minishell" Program

### Usage

```bash
./minishell
```

### Description

The "Minishell" program serves as a fully functional UNIX-like shell, capable of interpreting complex commands and executing them. The shell should provide a command prompt where users can enter commands and receive output on the standard output.

The shell should support the following features:

- Basic command execution: Run simple commands like ls, echo, etc.
- Environment variable expansion: Allow the use of environment variables like $HOME, $PATH, etc.
- Input/output redirection: Support redirecting input from a file and redirecting output to a file.
- Pipes: Allow chaining multiple commands together using pipes (|).
- Signal handling: Handle signals like Ctrl+C (SIGINT) and Ctrl+Z (SIGTSTP).
- Built-in commands: Implement some built-in commands like cd, echo, exit, etc.
- Command history: Support command history with the arrow keys.
- Line editing: Provide basic line editing and editing capabilities like moving the cursor.

## Project Constraints

- The shell should display a prompt and wait for user input.
- Commands should be executed in a separate process using fork() and exec() functions.
- The shell should handle signal interruptions and provide signal handling capabilities.
- Environment variables should be expanded within double quotes and commands using backticks.
- Input/output redirection should work for both input and output.
- Pipes should allow chaining multiple commands together.

## Example Usage

```bash
$> ./minishell
minishell$ ls -l
total 16
-rwxr-xr-x 1 user 197121 8424 Nov 20 16:53 minishell
minishell$ echo "Hello, world!"
Hello, world!
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
minishell$ ls | wc -l
       1
minishell$ ls -l > output.txt
minishell$ cat output.txt
total 16
-rwxr-xr-x 1 user 197121 8424 Nov 20 16:53 minishell
minishell$ cd Documents
minishell$ pwd
/Users/user/Documents
minishell$ exit
$
```
